#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "board.h"

#include "piece.h"

void board_init(board_t *board) {
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
	printf("\n");
}

void board_add_piece(board_t *board, int color, int x, int y) {
	piece_t *new_piece = piece_init(color, x, y);
	if (board_can_place(board, "horizontal", new_piece)) {
		board->pieces[y][x] = new_piece;
		printf("new %s piece added at x: %i, y: %i\n", color == 0 ? "white" : "black", x, y);
	} else {
		printf("cannot add new %s piece added at x: %i, y: %i\n", color == 0 ? "white" : "black", x, y);
	}
}

bool board_can_place(board_t *board, char* direction, piece_t* piece) {
	int pieceX = piece->x;
	int pieceY = piece->y;
	int pieceColor = piece->color;
	if (strcmp(direction, "horizontal") == 0) {
		if (board->pieces[pieceY][pieceX+1] != NULL || board->pieces[pieceY][pieceX-1] != NULL) {
			for (int i = pieceX+2; i < 8; i++) {
				if (board->pieces[pieceY][i] != NULL && board->pieces[pieceY][i]->color == pieceColor) {
					return true;
				}
			}
			for (int i = pieceX-2; i > 0; i--) {
				if (board->pieces[pieceY][i] != NULL && board->pieces[pieceY][i]->color == pieceColor) {
					return true;
				}
			}
		}
	}
	if (strcmp(direction, "vertical") == 0) {
		if (board->pieces[pieceY+1][pieceX] != NULL || board->pieces[pieceY-1][pieceX] != NULL) {
			for (int i = pieceY+2; i < 8; i++) {
				if (board->pieces[i][pieceX] != NULL && board->pieces[i][pieceX]->color == pieceColor) {
					return true;
				}
			}
			for (int i = pieceY-2; i > 0; i--) {
				if (board->pieces[i][pieceX] != NULL && board->pieces[i][pieceX]->color == pieceColor) {
					return true;
				}
			}
		}
	}
	return false;
}

void board_copy(board_t *board_to, board_t *board_from) {
	memcpy(board_to->pieces, board_from->pieces, sizeof(board_from->pieces));
}

bool board_is_full(board_t *board) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] == NULL) {
				return false;
			}
		}
	}
	return true;
}
