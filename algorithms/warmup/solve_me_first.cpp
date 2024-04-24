#include "gtest/gtest.h"

int solveMeFirst(int a, int b) {
	return a + b;
}

TEST(solveMeFirst, sample)
{
	EXPECT_EQ(5, solveMeFirst(2, 3));
}
TEST(solveMeFirst, case_0)
{
	EXPECT_EQ(5, solveMeFirst(2, 3));
}

TEST(solveMeFirst, case_1)
{
	EXPECT_EQ(1100, solveMeFirst(100, 1000));
}