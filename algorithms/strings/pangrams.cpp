// https://www.hackerrank.com/challenges/hackerrank-in-a-string/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <numeric>
#include <string>

namespace {
	std::string pangrams(std::string s) {
		constexpr size_t numLetters = 26;
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
		sort(s.begin(), s.end());
		s.erase(std::unique(s.begin(), s.end()), s.end());
		return s.size() == 1 + numLetters ? "pangram" : "not pangram";
	}
}

TEST(pangrams, example)
{
	EXPECT_EQ("pangram", pangrams("The quick brown fox jumps pver the lazy dog"));
}

TEST(pangrams, sample0)
{
	EXPECT_EQ("pangram",     pangrams("We promptly judged antique ivory buckles for the next prize"));
}

TEST(pangrams, sample1)
{
	EXPECT_EQ("not pangram", pangrams("We promptly judged antique ivory buckles for the prize"));
}


TEST(pangrams, case0)
{
	EXPECT_EQ("pangram", pangrams("We promptly judged antique ivory buckles for the next prize"));
}

TEST(pangrams, case1)
{
	EXPECT_EQ("not pangram", pangrams("We promptly judged antique ivory buckles for the prize"));
}
