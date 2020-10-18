#ifndef _BOARD_H_
#define _BOARD_H_

#include "piece.h"

typedef struct _board_t {
	bool isFull;
	piece_t pieces[8][8];
} board_t

extern void board_init(*board_t board);

extern void board_print(*board_t board);

extern *board_t board_copy(*board_t board);

extern bool board_full(*board_t board);

#endif
