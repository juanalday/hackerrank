// EASY https://www.hackerrank.com/challenges/find-digits/problem

#include <gtest/gtest.h>

namespace {
	int findDigits(int n) {
		int count = 0;
		int num = n;
		while (num > 0) {
			int digit = num % 10;
			if (digit != 0 && n % digit == 0) {
				++count;
			}
			num /= 10;
		}
		return count;
	}
}

TEST(FindDigits, example)
{
	EXPECT_EQ(3, findDigits(124));
	EXPECT_EQ(3, findDigits(111));
	EXPECT_EQ(1, findDigits(10));
}

TEST(FindDigits, sample0)
{
	EXPECT_EQ(2, findDigits(12));
	EXPECT_EQ(3, findDigits(1012));
}

TEST(FindDigits, case0)
{
	EXPECT_EQ(2, findDigits(12));
	EXPECT_EQ(3, findDigits(1012));
}

TEST(FindDigits, case1)
{
	EXPECT_EQ(3, findDigits(123456789));
	EXPECT_EQ(3, findDigits(114108089));
	EXPECT_EQ(6, findDigits(110110015));
	EXPECT_EQ(2, findDigits(121));
	EXPECT_EQ(2, findDigits(33));
	EXPECT_EQ(2, findDigits(44));
	EXPECT_EQ(2, findDigits(55));
	EXPECT_EQ(2, findDigits(66));
	EXPECT_EQ(2, findDigits(77));
	EXPECT_EQ(2, findDigits(88));
	EXPECT_EQ(5, findDigits(106108048));
}
