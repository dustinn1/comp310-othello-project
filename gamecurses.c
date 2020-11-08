#include <curses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "points.h"

int main(void) {
	// initialize curses
	WINDOW* mainwin;
	int ch;
	
	if ((mainwin = initscr()) == NULL) {
		exit(EXIT_FAILURE);
	}
	int widthcenter = (getmaxx(mainwin)/2)-20;
	start_color();

	// initialize othello game
	static board_t board;
	board_init(&board);

	char currentPlayer = 'B';
	char* currentPlayerName = "Black";

	while (!board_is_full(&board)) {
		mvprintw(2, widthcenter, "%s's turn", currentPlayerName);
		mvprintw(4, widthcenter-9, "Black: %i pieces, White: %i pieces\n", board_count_pieces(&board, 'B'), board_count_pieces(&board, 'W'));
		board_print(&board, currentPlayer, widthcenter-3);

		int playerX, playerY;
		if (!points_is_empty(board.points)) {
			mvprintw(18, widthcenter-13, "%s: Enter the x and y to place a piece\n", currentPlayerName);
			mvprintw(20, widthcenter-13, "x y: ");
			refresh();
			scanw("%d %d", &playerX, &playerY);
			refresh();
			while (((playerX < 0 || playerX > 7) || (playerY < 0 || playerY > 7)) || !points_contains(board.points, playerX, playerY)) {
				mvprintw(20, widthcenter-13, "Please enter a valid coordinate (x and y >= 0 and <= 7)");
				move(22, widthcenter-13);
				clrtoeol();
				printw("x y: ");
				scanw("%d %d", &playerX, &playerY);
			}

			//mvprintw(20, 4, "\n%s piece added at x: %i, y: %i \n", currentPlayerName, playerX, playerY);
			//refresh();
			board_add_piece(&board, currentPlayer, playerX, playerY);
			points_reset(board.points);
			refresh();
			clear();
		}

		currentPlayer = currentPlayer == 'B' ? 'W' : 'B';
		currentPlayerName = currentPlayer == 'B' ? "Black" : "White";
	}

	int BPieces = board_count_pieces(&board, 'B');
	int WPieces = board_count_pieces(&board, 'W');
/*	
	board_print(&board, currentPlayer);
	printf("Black: %i pieces, White: %i pieces\n", board_count_pieces(&board, 'B'), board_count_pieces(&board, 'W'));

	printf("========================================");
	printf("\n\t %s Player Wins \t\n", BPieces > WPieces ? "Black" : "White");
	printf("========================================\n");
*/
	
	board_delete(&board);

	exit(0);
}