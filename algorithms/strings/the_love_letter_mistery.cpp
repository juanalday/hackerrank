// https://www.hackerrank.com/challenges/the-love-letter-mystery/problem

#include <gtest/gtest.h>

namespace {

	int theLoveLetterMystery(std::string s) {
		int ret(0);
		auto left = s.begin();
		auto right = prev(s.end());

		while (left < right)
		{
			if (*left != *right)
			{
				ret += std::abs(*left - *right);
			}
			++left;
			--right;
		}
		return ret;
	}

}

TEST(TheLoveLetterMystery, example)
{
	EXPECT_EQ(2, theLoveLetterMystery("cde"));
}


TEST(TheLoveLetterMystery, sample0)
{
	EXPECT_EQ(2, theLoveLetterMystery("abc"));
	EXPECT_EQ(0, theLoveLetterMystery("abcba"));
	EXPECT_EQ(4, theLoveLetterMystery("abcd"));
	EXPECT_EQ(2, theLoveLetterMystery("cba"));
}

TEST(TheLoveLetterMystery, sample1)
{
	EXPECT_EQ(6, theLoveLetterMystery("lmnop"));
	EXPECT_EQ(36, theLoveLetterMystery("adslkfjas"));
	EXPECT_EQ(13, theLoveLetterMystery("bafhaef"));
	EXPECT_EQ(40, theLoveLetterMystery("ofrhase"));
}

TEST(TheLoveLetterMystery, case0)
{
	EXPECT_EQ(2, theLoveLetterMystery("abc"));
	EXPECT_EQ(0, theLoveLetterMystery("abcba"));
	EXPECT_EQ(4, theLoveLetterMystery("abcd"));
	EXPECT_EQ(2, theLoveLetterMystery("cba"));
}

TEST(TheLoveLetterMystery, case12)
{
	EXPECT_EQ(6, theLoveLetterMystery("lmnop"));
	EXPECT_EQ(36, theLoveLetterMystery("adslkfjas"));
	EXPECT_EQ(13, theLoveLetterMystery("bafhaef"));
	EXPECT_EQ(40, theLoveLetterMystery("ofrhase"));
}
