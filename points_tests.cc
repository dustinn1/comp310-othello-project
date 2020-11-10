#include <gtest/gtest.h>

#include "points.hh"

TEST(PointTest, Initialization) {
	point_t* point;
	point_t* point2;

	point = point_init(3, 5);
	point2 = point_init(2, 7);

	ASSERT_EQ(3, point->x);
	ASSERT_EQ(5, point->y);
	ASSERT_EQ(2, point2->x);
	ASSERT_EQ(7, point2->y);
}

TEST(PointsTest, Contains) {
	point_t* points[3];

	points[0] = point_init(3, 5);
	points[1] = point_init(2, 7);
	points[2] = point_init(0, 0);

	ASSERT_TRUE(points_contains(points, 3, 5));
	ASSERT_TRUE(points_contains(points, 0, 0));
	ASSERT_TRUE(points_contains(points, 2, 7));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
