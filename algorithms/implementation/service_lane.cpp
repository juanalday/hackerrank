#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

std::vector<int> serviceLane(std::vector<int> const& width, std::vector<std::vector<int>> const& cases) {
	std::vector<int> ret(width.size());
	std::transform(cases.begin(), cases.end(), ret.begin(), 
		[&width](auto const& c){return *std::min_element(std::next(width.begin(), c[0]), std::next(width.begin(), 1+c[1])); });
	return ret;
}

TEST(serviceLane, sample)
{
	EXPECT_EQ(std::vector<int>({1, 2, 3, 2, 1}), serviceLane({ 2, 3, 1, 2, 3, 2, 3, 3 }, { {0,3}, {4, 6}, {6,7}, {3,5}, {0,7} }));
}

TEST(serviceLane, case_0)
{
	EXPECT_EQ(std::vector<int>({ 1, 2, 3, 2, 1 }), serviceLane({ 2, 3, 1, 2, 3, 2, 3, 3 }, { {0,3}, {4, 6}, {6,7}, {3,5}, {0,7} }));
}

TEST(serviceLane, case_1)
{
	EXPECT_EQ(std::vector<int>({ 2, 1, 1, 1, 2 }), serviceLane({ 1, 2, 2, 2, 1 }, { {2,3}, {1,4}, {2,4}, {2,4}, {2,3} }));
}