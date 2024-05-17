// https://www.hackerrank.com/challenges/weighted-uniform-string/problem

#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;

namespace {
	std::vector<std::string> weightedUniformStrings(std::string s, std::vector<int> queries) {

		std::unordered_set<int> weights;

		int lastWeight(0);
		char prevChar = '\0';
		for (char c : s)
		{
			if (c != prevChar) {
				lastWeight = 0;
			}
			lastWeight += 1 + (c - 'a');

			weights.insert(lastWeight);
			prevChar = c;
		}

		std::vector<std::string> ret(queries.size(), "   ");
		transform(queries.begin(), queries.end(), ret.begin(), [&weights](int n) {
			return weights.count(n) ? "Yes" : "No"; });
		return ret;
	}
}

TEST(WeightedUniformStrings, example)
{
	EXPECT_THAT(weightedUniformStrings("abbcccdddd", {1, 7, 5, 4, 15}), ElementsAre("Yes", "No", "No", "Yes", "No"));
}

TEST(WeightedUniformStrings, sample0)
{
	EXPECT_THAT(weightedUniformStrings("abccddde", { 1, 3, 12, 5, 9, 10}), ElementsAre("Yes", "Yes", "Yes", "Yes", "No", "No"));
}


TEST(WeightedUniformStrings, case0)
{
	EXPECT_THAT(weightedUniformStrings("abccddde", { 1, 3, 12, 5, 9, 10 }), ElementsAre("Yes", "Yes", "Yes", "Yes", "No", "No"));
}

TEST(WeightedUniformStrings, case31)
{
	EXPECT_THAT(weightedUniformStrings("aaabbbbcccddd", {9, 7, 8, 12, 5 }), ElementsAre("Yes", "No", "Yes", "Yes", "No"));
}
