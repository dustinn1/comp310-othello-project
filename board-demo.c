#include "board.h"
#include "piece.h"

int main(void) {
	static board_t board;
	static board_t board2;
	
	board_init(&board);
	board_print(&board);
	printf("\n");
	board_add_piece(&board, 1, 2, 3);
	board_print(&board);
	//board_copy(&board2, &board);
	//printf("\n");
	//board_print(&board2);
	return 0;
}
