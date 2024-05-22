// EASY https://www.hackerrank.com/challenges/flatland-space-stations/problem

#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

namespace {
	int flatlandSpaceStations(int n, std::vector<int> c) {

		int maxDistance(0);

		sort(c.begin(), c.end());

		for (int i = 0; i < n; ++i)
		{
			auto low = std::lower_bound(c.begin(), c.end(), i);
			int dist1 = low == c.end() ? n : *low - i;
			int dist2 = low != c.begin() ? i - *std::prev(low) : n;
			auto dist = std::min(dist1, dist2);
			maxDistance = std::max(maxDistance, dist);

		}

		return maxDistance;
	}
}


TEST(FlatlandSpaceStations, sample)
{
	EXPECT_EQ(0, flatlandSpaceStations(6, { 0, 1, 2, 4, 3, 5 }));
}

TEST(FlatlandSpaceStations, sample0)
{
	EXPECT_EQ(2, flatlandSpaceStations(5, { 0, 4 }));
}

TEST(FlatlandSpaceStations, sample1)
{
	EXPECT_EQ(0, flatlandSpaceStations(6, { 0, 1, 2, 4, 3, 5 }));
}

TEST(FlatlandSpaceStations, case0)
{
	EXPECT_EQ(2, flatlandSpaceStations(5, { 0, 4 }));
}

TEST(FlatlandSpaceStations, case1)
{
	EXPECT_EQ(0, flatlandSpaceStations(6, { 0, 1, 2, 4, 3, 5 }));
}