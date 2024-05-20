// EASY https://www.hackerrank.com/challenges/funny-string/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <string>

namespace {
	std::string funnyString(std::string s) {
		std::vector<int> diffs(s.size() , 0);
		std::vector<int> rdiffs(s.size(), 0);
		std::adjacent_difference(s.begin(), s.end(), diffs.begin(), [](auto v1, auto v2){return std::abs(v1 - v2);});
		std::adjacent_difference(s.rbegin(), s.rend(), rdiffs.begin(), [](auto v1, auto v2) {return std::abs(v1 - v2); });
		diffs[0] = rdiffs[0] = 0;
		return (diffs == rdiffs) ? "Funny" :"Not Funny";
	}
}

TEST(FunnyString, example) {
	EXPECT_EQ("Funny", funnyString("lmnop"));
}

TEST(FunnyString, sample0) {
	EXPECT_EQ("Funny", funnyString("acxz"));
	EXPECT_EQ("Not Funny", funnyString("bcxz"));
}

TEST(FunnyString, sample1) {
	EXPECT_EQ("Not Funny", funnyString("ivvkxq"));
	EXPECT_EQ("Not Funny", funnyString("ivvkx"));
}

TEST(FunnyString, case0) {
	EXPECT_EQ("Funny", funnyString("acxz"));
	EXPECT_EQ("Not Funny", funnyString("bcxz"));
}

TEST(FunnyString, case1) {
	EXPECT_EQ("Not Funny", funnyString("ivvkxq"));
	EXPECT_EQ("Not Funny", funnyString("ivvkx"));
}
