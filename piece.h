#ifndef _PIECE_H_
#define _PIECE_H_

typedef struct _piece_t {
	int color; // 0 = white, 1 = black
	int x, y;	
} piece_t

extern void piece_init(int color, int x, int y);

extern int getColor(*piece_t piece);

#endif
