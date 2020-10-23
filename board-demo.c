#include "board.h"

int main(void) {
	static board_t board;
	static board_t board2;
	
	board_init(&board);
	board_print(&board);

	board_add_piece(&board, 1, 2, 3);
	board_print(&board);

	board_add_piece(&board, 1, 5, 4);
	board_print(&board);
	
	board_add_piece(&board, 1, 6, 3);
	board_print(&board);
	
	board_add_piece(&board, 1, 2, 6);

	board_add_piece(&board, 1, 4, 5);
	board_print(&board);

	printf(board_is_full(&board) ? "board is full\n" : "board is not full\n");
	
	board_copy(&board2, &board);
	board_print(&board2);
	return 0;
}
