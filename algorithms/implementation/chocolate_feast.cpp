// EASY https://www.hackerrank.com/challenges/chocolate-feast/problem

#include "gtest/gtest.h"


namespace {
	int chocolateFeast(int n, int c, int m) {
		int bars = n / c;
		int wrappers = bars;

		while (wrappers >= m)
		{
			int newBars = wrappers / m;
			wrappers = newBars + wrappers % m;
			bars += newBars;
		}

		return bars;
	}

}
TEST(ChocolateFeast, example)
{
	EXPECT_EQ(9, chocolateFeast(15, 3, 2));
}

TEST(ChocolateFeast, sample0)
{
	EXPECT_EQ(6, chocolateFeast(10, 2, 5));
	EXPECT_EQ(3, chocolateFeast(12, 4, 4));
	EXPECT_EQ(5, chocolateFeast(6, 2, 2));
}

TEST(ChocolateFeast, sample1)
{
	EXPECT_EQ(3, chocolateFeast(7, 3, 2));
}

TEST(ChocolateFeast, case0)
{
	EXPECT_EQ(6, chocolateFeast(10, 2, 5));
	EXPECT_EQ(3, chocolateFeast(12, 4, 4));
	EXPECT_EQ(5, chocolateFeast(6, 2, 2));
}

TEST(ChocolateFeast, case10)
{
	EXPECT_EQ(3, chocolateFeast(7, 3, 2));
}

