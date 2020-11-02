#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "points.h"

int main(void) {
	static board_t board;
	board_init(&board);

	char currentPlayer = 'B';
	char* currentPlayerName = "Black";

	while (!board_is_full(&board)) {
		printf("\n====================== %s's turn ====================\n\n", currentPlayerName);
		board_print(&board, currentPlayer);
		printf("Black: %i pieces, White: %i pieces\n", board_count_pieces(&board, 'B'), board_count_pieces(&board, 'W'));
		
		int playerX, playerY;
		if (!points_is_empty(board.points)) {
			printf("\n%s: Enter the x and y to place a piece\n", currentPlayerName);
			printf("x y: ");
			scanf("%d %d", &playerX, &playerY);
			while (((playerX < 0 || playerX > 7) || (playerY < 0 || playerY > 7)) || !points_contains(board.points, playerX, playerY)) {
				printf("Please enter a valid coordinate (x and y >= 0 and <= 7)\n");
				printf("x y: ");
				scanf("%d %d", &playerX, &playerY);
			}


			printf("\n%s piece added at x: %i, y: %i \n", currentPlayerName, playerX, playerY);
			
			board_add_piece(&board, currentPlayer, playerX, playerY);
			points_reset(board.points);
		}

		currentPlayer = currentPlayer == 'B' ? 'W' : 'B';
		currentPlayerName = currentPlayer == 'B' ? "Black" : "White";
	}

	int BPieces = board_count_pieces(&board, 'B');
	int WPieces = board_count_pieces(&board, 'W');
	
	board_print(&board, currentPlayer);
	printf("Black: %i pieces, White: %i pieces\n", board_count_pieces(&board, 'B'), board_count_pieces(&board, 'W'));

	printf("========================================");
	printf("\n\t %s Player Wins \t\n", BPieces > WPieces ? "Black" : "White");
	printf("========================================\n");

	board_delete(&board);

	return 0;
}
