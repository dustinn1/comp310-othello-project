#include <gtest/gtest.h>

#include "board.hh"

TEST(BoardTest, Initialization) {
	static board_t board;

	board_init(&board);

	ASSERT_TRUE(board.pieces[3][3] != NULL);
	ASSERT_TRUE(board.pieces[3][4] != NULL);
}

TEST(BoardTest, Add) {
	static board_t board;

	board_init(&board);

	board_add_piece(&board, 'B', 2, 3);
	board_add_piece(&board, 'B', 4, 5);

	ASSERT_TRUE(board.pieces[3][2] != NULL);
	ASSERT_TRUE(board.pieces[5][4] != NULL);
	ASSERT_EQ('B', board.pieces[5][4]->color);
}

TEST(BoardTest, Flip) {
	static board_t board;

	board_init(&board);

	ASSERT_EQ('W', board.pieces[3][3]->color);
	ASSERT_EQ('B', board.pieces[3][4]->color);

	board_add_piece(&board, 'B', 2, 3);
	board_add_piece(&board, 'W', 4, 2);

	ASSERT_EQ('B', board.pieces[3][3]->color);
	ASSERT_EQ('W', board.pieces[3][4]->color);

}

TEST(BoardTest, FlipDiagonal) {
	static board_t board;

	board_init(&board);
	
	board.pieces[0][0] = piece_init('W', 0, 0);
	board.pieces[1][1] = piece_init('B', 1, 1);

	board.pieces[0][6] = piece_init('B', 6, 0);
	board.pieces[1][5] = piece_init('W', 5, 1);
	
	board.pieces[6][0] = piece_init('B', 0, 6);
	board.pieces[5][1] = piece_init('W', 1, 5);
	
	board.pieces[6][6] = piece_init('W', 6, 6);
	board.pieces[5][5] = piece_init('B', 5, 5);
	
	board_add_piece(&board, 'W', 2, 2);
	board_add_piece(&board, 'B', 4, 2);
	board_add_piece(&board, 'B', 2, 4);
	board_add_piece(&board, 'W', 4, 4);

	ASSERT_EQ('W', board.pieces[1][1]->color);
	ASSERT_EQ('B', board.pieces[1][5]->color);
	ASSERT_EQ('B', board.pieces[5][1]->color);
	ASSERT_EQ('W', board.pieces[5][5]->color);
}

TEST(BoardTest, Full) {
	static board_t board;

	board_init(&board);

	ASSERT_FALSE(board_is_full(&board));

	// implement test for if full -- can only think of adding 60 pieces at the momement
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
