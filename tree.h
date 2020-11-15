#ifndef _TREE_H_
#define _TREE_H_

#include "board.h"

typedef struct _node_t {
	int depth;
	board_t* board;
	struct _node_t* children;
	int numOfChildren;
	char player;
	int piecesFlipped;
} node_t;

extern point_t* node_init(node_t *node, board_t *board);

extern point_t* node_add(node_t *node, node_t *parent);

extern void node_delete(node_t *node);

#endif
