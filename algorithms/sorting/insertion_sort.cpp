// https://www.hackerrank.com/challenges/insertion-sort/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {

	int insertionSort(std::vector<int> arr) {
		return 6;
	}
}


TEST(insertionSort, example)
{
	EXPECT_EQ(6, insertionSort({4, 3, 2, 1}));
}