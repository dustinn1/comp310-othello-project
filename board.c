#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

#include "board.h"
#include "points.h"

piece_t* piece_init(char color, int x, int y)  {
	piece_t *piece = (piece_t*) malloc(sizeof(piece_t));
	piece->color = color;
	piece->x = x;
	piece->y = y;
	return piece;
}

// initialize the board by adding the 4 pieces in the middle
void board_init(board_t *board) {
	board->pieces[3][3] = piece_init('W', 3, 3);
	board->pieces[3][4] = piece_init('B', 4, 3);
	board->pieces[4][3] = piece_init('B', 3, 4);
	board->pieces[4][4] = piece_init('W', 4, 4);
}

// print the board with the pieces. Put squares to represent potential spots to place a piece on
void board_print(board_t *board, char color, int widthcenter) {
	int height = 6; // y value to print the top of the board 
	mvprintw(height, widthcenter, "  0 1 2 3 4 5 6 7");
	height++;
	int amount = 0;
	for (int y = 0; y < 8; y++) {
		mvprintw(height, widthcenter, "%i ", y);
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] != NULL) {
				printw("%c", board->pieces[y][x]->color);
			} else if (board_can_add_print(board, color, x, y)) {
				addch(ACS_DIAMOND);
				// add the coordinate to an array
				board->points[amount] = point_init(x, y);
				amount++;
			} else {
				printw("·");
			}
			if (x != 7) printw(" ");
		}
		height++;
	}
	// print the list of coordinates of the squares
	mvprintw(16, widthcenter-12, "Available coordinates: ");
	points_print(board->points, amount);
}

// add a piece to the board only if the position (x,y) is a playable spot to put a piece on
void board_add_piece(board_t *board, char color, int x, int y) {
	piece_t *new_piece = piece_init(color, x, y);
	if (board_can_add(board, new_piece)) {
		board_flip_pieces(board, new_piece);
		board->pieces[y][x] = new_piece;
	} else {
		new_piece = (piece_t*) calloc(sizeof(new_piece), sizeof(piece_t));
		free(new_piece);
	}

}

// check to see if the piece can be added by seeing if placing it will flip any pieces in any direction
// returns true if it can flip at least 1 piece. else, return false.
bool board_can_add(board_t *board, piece_t *piece) {
	char* directions[8] = { "right", "left", "up", "down", "topright", "bottomright", "bottomleft", "topleft" };
	for (int i = 0; i < 8; i++) {
		if (board_flip_amount(board, directions[i], piece) > 0) return true;
	}
	return false;

}

// same as above but will create a temp piece to check
bool board_can_add_print(board_t *board, char color, int x, int y) {
	piece_t *piece = piece_init(color, x, y);
	char* directions[8] = { "right", "left", "up", "down", "topright", "bottomright", "bottomleft", "topleft" };
	bool value = false; 
	for (int i = 0; i < 8; i++) {	
		if (board_flip_amount(board, directions[i], piece) > 0) value = true;
	}
	piece = (piece_t*) calloc(sizeof(piece), sizeof(piece_t));
	free(piece);
	return value;
}

// returns the amount of pieces that a piece will flip depending on the direction
// depending on the direction, it will check to see 1) if the piece is next to another piece in that direction
// and 2) if that piece next to it is a different color
// if true to both, then it will go to the next piece in that direction and continue until it finds
// a piece with the same color as newly added piece.
int board_flip_amount(board_t *board, char* direction, piece_t *piece) {
	int pieceX = piece->x;
	int pieceY = piece->y;
	char pieceColor = piece->color;	
	if (strcmp(direction, "left") == 0) {
        	if (pieceX != 0 && board->pieces[pieceY][pieceX-1] != NULL && board->pieces[pieceY][pieceX-1]->color != pieceColor) {	
			int i = 1;
			int pieces = 0;
			while (pieceX-i > -1) {
				i++;
				if (board->pieces[pieceY][pieceX-i] == NULL) break;
				pieces++;
				if (board->pieces[pieceY][pieceX-i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
	if (strcmp(direction, "right") == 0) {
		if (pieceX != 7 && board->pieces[pieceY][pieceX+1] != NULL && board->pieces[pieceY][pieceX+1]->color != pieceColor) {	
			int i = 1;
			int pieces = 0;
			while (pieceX+i < 8) {
				i++;
				if (board->pieces[pieceY][pieceX+i] == NULL) break;
				pieces++;
				if (board->pieces[pieceY][pieceX+i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
	if (strcmp(direction, "up") == 0) {
		if (pieceY != 0 && board->pieces[pieceY-1][pieceX] != NULL && board->pieces[pieceY-1][pieceX]->color != pieceColor) {
			int i = 1;
			int pieces = 0;
			while (pieceY-i > -1) {
				i++;
				if (board->pieces[pieceY-i][pieceX] == NULL) break;
				pieces++;
				if (board->pieces[pieceY-i][pieceX]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
       	if (strcmp(direction, "down") == 0) {
		if (pieceY != 7 && board->pieces[pieceY+1][pieceX] != NULL && board->pieces[pieceY+1][pieceX]->color != pieceColor) {
			int i = 1;
			int pieces = 0;
			while (pieceY+i < 8) {
				i++;
				if (board->pieces[pieceY+i][pieceX] == NULL) break;
				pieces++;
				if (board->pieces[pieceY+i][pieceX]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;

		}
	}	
    	if (strcmp(direction, "topright") == 0) { 
		if (pieceX != 7 && pieceY != 0 && board->pieces[pieceY-1][pieceX+1] != NULL && board->pieces[pieceY-1][pieceX+1]->color != pieceColor) {
			int i = 1;
			int pieces = 0;
			while (pieceY-i > -1 || pieceX+i < 8) {
				i++;
				if (board->pieces[pieceY-i][pieceX+i] == NULL) break;
				pieces++;
				if (board->pieces[pieceY-i][pieceX+i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
    	if (strcmp(direction, "bottomright") == 0) {
		if (pieceX != 7 && pieceY != 7 && board->pieces[pieceY+1][pieceX+1] != NULL && board->pieces[pieceY+1][pieceX+1]->color != pieceColor) {
			int i = 1;
			int pieces = 0;
			while (pieceY+i < 8 || pieceX+i < 8) {
				i++;
				if (board->pieces[pieceY+i][pieceX+i] == NULL) break;
				pieces++;
				if (board->pieces[pieceY+i][pieceX+i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
 	if (strcmp(direction, "bottomleft") == 0) {
		if (pieceX != 0 && pieceY != 7 && board->pieces[pieceY+1][pieceX-1] != NULL && board->pieces[pieceY+1][pieceX-1]->color != pieceColor) {
			int i = 1;;
			int pieces = 0;
			while (pieceY+i < 8 || pieceX-i > -1) {
				i++;
				if (board->pieces[pieceY+i][pieceX-i] == NULL) break;
				pieces++;
				if (board->pieces[pieceY+i][pieceX-i]->color == pieceColor) {
					return pieces;
				}
			}
			return 0;
		}
	}
    	if (strcmp(direction, "topleft") == 0) {
		if (pieceX != 0 && pieceY != 0 && board->pieces[pieceY-1][pieceX-1] != NULL && board->pieces[pieceY-1][pieceX-1]->color != pieceColor) {
			int i = 1;
			int pieces = 0;
			while (pieceY-i > -1 || pieceX-i > -1) {
				i++;
				if (board->pieces[pieceY-i][pieceX-i] == NULL) break;
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

// flip the number of pieces (if possible) in all 8 directions of the newly placed piece
void board_flip_pieces(board_t *board, piece_t *piece) {
	int pieceX = piece->x;
	int pieceY = piece->y;
	char pieceColor = piece->color;
	int up_amount = board_flip_amount(board, "up", piece);
	int down_amount = board_flip_amount(board, "down", piece);
	int left_amount = board_flip_amount(board, "left", piece);
	int right_amount = board_flip_amount(board, "right", piece);
	int topright_amount = board_flip_amount(board, "topright", piece);
	int bottomright_amount = board_flip_amount(board, "bottomright", piece);
	int bottomleft_amount = board_flip_amount(board, "bottomleft", piece);
	int topleft_amount = board_flip_amount(board, "topleft", piece);
	if (left_amount > 0) {
		for (int i = 1; i <= left_amount; i++) {
			board->pieces[pieceY][pieceX-i]->color = pieceColor;
		}
	}
	if (right_amount > 0) {
		for (int i = 1; i <= right_amount; i++) {
			 board->pieces[pieceY][pieceX+i]->color = pieceColor;
		}
	}
	if (up_amount > 0) {
		for (int i = 1; i <= up_amount; ++i) {
			board->pieces[pieceY-i][pieceX]->color = pieceColor;
		}
	}
	if (down_amount > 0) {
		for (int i = 1; i <= down_amount; ++i) {
			board->pieces[pieceY+i][pieceX]->color = pieceColor;
		}
	}
	if (topright_amount > 0) {
		for (int i = 1; i <= topright_amount; ++i) {
			board->pieces[pieceY-i][pieceX+i]->color = pieceColor;
		}
	}
	if (bottomright_amount > 0) {
		for (int i = 1; i <= bottomright_amount; ++i) {
			board->pieces[pieceY+i][pieceX+i]->color = pieceColor;
		}
	}
	if (bottomleft_amount > 0) {
		for (int i = 1; i <= bottomleft_amount; ++i) {
			board->pieces[pieceY+i][pieceX-i]->color = pieceColor;
		}
	}
	if (topleft_amount > 0) {
		for (int i = 1; i <= topleft_amount; ++i) {
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

int board_count_pieces(board_t *board, char color) {
	int count = 0;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] != NULL && board->pieces[y][x]->color == color) {
				count++;
			}
		}
	}
	return count;
}

void board_delete(board_t *board) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] != NULL) {
				board->pieces[y][x] = (piece_t*) calloc(sizeof(board->pieces[y][x]), sizeof(piece_t));
				free(board->pieces[y][x]);
			} 
		}
	}
	board = (board_t*) calloc(sizeof(board), sizeof(board_t));
	free(board);
}
