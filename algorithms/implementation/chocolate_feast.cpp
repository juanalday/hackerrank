#include "gtest/gtest.h"


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

TEST(chocolateFeast, example)
{
	EXPECT_EQ(9, chocolateFeast(15, 3, 2));
}

TEST(chocolateFeast, sample)
{
	EXPECT_EQ(6, chocolateFeast(10, 2, 5));
	EXPECT_EQ(3, chocolateFeast(12, 4, 4));
	EXPECT_EQ(5, chocolateFeast(6, 2, 2));
}
