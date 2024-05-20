// EASY https://www.hackerrank.com/challenges/pangrams/problem

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

TEST(Pangrams, example)
{
	EXPECT_EQ("pangram", pangrams("The quick brown fox jumps pver the lazy dog"));
}

TEST(Pangrams, sample0)
{
	EXPECT_EQ("pangram",     pangrams("We promptly judged antique ivory buckles for the next prize"));
}

TEST(Pangrams, sample1)
{
	EXPECT_EQ("not pangram", pangrams("We promptly judged antique ivory buckles for the prize"));
}


TEST(Pangrams, case0)
{
	EXPECT_EQ("pangram", pangrams("We promptly judged antique ivory buckles for the next prize"));
}

TEST(Pangrams, case1)
{
	EXPECT_EQ("not pangram", pangrams("We promptly judged antique ivory buckles for the prize"));
}
