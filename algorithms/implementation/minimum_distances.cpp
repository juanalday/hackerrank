// EASY https://www.hackerrank.com/challenges/minimum-distances/problem

#include "gtest/gtest.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace {
	int minimumDistances(std::vector<int> const& a) {
		std::unordered_map<int, int> indexes; //number to index of last ocurrence
		int minDistance = std::numeric_limits<int>::max();
		for (int i = 0; i < a.size(); ++i)
		{
			if (indexes.find(a[i]) != indexes.end()) {
				auto distance = i - indexes[a[i]];
				if (distance < minDistance) {
					minDistance = distance;
				}
			}
			indexes[a[i]] = i;
		}
		return minDistance == std::numeric_limits<int>::max() ? -1 : minDistance;
	}
}

TEST(MinimumDistances, example)
{
	EXPECT_EQ(2, minimumDistances({ 3, 2, 1, 2, 3 }));
}

TEST(MinimumDistances, sample0)
{
	EXPECT_EQ(3, minimumDistances({ 7, 1, 3, 4, 1, 7}));
}

TEST(MinimumDistances, sample1)
{
	EXPECT_EQ(-1, minimumDistances({ 1, 2, 3, 4, 10 }));
}

TEST(MinimumDistances, case0)
{
	EXPECT_EQ(3, minimumDistances({ 7, 1, 3, 4, 1, 7 }));
}

TEST(MinimumDistances, case1)
{
	EXPECT_EQ(-1, minimumDistances({ 1, 2, 3, 4, 10 }));
}
