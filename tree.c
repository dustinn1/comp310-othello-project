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
    node->value = 0;
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

    node_calculate_value(node, parent->value, board_num_points(node->board, parent->player));
	return node;
}

void node_children_allocate(node_t *node, int size) {
    node->numOfChildren = size;
    node->children = malloc(size * sizeof(node_t*));
}

void node_delete(node_t *node) {
	node = calloc(1, sizeof(node_t));
	free(node);
}

void node_calculate_value(node_t *node, int parent_value, int numOfChildren) {
    if (node->depth == 1) {
        node->value = node->piecesFlipped + numOfChildren;
    } else {
        if (node->player == 'C') {
            node->value = parent_value + (node->piecesFlipped + numOfChildren);
        } else if (node->player == 'P') {
            node->value = parent_value - (node->piecesFlipped + numOfChildren);
        }
    }
}

void tree_create(node_t *parent_node) {
    if (parent_node->depth < 5) {
        int numPoints = board_num_points(parent_node->board, parent_node->player == 'P' ? 'C' : 'P');
        node_children_allocate(parent_node, numPoints);
        node_t* child_nodes[numPoints];
        for (int i = 0; i < numPoints; i++) {
            child_nodes[i] = node_add(parent_node, parent_node->board->points[i]->x, parent_node->board->points[i]->y);
            parent_node->children[i] = child_nodes[i];
            tree_create(child_nodes[i]);
        }
    }
}

node_t* tree_get_max(node_t *node) {
    node_t* max = (node_t*) malloc(sizeof(node_t));
    for (int i = 0; i < node->numOfChildren; i++) {
        if (node->depth == 2) {
            if (max == NULL || node->children[i]->value >= max->value) {
                max->firstPieceAdded.x = node->children[i]->firstPieceAdded.x;
                max->firstPieceAdded.y = node->children[i]->firstPieceAdded.y;
                max->value = node->children[i]->value;
            }
        } else if (node->depth < 2) {
            node_t* temp = tree_get_max(node->children[i]);
            if (temp->value > max->value) {
                max->firstPieceAdded.x = temp->firstPieceAdded.x;
                max->firstPieceAdded.y = temp->firstPieceAdded.y;
                max->value = temp->value;
                if (i == 0) {
                    free(temp);
                    temp = calloc(sizeof(temp), sizeof(node_t*));
                }
            }
        }
        free(node->children[i]);
        node->children[i] = calloc(sizeof(node->children[i]), sizeof(node_t*));
    }
    return max;
}