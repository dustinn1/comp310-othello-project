#include <gtest/gtest.h>

#include "board.hh"

TEST(BoardTest, Initialization) {
	board_t* board = board_init();

	ASSERT_TRUE(board->pieces[3][3] != NULL);
	ASSERT_TRUE(board->pieces[3][4] != NULL);
}

TEST(BoardTest, Add) {
	board_t* board = board_init();

	board_add_piece(board, 'P', 2, 3);
	board_add_piece(board, 'P', 4, 5);

	ASSERT_TRUE(board->pieces[3][2] != NULL);
	ASSERT_TRUE(board->pieces[5][4] != NULL);
	ASSERT_EQ('P', board->pieces[5][4]->color);
}

TEST(BoardTest, Flip) {
	board_t* board = board_init();

	ASSERT_EQ('C', board->pieces[3][3]->color);
	ASSERT_EQ('P', board->pieces[3][4]->color);

	board_add_piece(board, 'P', 2, 3);
	board_add_piece(board, 'C', 4, 2);

	ASSERT_EQ('P', board->pieces[3][3]->color);
	ASSERT_EQ('C', board->pieces[3][4]->color);

}

TEST(BoardTest, FlipDiagonal) {
	board_t* board = board_init();
	
	board->pieces[0][0] = piece_init('C', 0, 0);
	board->pieces[1][1] = piece_init('P', 1, 1);

	board->pieces[0][6] = piece_init('P', 6, 0);
	board->pieces[1][5] = piece_init('C', 5, 1);
	
	board->pieces[6][0] = piece_init('P', 0, 6);
	board->pieces[5][1] = piece_init('C', 1, 5);
	
	board->pieces[6][6] = piece_init('C', 6, 6);
	board->pieces[5][5] = piece_init('P', 5, 5);
	
	board_add_piece(board, 'C', 2, 2);
	board_add_piece(board, 'P', 4, 2);
	board_add_piece(board, 'P', 2, 4);
	board_add_piece(board, 'C', 4, 4);

	ASSERT_EQ('C', board->pieces[1][1]->color);
	ASSERT_EQ('P', board->pieces[1][5]->color);
	ASSERT_EQ('P', board->pieces[5][1]->color);
	ASSERT_EQ('C', board->pieces[5][5]->color);
}

TEST(BoardTest, Full) {
	board_t* board = board_init();

	ASSERT_FALSE(board_is_full(board));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
