// https://www.hackerrank.com/challenges/jumping-rooks/problem

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {
	int jumpingRooks(int k, std::vector<std::string> board) {
		return 0;
	}
}

TEST(jumpingRooks, DISABLED_sample0)
{
	EXPECT_EQ(2, jumpingRooks(4, { "...", "...", "..." }));
}

TEST(jumpingRooks, DISABLED_sample1)
{
	EXPECT_EQ(4, jumpingRooks(4, { "..#..", "..#..", "#####", "..#..", "..#.."}));
}