#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"

#define max_num(x, y) (x > y ? x : y)
#define min_num(x, y) (x < y ? x : y)

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
	printf("  0 1 2 3 4 5 6 7\n");
	for (int y = 0; y < 8; y++) {
		printf("%i ", y);
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] != NULL) {
				printf("%c", board->pieces[y][x]->color);
			} else {
				printf("·");
			}
			if (x != 7) printf(" ");
		}
		printf("\n");
	}
}

void board_add_piece(board_t *board, char color, int x, int y) {
	piece_t *new_piece = piece_init(color, x, y);
	if (board_can_add(board, new_piece)) {
		board_flip_pieces(board, new_piece);
		board->pieces[y][x] = new_piece;
	}

}

bool board_can_add(board_t *board, piece_t *piece) {
	return (board_flip_amount_HV(board, "horizontal", piece) > 0 || board_flip_amount_HV(board, "vertical", piece) > 0   ||
		board_flip_amount_D(board, "topright", piece) > 0    || board_flip_amount_D(board, "bottomright", piece) > 0 ||
		board_flip_amount_D(board, "bottomleft", piece) > 0  || board_flip_amount_D(board, "topleft", piece) > 0);
}

int board_flip_amount_HV(board_t *board, char* direction, piece_t *piece) {
	int pieceX = piece->x;
	int pieceY = piece->y;
	char pieceColor = piece->color;
	if (strcmp(direction, "horizontal") == 0) {
		if (board->pieces[pieceY][pieceX+1] != NULL && board->pieces[pieceY][pieceX+1]->color != pieceColor) {
			int pieces = 0;
			for (int i = pieceX+2; i < 8; ++i) {
				pieces++;
				if (board->pieces[pieceY][i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		} else if (board->pieces[pieceY][pieceX-1] != NULL && board->pieces[pieceY][pieceX-1]->color != pieceColor) {
			int pieces = 0;
			for (int i = pieceX-2; i > -1; --i) {
				pieces++;
				if (board->pieces[pieceY][i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
    if (strcmp(direction, "vertical") == 0) {
		if (board->pieces[pieceY+1][pieceX] != NULL && board->pieces[pieceY+1][pieceX]->color != pieceColor) {
			int pieces = 0;
			for (int i = pieceY+2; i < 8; ++i) {
				pieces++;
				if (board->pieces[i][pieceX]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		} else if (board->pieces[pieceY-1][pieceX] != NULL && board->pieces[pieceY-1][pieceX]->color != pieceColor) {
			int pieces = 0;
			for (int i = pieceY-2; i > -1; --i) {
				pieces++;
				if (board->pieces[i][pieceX]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
	return 0;
}

int board_flip_amount_D(board_t *board, char* direction, piece_t *piece) {
	int pieceX = piece->x;
	int pieceY = piece->y;
	char pieceColor = piece->color;
	if (strcmp(direction, "topright") == 0) { 
		if (board->pieces[pieceY-1][pieceX+1] != NULL && board->pieces[pieceY-1][pieceX+1]->color != pieceColor) {
			int max = max_num(pieceX, pieceY);
			int pieces = 0;
			for (int i = 2; i < 7-max; ++i) {
				pieces++;
				if (board->pieces[pieceY-i][pieceX+i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
    if (strcmp(direction, "bottomright") == 0) {
		if (board->pieces[pieceY+1][pieceX+1] != NULL && board->pieces[pieceY+1][pieceX+1]->color != pieceColor) {
			int max = max_num(pieceX, pieceY);
			int pieces = 0;
			for (int i = 2; i < 7-max; ++i) {
				pieces++;
				if (board->pieces[pieceY+i][pieceX+i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
    if (strcmp(direction, "bottomleft") == 0) {
		if (board->pieces[pieceY+1][pieceX-1] != NULL && board->pieces[pieceY+1][pieceX-1]->color != pieceColor) {
			int min = min_num(pieceX, pieceY);
			int pieces = 0;
			for (int i = 2; i < 1+min; --i) {
				pieces++;
				if (board->pieces[pieceY+i][pieceX-i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
    if (strcmp(direction, "topleft") == 0) {
		if (board->pieces[pieceY-1][pieceX-1] != NULL && board->pieces[pieceY-1][pieceX-1]->color != pieceColor) {
			int min = min_num(pieceX, pieceY);
			int pieces = 0;
			for (int i = 2; i < 1+min; --i) {
				pieces++;
				if (board->pieces[pieceY-i][pieceX-i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
	return 0;
}

void board_flip_pieces(board_t *board, piece_t *piece) {
	int pieceX = piece->x;
	int pieceY = piece->y;
	char pieceColor = piece->color;
	if (board_flip_amount_HV(board, "horizontal", piece) > 0) {
		for (int i = 1; i <= board_flip_amount_HV(board, "horizontal", piece); i++) {
			if (board->pieces[pieceY][pieceX+1] != NULL) board->pieces[pieceY][pieceX+i]->color = pieceColor;
			if (board->pieces[pieceY][pieceX-1] != NULL) board->pieces[pieceY][pieceX-i]->color = pieceColor;
		}
	}
	if (board_flip_amount_HV(board, "vertical", piece) > 0) {
		for (int i = 1; i <= board_flip_amount_HV(board, "vertical", piece); ++i) {
			if (board->pieces[pieceY+1][pieceX] != NULL) board->pieces[pieceY+i][pieceX]->color = pieceColor;
			if (board->pieces[pieceY-1][pieceX] != NULL) board->pieces[pieceY-i][pieceX]->color = pieceColor;
		}
	}
	if (board_flip_amount_D(board, "topright", piece) > 0) {
		for (int i = 1; i <= board_flip_amount_D(board, "topright", piece); ++i) {
			board->pieces[pieceY-i][pieceX+i]->color = pieceColor;
		}
	}
	if (board_flip_amount_D(board, "bottomright", piece) > 0) {
		for (int i = 1; i <= board_flip_amount_D(board, "bottomright", piece); ++i) {
			 board->pieces[pieceY+i][pieceX+i]->color = pieceColor;
		}
	}
	if (board_flip_amount_D(board, "bottomleft", piece) > 0) {
		for (int i = 1; i <= board_flip_amount_D(board, "bottomleft", piece); ++i) {
			board->pieces[pieceY+i][pieceX-i]->color = pieceColor;
		}
	}
	if (board_flip_amount_D(board, "topleft", piece) > 0) {
		for (int i = 1; i <= board_flip_amount_D(board, "topleft", piece); ++i) {
			board->pieces[pieceY-i][pieceX-i]->color = pieceColor;
		}
	}
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
