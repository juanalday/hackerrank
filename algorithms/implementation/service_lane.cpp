// EASY https://www.hackerrank.com/challenges/service-lane/problem

#include "gtest/gtest.h"
#include <gmock/gmock-matchers.h>

#include <algorithm>
#include <vector>

using ::testing::ElementsAre;

namespace {
	std::vector<int> serviceLane(std::vector<int> const& width, std::vector<std::vector<int>> const& cases) {
		std::vector<int> ret(cases.size());
		std::transform(cases.begin(), cases.end(), ret.begin(),
			[&width](auto const& c) {return *std::min_element(std::next(width.begin(), c.front()), std::next(width.begin(), c.back() +1)); });
		return ret;
	}
}

TEST(ServiceLane, example)
{
	EXPECT_THAT(serviceLane({ 2, 3, 2, 1 }, { {1,2}, {2, 3} }), ElementsAre(2, 1));
}

TEST(ServiceLane, sample0)
{
	EXPECT_THAT(serviceLane({ 2, 3, 1, 2, 3, 2, 3, 3 }, { {0,3}, {4, 6}, {6,7}, {3,5}, {0,7} }), ElementsAre(1, 2, 3, 2, 1));
}

TEST(ServiceLane, sample1)
{
	EXPECT_THAT(serviceLane({ 1, 2, 2, 2, 1 }, { {2,3}, {1,4}, {2,4}, {2,4}, {2,3} }), ElementsAre(2, 1, 1, 1, 2));
}

TEST(ServiceLane, case0)
{
	EXPECT_THAT(serviceLane({ 2, 3, 1, 2, 3, 2, 3, 3 }, { {0,3}, {4, 6}, {6,7}, {3,5}, {0,7} }), ElementsAre(1, 2, 3, 2, 1));
}

TEST(ServiceLane, case1)
{
	EXPECT_THAT(serviceLane({ 1, 2, 2, 2, 1 }, { {2,3}, {1,4}, {2,4}, {2,4}, {2,3} }), ElementsAre(2, 1, 1, 1, 2));
}
