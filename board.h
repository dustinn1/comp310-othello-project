#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>
#include <stdbool.h>

#include "piece.h"

typedef struct _board_t {
	bool isFull;
	piece_t* pieces[8][8];
} board_t;

extern void board_init(board_t *board);

extern void board_print(board_t *board);

extern void board_add_piece(board_t *board, int color, int x, int y);

extern void board_copy(board_t *board_to, board_t *board_from);

extern bool board_full(board_t *board);

#endif
