// EASY https://www.hackerrank.com/challenges/anagram/problem?

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

namespace {
	int anagram(std::string s) {

		if (s.size() % 2 == 1)
			return -1;
		auto const itMid = next(s.begin(), s.size() / 2);
		std::sort(s.begin(), itMid);
		std::sort(itMid, s.end());
		std::vector<char> tmp;
		std::set_difference(s.begin(), itMid, itMid, s.end(), std::back_inserter(tmp));
		return static_cast<int>(tmp.size());
	}
}

TEST(Anagram, example)
{
	EXPECT_EQ(3, anagram("abcdef"));
	EXPECT_EQ(2, anagram("abccde"));
}

TEST(Anagram, sample0)
{
	EXPECT_EQ(3, anagram("aaabbb"));
	EXPECT_EQ(1, anagram("ab"));
	EXPECT_EQ(-1, anagram("abc"));
	EXPECT_EQ(2, anagram("mnop"));
	EXPECT_EQ(0, anagram("xyyx"));
	EXPECT_EQ(1, anagram("xaxbbbxx"));
}

TEST(Anagram, sample1)
{
	EXPECT_EQ(3, anagram("asdfjoieufoa"));
	EXPECT_EQ(5, anagram("fdhlvosfpafhalll"));
	EXPECT_EQ(5, anagram("mvdalvkiopaufl"));
}

TEST(Anagram, case0)
{
	EXPECT_EQ(10, anagram("hhpddlnnsjfoyxpciioigvjqzfbpllssuj"));
	EXPECT_EQ(13, anagram("xulkowreuowzxgnhmiqekxhzistdocbnyozmnqthhpievvlj"));
	EXPECT_EQ(5,  anagram("dnqaurlplofnrtmh"));
	EXPECT_EQ(26, anagram("aujteqimwfkjoqodgqaxbrkrwykpmuimqtgulojjwtukjiqrasqejbvfbixnchzsahpnyayutsgecwvcqngzoehrmeeqlgknnb"));
	EXPECT_EQ(15, anagram("lbafwuoawkxydlfcbjjtxpzpchzrvbtievqbpedlqbktorypcjkzzkodrpvosqzxmpad"));
	EXPECT_EQ(-1, anagram("drngbjuuhmwqwxrinxccsqxkpwygwcdbtriwaesjsobrntzaqbe"));
	EXPECT_EQ(3,  anagram("ubulzt"));
	EXPECT_EQ(13, anagram("vxxzsqjqsnibgydzlyynqcrayvwjurfsqfrivayopgrxewwruvemzy"));
	EXPECT_EQ(13, anagram("xtnipeqhxvafqaggqoanvwkmthtfirwhmjrbphlmeluvoa"));
	EXPECT_EQ(-1, anagram("gqdvlchavotcykafyjzbbgmnlajiqlnwctrnvznspiwquxxsiwuldizqkkaawpyyisnftdzklwagv"));
}

TEST(Anagram, case14)
{
	EXPECT_EQ(3,  anagram("aaabbb"));
	EXPECT_EQ(1,  anagram("ab"));
	EXPECT_EQ(-1, anagram("abc"));
	EXPECT_EQ(2,  anagram("mnop"));
	EXPECT_EQ(0,  anagram("xyyx"));
	EXPECT_EQ(1,  anagram("xaxbbbxx"));
}

TEST(Anagram, case15)
{
	EXPECT_EQ(3, anagram("asdfjoieufoa"));
	EXPECT_EQ(5, anagram("fdhlvosfpafhalll"));
	EXPECT_EQ(5, anagram("mvdalvkiopaufl"));
}
