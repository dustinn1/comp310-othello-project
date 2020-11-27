#include <stdlib.h>
#include <curses.h>

#include "tree.h"
#include "board.h"
#include "points.h"

void board_print_old(board_t *board, char color) {
	printf("  0 1 2 3 4 5 6 7\n");
	int amount = 0;
	for (int y = 0; y < 8; y++) {
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
	printf("\n");
}

void points_print_old(point_t **points, int amount) {
        for (int i = 0; i < amount; ++i) {
            printf("%i, %i", points[i]->x, points[i]->y);
            if (i != amount-1) printf(" | ");
        }
	printf("\n\n");
}

void expand_tree(node_t *parent_node) {
        if (parent_node->depth != 4) {
            int numPoints = board_num_points(parent_node->board, parent_node->player == 'P' ? 'C' : 'P');
            board_print_old(parent_node->board, parent_node->player == 'P' ? 'C' : 'P');
                    
            points_print_old(parent_node->board->points, numPoints);
            node_t* child_nodes[numPoints];
            for (int i = 0; i < numPoints; i++) {
                child_nodes[i] = node_add(parent_node, parent_node->board->points[i]->x, parent_node->board->points[i]->y);
                //board_add_piece(child_nodes[i]->board, child_nodes[i]->player, parent_node->board->points[i]->x, parent_node->board->points[i]->y);
                //board_print_old(new_nodes[i]->board, node->player);
                //expand_tree(new_nodes[i]);
            }
            for (int j = 0; j < parent_node->numOfChildren; j++) {
                printf("%i\n", j);
                board_print_old(parent_node->children[j]->board, parent_node->children[j]->player);
                board_print_old(parent_node->board, parent_node->player == 'P' ? 'C' : 'P');
                printf("\n\n\n\n");
            }
            /*
            for (int k = 2; k > -1; k--) {
                printf("%i\n", k);
                board_print_old(node->children[k]->board, node->children[k]->player);
            } */
        }
}

int main(void) {
	board_t* board = board_init();
    board_print_old(board, 'P');
    board_add_piece(board, 'P', 2, 3);
    node_t* root = node_init(board);
    expand_tree(root);

    //board_print_old(board, 'P');

	return 0;
}
