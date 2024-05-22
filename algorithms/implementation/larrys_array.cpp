// MEDIUM  https://www.hackerrank.com/challenges/larrys-array/problem
#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

namespace {
	std::string larrysArray(std::vector<int> const& data)
	{
		auto counter = 0;
		for (auto it1 = data.begin(); it1 != prev(data.end()); ++it1) {
			auto v1 = *it1;
			counter = accumulate(next(it1), data.end(), counter, [v1](auto innerAcc, auto v) {return innerAcc + (v1 > v ? 1 : 0); });
		};

		return counter % 2 == 0 ? "YES" : "NO";
	}

}

TEST(LarrysArray, example)
{
	EXPECT_EQ("YES", larrysArray({ 1, 6, 5, 2, 4, 3}));
}

TEST(LarrysArray, sample0)
{
	EXPECT_EQ("YES", larrysArray({ 3, 1, 2 }));
	EXPECT_EQ("YES", larrysArray({ 1, 3, 4, 2 }));
	EXPECT_EQ("NO", larrysArray({ 1, 2, 3, 5, 4 }));
}

TEST(LarrysArray, sample1)
{
	EXPECT_EQ("NO", larrysArray({ 1, 6, 5, 2, 3, 4 }));
	EXPECT_EQ("YES", larrysArray({ 3, 1, 2, 4 }));
}

TEST(LarrysArray, case0)
{
	EXPECT_EQ("YES", larrysArray({ 3, 1, 2 }));
	EXPECT_EQ("YES", larrysArray({ 1, 3 , 4, 2 }));
	EXPECT_EQ("NO", larrysArray({ 1, 2, 3, 5, 4 }));
}

TEST(LarrysArray, case21)
{
	EXPECT_EQ("NO", larrysArray({ 1, 6, 5, 2, 3, 4 }));
	EXPECT_EQ("YES", larrysArray({ 3, 1, 2, 4 }));
}
