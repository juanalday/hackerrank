// https://www.hackerrank.com/challenges/closest-numbers/problem

#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"

#include <algorithm>
#include <cmath>
#include <vector>

using ::testing::ElementsAre;

namespace {
	std::vector<int> closestNumbers(std::vector<int> arr) {
		std::vector<int> ret;
		ret.reserve(arr.size() * 2); // This can be optimized later on
		int minDiff = std::numeric_limits<int>::max();
		sort(arr.begin(), arr.end());
		for (auto it = arr.begin(); it != prev(arr.end()); ++it)
		{
			auto diff = *std::next(it) - *it; // no need for abs, since the array is sorted, it will always be positive
			if (diff < minDiff)
			{
				minDiff = diff;
				ret.clear();
			}
			if (diff == minDiff) {
				ret.push_back(*it);
				ret.push_back(*std::next(it));
			}
		}

		return ret;
	}

}

TEST(closest_numbers, example)
{
	EXPECT_THAT(closestNumbers({5, 2, 3, 4, 1}), ElementsAre(1, 2, 2, 3, 3, 4, 4, 5));
}


TEST(closest_numbers, sample)
{
	EXPECT_THAT(closestNumbers({ -20, -3916237, -357920, -3620601, 7374819, -7330761, 30, 6246457, -6461594, 266854, -520, -470 }), ElementsAre(-520, -470, -20, 30));
	EXPECT_THAT(closestNumbers({ -20, -3916237, -357920,-3620601,7374819,-7330761,30,6246457, -6461594, 266854, -520, -470 }),ElementsAre(-520, -470, -20, 30));
	EXPECT_THAT(closestNumbers({ 5, 4, 3, 2 }), ElementsAre(2, 3, 3, 4, 4, 5));
}


TEST(closest_numbers, case0)
{
	EXPECT_THAT(closestNumbers({ -20, -3916237, -357920, -3620601, 7374819, -7330761, 30, 6246457, -6461594, 266854, -520, -470 }), ElementsAre(-520, -470, -20, 30));
}

TEST(closest_numbers, case5)
{
	EXPECT_THAT(closestNumbers({ -5, 15, 25, 71, 63 }), ElementsAre(63, 71));
}
