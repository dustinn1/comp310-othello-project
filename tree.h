#ifndef _TREE_H_
#define _TREE_H_

#include "board.h"

typedef struct _node_t {
    board_t* board;
	int depth;
	int numOfChildren;
	char player;
	int piecesFlipped;
	piece_t pieceAdded;
    struct _node_t* *children;
} node_t;

extern node_t* node_init(board_t *board);

extern node_t* node_add(node_t *parent, int x, int y);

extern void node_delete(node_t *node);

extern void tree_create(node_t *parent_node);

#endif