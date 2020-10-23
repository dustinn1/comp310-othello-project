#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct _piece_t {
	int color; // 0 = white, 1 = black
	int x, y;	
} piece_t;

typedef struct _board_t {
	piece_t* pieces[8][8];
} board_t;

extern piece_t* piece_init(int color, int x, int y);

extern void board_init(board_t *board);

extern void board_print(board_t *board);

extern void board_add_piece(board_t *board, int color, int x, int y);

extern bool board_can_place(board_t *board, char* direction, piece_t* piece);

extern void board_copy(board_t *board_to, board_t *board_from);

extern bool board_is_full(board_t *board);

#endif
