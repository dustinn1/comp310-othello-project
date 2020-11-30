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

void print_tree(node_t *node) {
    if (node->recentPieceAdded.x == 0 && node->recentPieceAdded.y == 0) {
        printf("\troot\n");
        //board_print_old(node->board, node->player, node->depth);
    } else {
        for (int i = 0; i <= node->depth; i++) {
            printf("\t");
        }
        printf("%c Added: %i, %i (First: %i, %i) Flipped %i, num of children %i, value %i\n\n", 
            node->player, node->recentPieceAdded.x, node->recentPieceAdded.y, node->firstPieceAdded.x, node->firstPieceAdded.y, node->piecesFlipped, node->test,
            node->value);
        //board_print_old(node->board, node->player == 'P' ? 'C' : 'P', node->depth);
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
    tree_create(root);
    print_tree(root);
	return 0;
}
