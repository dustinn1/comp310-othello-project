#ifndef _TREE_H_
#define _TREE_H_

#include "board.h"

typedef struct _node_t {
    board_t* board;
	int depth;
	int numOfChildren;
	char player;
	int piecesFlipped, value;
	point_t recentPieceAdded, firstPieceAdded;
    struct _node_t* *children;
} node_t;

extern node_t* node_init(board_t *board);

extern node_t* node_add(node_t *parent, int x, int y);

extern void node_clear(node_t *node);

extern void node_children_allocate(node_t *node, int size);

extern void node_delete(node_t *node);

extern void node_calculate_value(node_t *node, int parent_value, int numOfChildren);

extern void tree_create(node_t *parent_node, int depth);

extern void tree_init();

extern node_t* tree_get_max(node_t *node, int depth);

#endif