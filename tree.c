#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "board.h"

// initialize the root node for a tree
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

// initialize and add a node to the tree as a child of a parent node
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

// allocate the needed memory for a parent node to store its children nodes
// in an array
void node_children_allocate(node_t *node, int size) {
    node->numOfChildren = size;
    node->children = malloc(size * sizeof(node_t*));
}

// delete a node by free it from memory
void node_delete(node_t *node) {
	node = calloc(1, sizeof(node_t));
	free(node);
}

// calculate the value of the node depending on the parent's value.
// if the node is a computer, add the number of pieces that it flipped when its piece was added
// and the number of children that it has afterwards
// if player, do the same but subtract from the parent value.
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

// recursive function to create a tree 
// get the possible positions that a piece can be placed on
// and create enough children nodes to represent those possible positions
// create the tree until it reaches the specified depth
void tree_create(node_t *parent_node, int depth) {
    if (parent_node->depth < depth) {
        int numPoints = board_num_points(parent_node->board, parent_node->player == 'P' ? 'C' : 'P');
        node_children_allocate(parent_node, numPoints);
        node_t* child_nodes[numPoints];
        for (int i = 0; i < numPoints; i++) {
            child_nodes[i] = node_add(parent_node, parent_node->board->points[i]->x, parent_node->board->points[i]->y);
            parent_node->children[i] = child_nodes[i];
            tree_create(child_nodes[i], depth);
        }
    }
}

// find the largest value out of all of the bottommode nodes
// get the first piece that was added that resulted in the value
node_t* tree_get_max(node_t *node, int depth) {
    node_t* max = (node_t*) malloc(sizeof(node_t));
    for (int i = 0; i < node->numOfChildren; i++) {
        if (node->depth == depth-1) {
            if (max == NULL || node->children[i]->value >= max->value) {
                max->firstPieceAdded.x = node->children[i]->firstPieceAdded.x;
                max->firstPieceAdded.y = node->children[i]->firstPieceAdded.y;
                max->value = node->children[i]->value;
            }
        } else if (node->depth < depth-1) {
            node_t* temp = tree_get_max(node->children[i], depth);
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
        node->children[i] = calloc(sizeof(node->children[i]), sizeof(node_t));
    }
    return max;
}