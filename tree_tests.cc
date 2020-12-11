#include <gtest/gtest.h>

#include "tree.hh"

TEST(TreeTest, Create) {
	board_t* board = board_init();
	board_add_piece(board, 'P', 2, 3);

	node_t* root = node_init(board);
    tree_create(root, 3);
}

TEST(TreeTest, GetMax) {
	board_t* board = board_init();
	board_add_piece(board, 'P', 2, 3);

	node_t* root = node_init(board);
    tree_create(root, 5);
	node_t* max = tree_get_max(root, 5);
	ASSERT_EQ(2, max->firstPieceAdded.x);
	ASSERT_EQ(2, max->firstPieceAdded.y);
	ASSERT_EQ(18, max->value);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
