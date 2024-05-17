// https://www.hackerrank.com/challenges/mars-exploration/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace {
	int marsExploration(std::string s) {

		int counter(0);
		for (auto i = 0; i < s.size(); ++i)
		{
			if (i % 3 == 1)
			{
				counter += (s[i] == 'O') ? 0 : 1;
			}
			else
				counter += (s[i] == 'S') ? 0 : 1;
		}
		return counter;
	}
}

TEST(MarsExploration, example)
{
	EXPECT_EQ(2, marsExploration("SOSTOT"));
}

TEST(MarsExploration, sample0)
{
	EXPECT_EQ(3, marsExploration("SOSSPSSQSSOR"));
}

TEST(MarsExploration, sample1)
{
	EXPECT_EQ(1, marsExploration("SOSSOT"));
}

TEST(MarsExploration, sample2)
{
	EXPECT_EQ(0, marsExploration("SOSSOSSOS"));
}

TEST(MarsExploration, case0)
{
	EXPECT_EQ(3, marsExploration("SOSSPSSQSSOR"));
}

TEST(MarsExploration, case1)
{
	EXPECT_EQ(1, marsExploration("SOSSOT"));
}

TEST(MarsExploration, case11)
{
	EXPECT_EQ(0, marsExploration("SOSSOSSOS"));
}
