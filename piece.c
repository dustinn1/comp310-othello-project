#include <stdlib.h>

#include "piece.h"

piece_t* piece_init(int color, int x, int y)  {
	piece_t *piece = (piece_t*) malloc(sizeof(piece_t));
	piece->color = color;
	piece->x = x;
	piece->y = y;
	return piece;
}

int get_color(piece_t *piece) {
	return piece->color;
}
