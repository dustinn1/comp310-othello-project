#include <stdlib.h>

#include "tree.h"
#include "board.h"

void node_init(node_t *node, board_t *board) {
	node->depth = 1;
	node->board = board;
	node->children = malloc(sizeof(node_t));
	node->numOfChildren = 0;
	node->player = 'C';
	node->piecesFlipped = 0;
}

void node_add(struct _node_t *node, node_t *parent) {
	node->depth = parent->depth+1;
	node->children = malloc(sizeof(node_t));
	board_copy(node->board, parent->board);
	parent->numOfChildren += 1;
	node->player = parent->player == 'P' ? 'C' : 'P';
	parent->children = realloc(parent->children, parent->numOfChildren * sizeof(node_t));
	parent->children[parent->numOfChildren-1] = *node;
}

void node_delete(node_t *node) {
	node = calloc(1, sizeof(node_t));
	free(node);
}
