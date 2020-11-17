#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "board.h"

void node_init(node_t *node, board_t *board) {
	node->depth = 1;
	node->board = *board;
	node->children = malloc(sizeof(node_t));
	node->numOfChildren = 0;
	node->player = 'P';
	node->piecesFlipped = 0;
}

node_t* node_add(node_t *parent, int x, int y) {
	node_t* node = (node_t*) malloc(sizeof(node_t));
	node->depth = parent->depth+1;
	node->children = (node_t*) malloc(sizeof(node_t));

	board_copy(&node->board, &parent->board);
	parent->numOfChildren += 1;

	node->player = parent->player == 'P' ? 'C' : 'P';
	//printf("%c\n", node->player);
	//printf("%i, %i\n", node->board.points[i]->x, node->board.points[i]->y);
	//board_add_piece(&node->board, node->player, x, y);	
	parent->children = (node_t*) realloc(parent->children, parent->numOfChildren * sizeof(node_t));
	//parent->children[parent->numOfChildren-1] = *node;
	return node;
}

void node_delete(node_t *node) {
	node = calloc(1, sizeof(node_t));
	free(node);
}
