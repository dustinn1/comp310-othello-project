#ifndef _TREE_H_
#define _TREE_H_

#include "board.h"

typedef struct _node_t {
	board_t* board;
	int numOfChildren;
	struct _node_t* children;
} node_t;

extern point_t* node_init(node_t *node, board_t *board);

extern point_t* node_add(node_t *node, node_t *parent);

#endif
