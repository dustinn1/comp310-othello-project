#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdlib.h>

typedef struct _piece_t {
	int color; // 0 = white, 1 = black
	int x, y;	
} piece_t;

extern piece_t* piece_init(int color, int x, int y);

extern int get_color(piece_t *piece);

#endif
