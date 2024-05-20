// EASY https://www.hackerrank.com/challenges/alternating-characters/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace {
	int alternatingCharacters(std::string s) {
		bool nextShouldBeA = s[0] == 'A' ? true : false;
		int ret(0);
		for (auto x : s)
		{
			if ((nextShouldBeA && x == 'B') || (!nextShouldBeA && x == 'A'))
				++ret;
			else
				nextShouldBeA ^= true;
		}
		return ret;
	}
}

TEST(AlternatingCharacters, example) {
	EXPECT_EQ(2, alternatingCharacters("AABAAD"));
}

TEST(AlternatingCharacters, sample0) {
	EXPECT_EQ(3, alternatingCharacters("AAAA"));
	EXPECT_EQ(4, alternatingCharacters("BBBBB"));
	EXPECT_EQ(0, alternatingCharacters("ABABABAB"));
	EXPECT_EQ(0, alternatingCharacters("BABABA"));
	EXPECT_EQ(4, alternatingCharacters("AAABBB"));
}

TEST(AlternatingCharacters, sample1) {
	EXPECT_EQ(6, alternatingCharacters("AAABBBAABB"));
	EXPECT_EQ(4, alternatingCharacters("AABBAABB"));
	EXPECT_EQ(1, alternatingCharacters("ABABABAA"));
}

TEST(AlternatingCharacters, sample2) {
	EXPECT_EQ(3, alternatingCharacters("ABBABBAA"));
}

TEST(AlternatingCharacters, case0) {
	EXPECT_EQ(3, alternatingCharacters("AAAA"));
	EXPECT_EQ(4, alternatingCharacters("BBBBB"));
	EXPECT_EQ(0, alternatingCharacters("ABABABAB"));
	EXPECT_EQ(0, alternatingCharacters("BABABA"));
	EXPECT_EQ(4, alternatingCharacters("AAABBB"));
}

TEST(AlternatingCharacters, case13) {
	EXPECT_EQ(6, alternatingCharacters("AAABBBAABB"));
	EXPECT_EQ(4, alternatingCharacters("AABBAABB"));
	EXPECT_EQ(1, alternatingCharacters("ABABABAA"));
}

TEST(AlternatingCharacters, case14) {
	EXPECT_EQ(3, alternatingCharacters("ABBABBAA"));
}
