// EASY https://www.hackerrank.com/challenges/string-construction/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>

namespace {
	int stringConstruction(std::string const& s) {
		std::map<char, int> freq;
		std::for_each(s.begin(), s.end(), [&freq](char c) { freq[c]++; });
		return static_cast<int>(freq.size());
	}
}

TEST(StringConstruction, example)
{
	EXPECT_EQ(3, stringConstruction("abcabc"));
}

TEST(StringConstruction, sample0)
{
	EXPECT_EQ(4, stringConstruction("abcd"));
	EXPECT_EQ(2, stringConstruction("abab"));
}


TEST(StringConstruction, sample1)
{
	EXPECT_EQ(4, stringConstruction("scfg"));
	EXPECT_EQ(2, stringConstruction("bccb"));
}

TEST(StringConstruction, case0)
{
	EXPECT_EQ(4, stringConstruction("abcd"));
	EXPECT_EQ(2, stringConstruction("abab"));
}


TEST(StringConstruction, case12)
{
	EXPECT_EQ(4, stringConstruction("scfg"));
	EXPECT_EQ(2, stringConstruction("bccb"));
}
