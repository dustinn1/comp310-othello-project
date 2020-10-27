#include <stdio.h>
#include <stdlib.h>

#include "board.h"

int main(void) {
	static board_t board;
	board_init(&board);

	char currentPlayer = 'B';
	char* currentPlayerName = "Black";

	while (!board_is_full(&board)) {
		printf("Black: %i pieces, White: %i pieces\n", board_count_pieces(&board, 'B'), board_count_pieces(&board, 'W'));
		board_print(&board, currentPlayer);

		int playerX, playerY;
		printf("\n%s: Enter the x and y to place a piece\n", currentPlayerName);
		printf("x y: ");
		scanf("%d %d", &playerX, &playerY);
		printf("\n%s piece added at x: %i, y: %i \n", currentPlayerName, playerX, playerY);
		
		board_add_piece(&board, currentPlayer, playerX, playerY);

		currentPlayer = currentPlayer == 'B' ? 'W' : 'B';
		currentPlayerName = currentPlayer == 'B' ? "Black" : "White";
	}

	return 0;
}