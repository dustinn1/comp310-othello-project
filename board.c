#include "board.h"

#include "piece.h"

void board_init(*board_t board) {
	board->pieces[3][3] = piece_init(0, 3, 3);
	board->pieces[3][4] = piece_init(1, 4, 3);
	board->pieces[4][3] = piece_init(0, 3, 4);
	board->pieces[4][4] = piece_init(1, 4, 4);
}

bool board_full(*board_t board) {
	return board->isFull;
}
