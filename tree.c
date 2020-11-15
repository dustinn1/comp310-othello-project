#include <stdlib.h>

#include "tree.h"
#include "board.h"

point_t* node_init(node_t *node, board_t *board) {
	node->depth = 1;
	node->board = board;
	node->children = malloc(sizeof(node_t));
	node->numOfChildren = 0;
	node->player = 'C';
	node->piecesFlipped = 0;
}

point_t* node_add(node_t *node, node_t *parent) {
	node->depth = parent->depth+1;
	board_copy(node->board, parent->board);
	parent->numOfChildren += 1;
	parent->children = realloc(parent->children, parent->numOfChildren * sizeof(node_t));
}

void node_delete(node_t *node) {
	node = calloc(1, sizeof(node_t));
	free(node);
}
