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

void expand_tree(node_t *node) {
        if (node->depth != 4) {
                int numPoints = board_num_points(node->board, node->player);
		board_print_old(node->board, node->player);
		printf("%i\n", numPoints);
                for (int i = 0; i < numPoints; i++) {
                        node_t new_node;
                      	node_add(&new_node, node);
                        expand_tree(&new_node);
                }
        }
}

int main(void) {
	static board_t board;
	board_init(&board);

	node_t root;
	node_init(&root, &board);
        expand_tree(&root);

	return 0;
}

