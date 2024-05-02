//https://www.hackerrank.com/challenges/the-time-in-words/problem

#include "gtest/gtest.h"

#include <array>
#include <cmath>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <vector>

std::string time_in_words(int h, int m) {
	constexpr std::array<std::string_view, 30> const nums = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
									 "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
									 "twenty", "twenty one", "twenty two", "twenty three", "twenty four", "twenty five", "twenty six",
									 "twenty seven", "twenty eight", "twenty nine", };
	int nextHour = 1 + (h % 12);
	std::ostringstream buffer;
	if (m == 0)
		buffer << nums[h] << " o' clock";
	else if (m == 1)
		buffer << "one minute past " << nums[h];
	else if (m == 15)
		buffer << "quarter past " << nums[h];
	else if (m == 30)
		buffer << "half past " << nums[h];
	else if (m < 30)
		buffer << nums[m] << " minutes past " << nums[h];
	else if (m == 45)
		buffer << "quarter to " << nums[nextHour];
	else if (m == 59)
		buffer << "one minute to " << nums[nextHour];
	else
		buffer << nums[60 - m] << " minutes to " << nums[nextHour];

	return buffer.str();
}

TEST(time_in_words, sample_0)
{
	EXPECT_EQ("thirteen minutes to six", time_in_words(5, 47));
}

TEST(time_in_words, sample_1)
{
	EXPECT_EQ("three o' clock", time_in_words(3, 00));
}

TEST(time_in_words, sample_2)
{
	EXPECT_EQ("quarter past seven", time_in_words(7, 15));
}

TEST(time_in_words, case_2)
{
	EXPECT_EQ("twenty nine minutes past seven", time_in_words(7, 29));
}
