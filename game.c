#include <curses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "board.h"
#include "points.h"
#include "tree.h"

#define PLAYER 'P'
#define PLAYER_NAME "Player"
#define COMPUTER 'C'
#define COMPUTER_NAME "Computer"

int main(void) {
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

	while (!board_is_full(board)) {
		int numPoints;
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
					scanw("%d %d", &x, &y);
					refresh();
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
					node_t* root = node_init(board);
    				tree_create(root);
					node_t* max = tree_get_max(root);
					x = max->firstPieceAdded.x;
					y = max->firstPieceAdded.y;

					free(root);
					free(max);
    				root = calloc(sizeof(root), sizeof(node_t*));
    				max = calloc(sizeof(max), sizeof(node_t*));
					sleep(3);
				}	
				board_add_piece(board, currentPlayer, x, y);
				points_reset(board->points);
				clear();
				refresh();
				mvprintw(24, widthcenter-10, "%s piece added at x: %i, y: %i", currentPlayerName, x, y);	
			}
		}
		currentPlayer = currentPlayer == PLAYER ? COMPUTER : PLAYER;
		currentPlayerName = currentPlayer == PLAYER ? PLAYER_NAME : COMPUTER_NAME;
	}

	int PPieces = board_count_pieces(board, PLAYER);
	int CPieces = board_count_pieces(board, COMPUTER);

	clear();
	board_print(board, currentPlayer, widthcenter+3);
	mvprintw(18, widthcenter-9, "%s: %i pieces, %s: %i pieces", PLAYER_NAME, board_count_pieces(board, PLAYER), COMPUTER_NAME, board_count_pieces(board, COMPUTER));
	mvprintw(20, widthcenter-9, "\t %s Player Wins \t", PPieces > CPieces ? PLAYER_NAME : COMPUTER_NAME);
	refresh();
	sleep(10);
	
	board_delete(board);

	endwin();
	delwin(mainwin);
	exit(0);
}