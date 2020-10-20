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

	board_add_piece(&board, 1, 2, 3);
	board_add_piece(&board, 1, 4, 5);

	ASSERT_TRUE(board.pieces[3][2] != NULL);
	ASSERT_TRUE(board.pieces[5][4] != NULL);
	ASSERT_EQ(1, board.pieces[5][4]->color);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
