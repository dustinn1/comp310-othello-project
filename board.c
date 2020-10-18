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
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] != NULL) {
				printf("%i", board->pieces[y][x]->color);
			} else {
				printf("-");
			}
			if (x != 7) printf(" ");
		}
		printf("\n");
	}
}

void board_add_piece(board_t *board, int color, int x, int y) {
	piece_t *new_piece = piece_init(color, x, y);
	board->pieces[y][x] = new_piece;
}

void board_copy(board_t *board_to, board_t *board_from) {
	board_to = board_from;
}

bool board_full(board_t *board) {
	return board->isFull;
}
