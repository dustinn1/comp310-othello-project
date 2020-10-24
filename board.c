#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"

piece_t* piece_init(char color, int x, int y)  {
	piece_t *piece = (piece_t*) malloc(sizeof(piece_t));
	piece->color = color;
	piece->x = x;
	piece->y = y;
	return piece;
}

void board_init(board_t *board) {
	board->pieces[3][3] = piece_init('W', 3, 3);
	board->pieces[3][4] = piece_init('B', 4, 3);
	board->pieces[4][3] = piece_init('B', 3, 4);
	board->pieces[4][4] = piece_init('W', 4, 4);
}

void board_print(board_t *board) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] != NULL) {
				printf("%c", board->pieces[y][x]->color);
			} else {
				printf("*");
			}
			if (x != 7) printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

void board_add_piece(board_t *board, char color, int x, int y) {
	piece_t *new_piece = piece_init(color, x, y);
	if (board_can_place(board, "horizontal", new_piece)) {
		board->pieces[y][x] = new_piece;
	} else if (board_can_place(board, "vertical", new_piece)) {
		board->pieces[y][x] = new_piece;
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
