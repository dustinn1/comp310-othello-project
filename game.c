#include <curses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "points.h"

#define PLAYER 'P'
#define PLAYER_NAME "Player"
#define PLAYER_COLOR "red"
#define COMPUTER 'C'
#define COMPUTER_NAME "Computer"
#define COMPUTER_COLOR "blue"

int main(void) {
	// initialize curses
	WINDOW* mainwin;

	if ((mainwin = initscr()) == NULL) {
		exit(1);
	}
	int widthcenter = (getmaxx(mainwin)/2)-20;
	start_color();
	
	init_pair('r', COLOR_RED, COLOR_BLACK);
	init_pair('w', COLOR_WHITE, COLOR_BLACK);

	// initialize othello game
	static board_t board;
	board_init(&board);

	char currentPlayer = PLAYER;
	char* currentPlayerName = PLAYER_NAME;

	while (!board_is_full(&board)) {
		mvprintw(2, widthcenter, "%s's turn", currentPlayerName);
		mvprintw(4, widthcenter-9, "%s: %i pieces, %s: %i pieces\n", PLAYER_NAME, board_count_pieces(&board, PLAYER), COMPUTER_NAME, board_count_pieces(&board, COMPUTER));
		board_print(&board, currentPlayer, widthcenter-3);

		int x, y;
		if (!points_is_empty(board.points)) {
			mvprintw(18, widthcenter-13, "%s: Enter the x and y to place a piece\n", currentPlayerName);
			mvprintw(20, widthcenter-13, "x y: ");
			refresh();
			scanw("%d %d", &x, &y);
			refresh();
			while (((x < 0 || x > 7) || (y < 0 || y > 7)) || !points_contains(board.points, x, y)) {
				color_set('r', NULL);
				mvprintw(20, widthcenter-13, "Please enter a valid coordinate (x and y >= 0 and <= 7)");
				color_set('w', NULL);
				move(22, widthcenter-13);
				clrtoeol();
				printw("x y: ");
				scanw("%d %d", &x, &y);
			}

			//mvprintw(20, 4, "\n%s piece added at x: %i, y: %i \n", currentPlayerName, playerX, playerY);
			//refresh();
			board_add_piece(&board, currentPlayer, x, y);
			points_reset(board.points);
			refresh();
			clear();
		}

		currentPlayer = currentPlayer == PLAYER ? COMPUTER : PLAYER;
		currentPlayerName = currentPlayer == PLAYER ? PLAYER_NAME : COMPUTER_NAME;
	}
/*
	int BPieces = board_count_pieces(&board, 'B');
	int WPieces = board_count_pieces(&board, 'W');

	board_print(&board, currentPlayer, widthcenter+3);
	mvprintw(4, widthcenter-9, "Black: %i pieces, White: %i pieces\n", board_count_pieces(&board, 'B'), board_count_pieces(&board, 'W'));
	mvprintw(4, widthcenter-9, "\n\t %s Player Wins \t\n", BPieces > WPieces ? "Black" : "White");
	refresh();
*/	
	board_delete(&board);

	endwin();
	delwin(mainwin);
	exit(0);
}
