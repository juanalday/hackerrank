#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>


namespace {
	int sortedSum(std::vector<int> nums) {

		std::vector<int> tmp(nums); // Just so that I have enough space
		long ret = 0;
		for (auto it = nums.begin(); it != nums.end(); ++it)
		{
			tmp.clear();
			tmp.insert(tmp.end(), nums.begin(), next(it));
			sort(tmp.begin(), tmp.end());
			ret += std::accumulate(tmp.begin(), tmp.end(), 0, [idx = 0](int acc, int elem) mutable {return acc + (++idx * elem); });
		}
		return ret % 1000000007;
	}
}


TEST(sortedSums, example)
{
	EXPECT_EQ(65, sortedSum({ 4, 3, 2, 1 }));
}

TEST(sortedSums, sample0)
{
	EXPECT_EQ(80, sortedSum({ 9, 5, 8 }));
}

TEST(sortedSums, sample1)
{
	EXPECT_EQ(28, sortedSum({ 5, 9 }));
}

TEST(sortedSums, case0)
{
	EXPECT_EQ(80, sortedSum({ 9, 5, 8 }));
}

TEST(sortedSums, case1)
{
	EXPECT_EQ(28, sortedSum({ 5, 9 }));
}

TEST(sortedSums, case2)
{
	EXPECT_EQ(364271696, sortedSum({ 747402, 380408, 605449, 846906, 385224, 31431, 677517, 770001, 389085, 40373, 487560, 886252, 596334, 59083 }));
}


TEST(sortedSums, case3)
{
	EXPECT_EQ(132805734, sortedSum({ 552565, 251358, 612259, 542802, 12194, 345248, 290765, 232501, 391793, 107191, 726097 }));
}


TEST(sortedSums, case4)
{
	EXPECT_EQ(160569914, sortedSum({ 989605, 554335, 938146, 420327, 573599, 674780, 226418, 80001, 589043, 194195 }));
}


TEST(sortedSums, case5)
{
	EXPECT_EQ(344134692, sortedSum({ 542169, 805692, 66757, 479481, 585792, 20027, 517182, 312501, 497188, 817738, 709039, 983570, 397053, 176499 }));
}

TEST(sortedSums, case6)
{
	EXPECT_EQ(145945368, sortedSum({ 726610, 5429, 998092, 203911, 48773, 897342, 163057, 930001, 83522, 945114 }));
}

