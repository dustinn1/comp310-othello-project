#include <curses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "board.h"
#include "points.h"
#include "tree.h"

#define PLAYER 'P'
#define PLAYER_NAME "Player"
#define COMPUTER 'C'
#define COMPUTER_NAME "Computer"

int main(int argc, char *argv[]) {
	// get the difficulty of the game
	// if no difficulty parameter is set, then set the difficulty as 2
	// otherwise, set the difficulty to 1, 2, or 3 depending on what was chosen
	int difficulty;

	if (argc == 1) {
		difficulty = 2;
	} else {
		int c;
		int digit_optind = 0;

		while (1) {
			int this_option_optind = optind ? optind : 1;
			int option_index = 0;
			static struct option long_options[] = {
				{"difficulty", required_argument, 0, 'd' },
				{0,            0,                 0,  0 }
			};
			c = getopt_long(argc, argv, "abc:d:012", long_options, &option_index);
			if (c == -1) break;
			switch (c) {
				case 'd': {
						int argint = atoi(optarg);
						if (argint > 0 && argint < 4) {
							difficulty = argint;
							break;
						} else {
							printf("Difficulty must be 1, 2, or 3\n");
							exit(EXIT_FAILURE);
						}
					}
				default:
					exit(EXIT_FAILURE);
			}
		}
	}

	int depth;
	switch (difficulty) {
		case 1:
			depth = 3;
		case 2:
			depth = 4;
		case 3:
			depth = 5;
	}

	// initialize curses
	WINDOW* mainwin;

	if ((mainwin = initscr()) == NULL) {
		exit(1);
	}
	int widthcenter = (getmaxx(mainwin)/2)-20;
	start_color();
	
	init_pair('r', COLOR_RED, COLOR_BLACK);
	init_pair('b', COLOR_BLUE, COLOR_BLACK);
	init_pair('w', COLOR_WHITE, COLOR_BLACK);

	// initialize othello game
	board_t* board = board_init();

	char currentPlayer = PLAYER;
	char* currentPlayerName = PLAYER_NAME;

	// run the loop until the board is filled with pieces
	while (!board_is_full(board)) {
		int numPoints;
		mvprintw(0, widthcenter, "Difficulty %i", difficulty);
		mvprintw(2, widthcenter, "%s's turn", currentPlayerName);
		mvprintw(4, widthcenter-9, "%s: %i pieces, %s: %i pieces\n", PLAYER_NAME, board_count_pieces(board, PLAYER), COMPUTER_NAME, board_count_pieces(board, COMPUTER));
		numPoints = board_print(board, currentPlayer, widthcenter-3);

		int x, y;
		if (numPoints > 0) {
			if (!points_is_empty(board->points)) {
				mvprintw(18, widthcenter-13, "%s: Enter the x and y to place a piece\n", currentPlayerName);
				mvprintw(20, widthcenter-13, "x y: ");
				refresh();
				if (currentPlayer == PLAYER) {
					scanw("%d %d", &x, &y); // get the player's input
					refresh();
					// check to see if the coordinate the player enter is valie (x and y between 0 and 7)
					// and that it is a possible position to place a piece on
					while (((x < 0 || x > 7) || (y < 0 || y > 7)) || !points_contains(board->points, x, y)) {
						color_set('r', NULL);
						mvprintw(20, widthcenter-13, "Please enter a valid coordinate (x and y >= 0 and <= 7)");
						color_set('w', NULL);
						move(22, widthcenter-13);
						clrtoeol();
						printw("x y: ");
						scanw("%d %d", &x, &y);
					}
				} else if (currentPlayer == COMPUTER) {
					// create a search tree to determine where to place a piece that would
					// give the computer a better chance of winning.
					node_t* root = node_init(board);
    				tree_create(root, depth);
					node_t* max = tree_get_max(root, depth);
					x = max->firstPieceAdded.x;
					y = max->firstPieceAdded.y;

					// remove the tree from memory
					free(root);
					free(max);
    				root = calloc(sizeof(root), sizeof(node_t*));
    				max = calloc(sizeof(max), sizeof(node_t*));
				}	
				board_add_piece(board, currentPlayer, x, y);
				points_reset(board->points);
				clear();
				refresh();
				mvprintw(24, widthcenter-10, "%s piece added at x: %i, y: %i", currentPlayerName, x, y);	
			}
		}
		// switch the current player
		currentPlayer = currentPlayer == PLAYER ? COMPUTER : PLAYER;
		currentPlayerName = currentPlayer == PLAYER ? PLAYER_NAME : COMPUTER_NAME;
	}

	// count the number of pieces each player has in the end
	int PPieces = board_count_pieces(board, PLAYER);
	int CPieces = board_count_pieces(board, COMPUTER);

	// display the winner based on who has the largest number of pieces
	clear();
	board_print(board, currentPlayer, widthcenter+3);
	mvprintw(18, widthcenter-9, "%s: %i pieces, %s: %i pieces", PLAYER_NAME, board_count_pieces(board, PLAYER), COMPUTER_NAME, board_count_pieces(board, COMPUTER));
	mvprintw(20, widthcenter-9, "\t %s Player Wins \t", PPieces > CPieces ? PLAYER_NAME : COMPUTER_NAME);
	refresh();
	sleep(10);
	
	// delete the board from memory
	board_delete(board);

	endwin();
	delwin(mainwin);
	exit(0);
}