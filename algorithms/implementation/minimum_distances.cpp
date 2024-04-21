#include "gtest/gtest.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

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

TEST(minimumDistances, example)
{
	EXPECT_EQ(2, minimumDistances({ 3, 2, 1, 2, 3 }));
}

TEST(minimumDistances, sample)
{
	EXPECT_EQ(3, minimumDistances({ 7, 1, 3, 4, 1, 7}));
}

TEST(minimumDistances, case_0)
{
	EXPECT_EQ(3, minimumDistances({ 7, 1, 3, 4, 1, 7 }));
}

TEST(minimumDistances, case_1)
{
	EXPECT_EQ(-1, minimumDistances({ 1, 2, 3, 4, 10 }));
}
