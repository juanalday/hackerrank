// https://www.hackerrank.com/challenges/hackerrank-in-a-string/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace {
	std::string hackerrankInString(std::string s) {
		std::string const tokens{ "hackerrank" };

		auto it = s.begin();
		for (auto token : tokens)
		{
			it = std::find(it, s.end(), token);
			if (it == s.end())
				return "NO";
			++it;
		}
		return "YES";
	}
}

TEST(HackerrankInString, example)
{
	EXPECT_EQ("YES", hackerrankInString("haacckkerrannkk"));
	EXPECT_EQ("NO", hackerrankInString("haacckkerannk"));
	EXPECT_EQ("NO", hackerrankInString("hccaakkerrannkk"));
}

TEST(HackerrankInString, sample0)
{
	EXPECT_EQ("YES", hackerrankInString("hereiamstackerrank"));
	EXPECT_EQ("NO", hackerrankInString("hackerworld"));
}

TEST(HackerrankInString, sample1)
{
	EXPECT_EQ("YES", hackerrankInString("hhaacckkekraraannk"));
	EXPECT_EQ("NO", hackerrankInString("rhbaasdndfsdskgbfefdbrsdfhuyatrjtcrtyytktjjt"));
}

TEST(HackerrankInString, case0)
{
	EXPECT_EQ("YES", hackerrankInString("hereiamstackerrank"));
	EXPECT_EQ("NO", hackerrankInString("hackerworld"));
}

TEST(HackerrankInString, case3)
{
	EXPECT_EQ("YES", hackerrankInString("hhaacckkekraraannk"));
	EXPECT_EQ("NO", hackerrankInString("rhbaasdndfsdskgbfefdbrsdfhuyatrjtcrtyytktjjt"));
}