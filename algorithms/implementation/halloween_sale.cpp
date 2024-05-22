// EASY https://www.hackerrank.com/challenges/halloween-sale/problem

#include "gtest/gtest.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace {
	int howManyGames(int p, int d, int m, int s) {

		int counter(0);
		int price = p;
		while (s > 0)
		{
			if (s < price)
				break;
			++counter;
			s -= price;
			price = std::max(price - d, m);
		}
		return counter;
	}
}

TEST(HalloweenSale, example)
{
	EXPECT_EQ(5, howManyGames(20, 3, 6, 70));
	
}

TEST(HalloweenSale, sample0)
{
	EXPECT_EQ(6, howManyGames(20, 3, 6, 80));
}

TEST(HalloweenSale, sample1)
{
	EXPECT_EQ(7, howManyGames(20, 3, 6, 85));
}

TEST(HalloweenSale, case0)
{
	EXPECT_EQ(5, howManyGames(20, 3, 6, 70));
}

TEST(howManyGames, case1)
{
	EXPECT_EQ(7, howManyGames(20, 3, 6, 85));
}
