// https://www.hackerrank.com/challenges/find-the-median/problem
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
	int findMedian(std::vector<int> arr) {
		sort(arr.begin(), arr.end());
		return *next(arr.begin(), arr.size() / 2);
	}
}

TEST(findMedian, example)
{
	EXPECT_EQ(3, findMedian({ 5, 3, 1, 2, 4 }));
}

TEST(findMedian, sample0)
{
	EXPECT_EQ(3, findMedian({0, 1, 2, 4, 6, 5, 3}));
}

TEST(findMedian, case0)
{
	EXPECT_EQ(3, findMedian({ 0, 1, 2, 4, 6, 5, 3 }));
}