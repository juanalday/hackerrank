// EASY https://www.hackerrank.com/challenges/fair-rations/problem

#include "gtest/gtest.h"

#include <algorithm>
#include <string>
#include <vector>

namespace {
	std::string fairRations(std::vector<int> const& B) {
		std::vector<int> rations(B);
		int counter(0);
		for (auto it = rations.begin(); it != std::prev(rations.end()); ++it)
		{
			if (*it % 2 == 1)
			{
				(*it)++;
				(*std::next(it))++;
				counter += 2;
			}
		}
		if (rations.back() % 2 == 1)
			return "NO";
		else
			return std::to_string(counter);
	}
}

TEST(FairRations, example)
{
	EXPECT_EQ("4", fairRations({4, 5, 6, 7}));
}

TEST(FairRations, sample0)
{
	EXPECT_EQ("4", fairRations({ 2, 3, 4, 5, 6 }));
}

TEST(FairRations, sample1)
{
	EXPECT_EQ("NO", fairRations({ 1, 2 }));
}


TEST(FairRations, case_0)
{
	EXPECT_EQ("4", fairRations({ 2, 3, 4, 5, 6}));
}
