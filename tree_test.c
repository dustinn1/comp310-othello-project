#include <stdlib.h>
#include <curses.h>

#include "tree.h"
#include "board.h"
#include "points.h"

void board_print_old(board_t *board, char color, int depth) {
	for (int i = 0; i <= depth; i++) {
        printf("\t");
    }
    printf("  0 1 2 3 4 5 6 7\n");
	int amount = 0;
	for (int y = 0; y < 8; y++) {
        for (int i = 0; i <= depth; i++) {
            printf("\t");
        }
		printf("%i ", y);
		for (int x = 0; x < 8; x++) {
			if (board->pieces[y][x] != NULL) {
				printf("%c", board->pieces[y][x]->color);
			} else if (board_can_add_print(board, color, x, y)) {
				if (color == 'W') {
					printf("◼");
				} else {
					printf("◻");
				}
				amount++;
			} else {
				printf("·");
			}
			if (x != 7) printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
}

void points_print_old(point_t **points, int amount) {
        for (int i = 0; i < amount; ++i) {
            printf("%i, %i", points[i]->x, points[i]->y);
            if (i != amount-1) printf(" | ");
        }
	printf("\n\n");
}

void expand_tree(node_t *parent_node) {
    if (parent_node->depth != 3) {
        char oppositePlayer = parent_node->player == 'P' ? 'C' : 'P';
        int numPoints = board_num_points(parent_node->board, oppositePlayer);

        node_t* child_nodes[numPoints];
        for (int i = 0; i < numPoints; i++) {
            child_nodes[i] = node_add(parent_node, parent_node->board->points[i]->x, parent_node->board->points[i]->y);
            expand_tree(child_nodes[i]);
        }
    }
}

void print_tree(node_t *node) {
    if (node->pieceAdded.x == 0 && node->pieceAdded.y == 0) {
        printf("\troot\n");
        //board_print_old(node->board, node->player, node->depth);
    } else {
        for (int i = 0; i <= node->depth; i++) {
            printf("\t");
        }
        printf("%i, %i\n\n", node->pieceAdded.x, node->pieceAdded.y);
        //board_print_old(node->board, node->player, node->depth);
    }
    for (int i = 0; i < node->numOfChildren; i++) {
        print_tree(node->children[i]);
    }
}

int main(void) {
	board_t* board = board_init();
    board_print_old(board, 'P', 0);
    board_add_piece(board, 'P', 2, 3);
    node_t* root = node_init(board);
    expand_tree(root);
    print_tree(root);
	return 0;
}
