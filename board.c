#include <stdio.h>
#include <stdbool.h>

#include "board.h"

#include "piece.h"

void board_init(board_t *board) {
	board->isFull = false;
	board->pieces[3][3] = piece_init(0, 3, 3);
	board->pieces[3][4] = piece_init(1, 4, 3);
	board->pieces[4][3] = piece_init(1, 3, 4);
	board->pieces[4][4] = piece_init(0, 4, 4);
}

void board_print(board_t *board) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->pieces[i][j] != NULL) {
				printf("%i", board->pieces[j][i]->color);
			} else {
				printf("-");
			}
			if (j != 7) printf(" ");
		}
		printf("\n");
	}
}

bool board_full(board_t *board) {
	return board->isFull;
}
