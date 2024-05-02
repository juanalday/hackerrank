// https://www.hackerrank.com/challenges/correctness-invariant/problem

#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"

#include <vector>

using ::testing::ElementsAre;

std::vector<int> insertionSort(std::vector<int> arr) {
	int i, j;
	int value;
	int N = static_cast<int>(arr.size());
	for (i = 1; i < N; i++)
	{
		value = arr[i];
		j = i - 1;
		while (j >= 0 && value < arr[j]) // changed to j>=0
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = value;
	}
	return arr;
}

TEST(correctnessInvariant, sample)
{
	EXPECT_THAT(insertionSort({ 7, 4, 3, 5, 6, 2 }), ElementsAre(2, 3, 4, 5, 6, 7));
}

TEST(correctnessInvariant, case0)
{
	EXPECT_THAT(insertionSort({ 4, 1, 3, 5, 6, 2 }), ElementsAre(1, 2, 3, 4, 5, 6));
}