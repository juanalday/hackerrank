// MEDIUM https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>

namespace {

	std::string isValid(std::string s) {
		std::map<char, int> freqs;
		for_each(s.begin(), s.end(), [&freqs](char c) { freqs[c]++; });
		std::map<int, int> frequencyCounter;

		for (auto f : freqs) {
			if (f.second == 0)
				continue;
			frequencyCounter[f.second]++;
		}

		if (frequencyCounter.size() == 1) {
			return "YES";
		}
		else if (frequencyCounter.size() == 2) {
			auto it1 = frequencyCounter.begin();
			auto it2 = std::next(frequencyCounter.begin());

			if ((it1->first == 1 && it1->second == 1) ||
				(it2->first == 1 && it2->second == 1)) {
				return "YES";
			}

			if ((it1->first == it2->first + 1 && it1->second == 1) ||
				(it2->first == it1->first + 1 && it2->second == 1)) {
				return "YES";
			}
		}


		return "NO";

	}
}

TEST(SherlockAndValidString, example)
{
	EXPECT_EQ("YES", isValid("abc"));
	EXPECT_EQ("YES", isValid("abcc"));
	EXPECT_EQ("NO", isValid("abccc"));
}

TEST(SherlockAndValidString, sample0)
{
	EXPECT_EQ("NO", isValid("aabbcd"));
}

TEST(SherlockAndValidString, sample1)
{
	EXPECT_EQ("NO", isValid("aabbccddeefghi"));
}

TEST(SherlockAndValidString, sample2)
{
	EXPECT_EQ("YES", isValid("abcdefghhgfedecba"));
}


TEST(SherlockAndValidString, case0)
{
	EXPECT_EQ("NO", isValid("aabbcd"));
}

TEST(SherlockAndValidString, case1)
{
	EXPECT_EQ("NO", isValid("aabbccddeefghi"));
}

TEST(SherlockAndValidString, case18)
{
	EXPECT_EQ("YES", isValid("abcdefghhgfedecba"));
}
