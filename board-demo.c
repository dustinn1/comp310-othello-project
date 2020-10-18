#include "board.h"
#include "piece.h"

int main(void) {
	static board_t board;
	
	board_init(&board);
	board_print(&board);
	return 0;
}
