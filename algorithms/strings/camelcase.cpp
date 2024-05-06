// https://www.hackerrank.com/challenges/camelcase/problem

#include <gtest/gtest.h>

#include <string>

namespace {
	int camelcase(std::string s) {
		return 0;
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

