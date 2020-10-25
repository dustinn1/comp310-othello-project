#include "board.h"

int main(void) {
	static board_t board;
	
	board_init(&board);
	board_print(&board);
/*
	board_add_piece(&board, 'W', 4, 2);
	board_print(&board);
*/	
	board_add_piece(&board, 'B', 2, 3);
	board_print(&board);

	static board_t board2;
	board2.pieces[0][0] = piece_init('W', 0, 0);
	board2.pieces[1][1] = piece_init('B', 1, 1);
	
	board2.pieces[0][6] = piece_init('B', 6, 0);
	board2.pieces[1][5] = piece_init('W', 5, 1);
	
	board2.pieces[6][0] = piece_init('B', 0, 6);
	board2.pieces[5][1] = piece_init('W', 1, 5);
	
	board2.pieces[6][6] = piece_init('W', 6, 6);
	board2.pieces[5][5] = piece_init('B', 5, 5);
	
	board_print(&board2);

	board_add_piece(&board2, 'W', 2, 2);
	board_add_piece(&board2, 'B', 4, 2);
	board_add_piece(&board2, 'B', 2, 4);
	board_add_piece(&board2, 'W', 4, 4);
	board_print(&board2);

	return 0;
}
