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

	node->recentPieceAdded.x = 0;
	node->recentPieceAdded.y = 0;

    return node;
}

node_t* node_add(node_t *parent, int x, int y) {
	node_t* node = (node_t*) malloc(sizeof(node_t));
    node->board = board_copy(parent->board);
	node->depth = parent->depth+1;
	node->children = malloc(sizeof(node_t*));
	node->player = parent->player == 'P' ? 'C' : 'P';

    node->piecesFlipped = board_amount_flipped(node->board, node->player, x, y);
	board_add_piece(node->board, node->player, x, y);

	node->recentPieceAdded.x = x;
	node->recentPieceAdded.y = y;

	if (node->depth == 1) {
		node->firstPieceAdded.x = x;
		node->firstPieceAdded.y = y;
	} else {
		node->firstPieceAdded.x = parent->firstPieceAdded.x;
		node->firstPieceAdded.y = parent->firstPieceAdded.y;
	}

    parent->numOfChildren += 1;
    parent->children = realloc(parent->children, parent->numOfChildren * sizeof(node_t*));
    parent->children[parent->numOfChildren-1] = node;
	return node;
}

void node_delete(node_t *node) {
	node = calloc(1, sizeof(node_t));
	free(node);
}

void tree_create(node_t *parent_node) {
    if (parent_node->depth != 3) {
        int numPoints = board_num_points(parent_node->board, parent_node->player == 'P' ? 'C' : 'P');
        node_t* child_nodes[numPoints];
        for (int i = 0; i < numPoints; i++) {
            child_nodes[i] = node_add(parent_node, parent_node->board->points[i]->x, parent_node->board->points[i]->y);
            tree_create(child_nodes[i]);
        }
    }
}