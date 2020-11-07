#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

#include "points.h"

#define BOARD_SIZE 8

typedef struct _piece_t {
	char color;
	int x, y;	
} piece_t;

typedef struct _board_t {
	point_t* points[50];
	piece_t* pieces[BOARD_SIZE][BOARD_SIZE];
} board_t;

extern piece_t* piece_init(char color, int x, int y);

extern void board_init(board_t *board);

extern void board_print(board_t *board, char color);

extern void board_add_piece(board_t *board, char color, int x, int y);

extern bool board_can_add(board_t *board, piece_t *piece);

extern bool board_can_add_print(board_t *board, char color, int x, int y);

extern int board_flip_amount(board_t *board, char* direction, piece_t *piece);

extern void board_flip_pieces(board_t *board, piece_t *piece);

extern void board_copy(board_t *board_to, board_t *board_from);

extern bool board_is_full(board_t *board);

extern int board_count_pieces(board_t *board, char color);

extern void board_delete(board_t *board);

#endif
