// https://www.hackerrank.com/challenges/camelcase/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <string>

namespace {
	int camelcase(std::string s) {
		auto n = 1 + count_if(s.begin(), s.end(), [](auto c) {return std::isupper(c); });
		
		return static_cast<int>(n);
	}
}

TEST(camelcase, example)
{
	EXPECT_EQ(3, camelcase("oneTwoThree"));
}

TEST(camelcase, sample)
{
	EXPECT_EQ(5, camelcase("saveChangesInTheEditor"));
}

TEST(camelcase, case0)
{
	EXPECT_EQ(5, camelcase("saveChangesInTheEditor"));
}

TEST(camelcase, case5)
{
	EXPECT_EQ(1, camelcase("abcd"));
}


