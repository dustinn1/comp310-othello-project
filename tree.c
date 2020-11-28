#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "board.h"

node_t* node_init(board_t *board) {
    node_t* node = (node_t*) malloc(sizeof(node_t));
	node->depth = 0;
	node->board = board_copy(board);
	node->numOfChildren = 0;
	node->player = 'P';
	node->piecesFlipped = 0;
    node->children = malloc(sizeof(node_t*));

	node->pieceAdded.x = 0;
	node->pieceAdded.y = 0;
	node->pieceAdded.color = node->player;

    return node;
}

node_t* node_add(node_t *parent, int x, int y) {
	node_t* node = (node_t*) malloc(sizeof(node_t));
    node->board = board_copy(parent->board);
	node->depth = parent->depth+1;
	node->children = malloc(sizeof(node_t*));
	node->player = parent->player == 'P' ? 'C' : 'P';
    
	board_add_piece(node->board, node->player, x, y);

	node->pieceAdded.x = x;
	node->pieceAdded.y = y;
	node->pieceAdded.color = node->player;

    parent->numOfChildren += 1;
    parent->children = realloc(parent->children, parent->numOfChildren * sizeof(node_t*));
    parent->children[parent->numOfChildren-1] = node;
	return node;
}

void node_delete(node_t *node) {
	node = calloc(1, sizeof(node_t));
	free(node);
}