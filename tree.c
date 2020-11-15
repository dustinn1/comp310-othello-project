#include <stdlib.h>

#include "tree.h"
#include "board.h"

point_t* node_init(node_t *node, board_t *board) {
	node->board = board;
	node->children = malloc(sizeof(node_t));
}

point_t* node_add(node_t *node, node_t *parent) {
	board_copy(node->board, parent->board);
	parent->numOfChildren += 1;
	parent->children = realloc(parent->children, parent->numOfChildren * sizeof(node_t));
}
