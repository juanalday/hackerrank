// EASY https://www.hackerrank.com/challenges/making-anagrams/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace {
	int making_anagrams(std::string s1, std::string s2) {
		sort(s1.begin(), s1.end());
		sort(s2.begin(), s2.end());
		std::vector<char> tmp;
		std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(tmp));
		std::set_difference(s2.begin(), s2.end(), s1.begin(), s1.end(), std::back_inserter(tmp));
		return static_cast<int>(tmp.size());
	}
}

TEST(MakingAnagrams, example)
{
	EXPECT_EQ(6, making_anagrams("abc", "amnop"));
}

TEST(MakingAnagrams, sample0)
{
	EXPECT_EQ(4, making_anagrams("cde", "abc"));
}

TEST(MakingAnagrams, sample1)
{
	EXPECT_EQ(19, making_anagrams("absdjkvuahdakejfnfauhdsaavasdlkj", "djfladfhiawasdkjvalskufhafablsdkashlahdfa"));
}

TEST(MakingAnagrams, case0)
{
	EXPECT_EQ(4, making_anagrams("cde", "abc"));
}

TEST(MakingAnagrams, case15)
{
	EXPECT_EQ(19, making_anagrams("absdjkvuahdakejfnfauhdsaavasdlkj", "djfladfhiawasdkjvalskufhafablsdkashlahdfa"));
}