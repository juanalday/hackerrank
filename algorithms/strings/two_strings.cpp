// EASY https://www.hackerrank.com/challenges/two-strings/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>

namespace {
	std::string twoStrings(std::string s1, std::string s2) {
		std::map<char, int> freq;
		for_each(s1.begin(), s1.end(), [&freq](char c) { freq[c]++; });
		for (auto c : s2)
		{
			if (freq.find(c) != freq.end())
			{
				return "YES";
			}
		}
		return "NO";
	}
}

TEST(TwoStrings, example)
{
	EXPECT_EQ("YES", twoStrings("and", "art"));
	EXPECT_EQ("NO", twoStrings("be", "cat"));
}

TEST(TwoStrings, sample0)
{
	EXPECT_EQ("YES", twoStrings("hello", "world"));
	EXPECT_EQ("NO", twoStrings("hi", "world"));
}

TEST(TwoStrings, sample1)
{
	EXPECT_EQ("NO", twoStrings("wouldyoulikefries", "abcabcabcabcabcabc"));
	EXPECT_EQ("YES", twoStrings("hackerrankcommunity", "cdecdecdecde"));
	EXPECT_EQ("YES", twoStrings("jackandjill", "wentupthehill"));
	EXPECT_EQ("NO", twoStrings("writetoyourparents", "fghmqzldbc"));

}

TEST(TwoStrings, sample2)
{
	EXPECT_EQ("YES", twoStrings("aardvark", "apple"));
	EXPECT_EQ("NO", twoStrings("beetroot", "sandals"));
}


TEST(TwoStrings, case0)
{
	EXPECT_EQ("YES", twoStrings("hello", "world"));
	EXPECT_EQ("NO", twoStrings("hi", "world"));
}

TEST(TwoStrings, case6)
{
	EXPECT_EQ("NO", twoStrings("wouldyoulikefries", "abcabcabcabcabcabc"));
	EXPECT_EQ("YES", twoStrings("hackerrankcommunity", "cdecdecdecde"));
	EXPECT_EQ("YES", twoStrings("jackandjill", "wentupthehill"));
	EXPECT_EQ("NO", twoStrings("writetoyourparents", "fghmqzldbc"));

}

TEST(TwoStrings, case7)
{
	EXPECT_EQ("YES", twoStrings("aardvark", "apple"));
	EXPECT_EQ("NO", twoStrings("beetroot", "sandals"));
}
