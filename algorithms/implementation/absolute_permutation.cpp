#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

#include <numeric>
#include <vector>

using ::testing::ElementsAre;

std::vector<int> absolutePermutationStd(int n, int k) {
	std::vector<int> data(n, 0);
	iota(data.begin(), data.end(), 1);
	if (k == 0)
		return data;

	do
	{
		auto idx(0);
		auto c = count_if(data.begin(), data.end(), [&idx, k](int value) {return std::abs(value - ++idx) == k; });
		if (c == data.size())
			return data;
	} while (std::next_permutation(data.begin(), data.end()));
	return { -1 };
}

std::vector<int> absolutePermutation(int n, int k) {
	std::vector<int> data(n, 0);
	iota(data.begin(), data.end(), 1);

	if (k == 0)
		return data;

	if ((n % 2 != 0) // Odd number of elements, return...
		|| (n % (2 * k) != 0)) // Check if n is divisible by 2k
		return { -1 };
	int counter(0);
	for_each(data.begin(), data.end(), [&counter, &k](int& number) {number = ++counter + k; if (counter % k == 0) k *= -1; });
	return data;
}

TEST(absolutePermutationStd, example)
{
	EXPECT_THAT(absolutePermutation(4, 2), ElementsAre(3, 4, 1, 2));
}

TEST(absolutePermutation, example)
{
	EXPECT_THAT(absolutePermutation(4, 2), ElementsAre(3, 4, 1, 2));
}

TEST(absolutePermutationStd, sample0)
{
	EXPECT_THAT(absolutePermutationStd(2, 1), ElementsAre(2, 1));
	EXPECT_THAT(absolutePermutationStd(3, 0), ElementsAre(1, 2, 3));
	EXPECT_THAT(absolutePermutationStd(3, 2), ElementsAre(-1));
}

TEST(absolutePermutation, sample0)
{
	EXPECT_THAT(absolutePermutation(2, 1), ElementsAre(2, 1));
	EXPECT_THAT(absolutePermutation(3, 0), ElementsAre(1, 2, 3));
	EXPECT_THAT(absolutePermutation(3, 2), ElementsAre(-1));
}

TEST(absolutePermutation, sample1)
{
	EXPECT_THAT(absolutePermutation(2, 1), ElementsAre(2, 1));
	EXPECT_THAT(absolutePermutation(10, 5), ElementsAre(6, 7, 8, 9, 10, 1, 2, 3, 4, 5));
	EXPECT_THAT(absolutePermutation(7, 5), ElementsAre(-1));
	EXPECT_THAT(absolutePermutation(2, 1), ElementsAre(2, 1));
	EXPECT_THAT(absolutePermutation(2, 0), ElementsAre(1, 2));
	EXPECT_THAT(absolutePermutation(2, 0), ElementsAre(1, 2));
	EXPECT_THAT(absolutePermutation(1, 0), ElementsAre(1));
	EXPECT_THAT(absolutePermutation(10, 5), ElementsAre(6, 7, 8, 9, 10, 1, 2, 3, 4, 5));
	EXPECT_THAT(absolutePermutation(10, 0), ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
	EXPECT_THAT(absolutePermutation(6, 0), ElementsAre(1, 2, 3, 4, 5, 6));

}

TEST(absolutePermutation, case0)
{
	EXPECT_THAT(absolutePermutation(2, 1), ElementsAre(2, 1));
	EXPECT_THAT(absolutePermutation(3, 0), ElementsAre(1, 2, 3));
	EXPECT_THAT(absolutePermutation(3, 2), ElementsAre(-1));
}

TEST(absolutePermutation, case1)
{
	EXPECT_THAT(absolutePermutation(2, 1), ElementsAre(2, 1));
	EXPECT_THAT(absolutePermutation(10, 5), ElementsAre(6, 7, 8, 9, 10, 1, 2, 3, 4, 5));
	EXPECT_THAT(absolutePermutation(7, 5), ElementsAre(-1));
	EXPECT_THAT(absolutePermutation(2, 1), ElementsAre(2, 1));
	EXPECT_THAT(absolutePermutation(2, 0), ElementsAre(1, 2));
	EXPECT_THAT(absolutePermutation(2, 0), ElementsAre(1, 2));
	EXPECT_THAT(absolutePermutation(1, 0), ElementsAre(1));
	EXPECT_THAT(absolutePermutation(10, 5), ElementsAre(6, 7, 8, 9, 10, 1, 2, 3, 4, 5));
	EXPECT_THAT(absolutePermutation(10, 0), ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
	EXPECT_THAT(absolutePermutation(6, 0), ElementsAre(1, 2, 3, 4, 5, 6));

}