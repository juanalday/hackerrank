//https://www.hackerrank.com/challenges/quicksort1/problem

#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"

#include <vector>

using ::testing::ElementsAre;

std::vector<int> quickSort(std::vector<int> arr) {
	auto pivot = *arr.begin();
	auto it1 = next(arr.begin());
	for (auto it2 = it1; it2 != arr.end(); ++it2)
	{
		if (*it2 < pivot)
		{
			iter_swap(it1++, it2);
		}
	}
	// Let's move the pivot where it belongs
	iter_swap(arr.begin(), prev(it1));
	return arr;

}


TEST(quickSort, example)
{
	EXPECT_THAT(quickSort({5, 7, 4, 3, 8}), ElementsAre(3, 4, 5, 7, 8));
}

TEST(quickSort, sample0)
{
	EXPECT_THAT(quickSort({ 4, 5, 3, 7, 2 }), ElementsAre(2, 3, 4, 7, 5));
}

TEST(quickSort, case0)
{
	EXPECT_THAT(quickSort({ 4, 5, 3, 7, 2 }), ElementsAre(2, 3, 4, 7, 5));
}