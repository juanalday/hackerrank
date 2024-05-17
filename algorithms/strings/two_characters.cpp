// https://www.hackerrank.com/challenges/two-characters/problem

#include <gtest/gtest.h>

#include <array>
#include <algorithm>
#include <string>

namespace {

	int alternate(std::string s)
	{
		int count(0);
		std::string chars(s);
		sort(chars.begin(), chars.end());
		chars.erase(unique(chars.begin(), chars.end()), chars.end());
		std::string data;

		for (auto x1 : chars)
		{
			for (auto x2 : chars)
			{
				if (x1 == x2)
					continue;
				data = s;
				data.erase(std::remove_if(data.begin(), data.end(), [&x1, &x2](auto c) {return ((c != x1) && (c != x2)); }), data.end());
				if (adjacent_find(data.begin(), data.end()) == data.end())
				{
					count = std::max(count, static_cast<int>(data.size()));
				}
			}
		}
		return count;
	}
}

TEST(TwoCharacters, example)
{
	EXPECT_EQ(4, alternate("abaacdabd"));
}

TEST(TwoCharacters, sample0)
{
	EXPECT_EQ(5, alternate("beabeefeab"));
}

TEST(TwoCharacters, sample1)
{
	EXPECT_EQ(8, alternate("asdcbsdcagfsdbgdfanfghbsfdab"));
}

TEST(TwoCharacters, sample_case2)
{
	EXPECT_EQ(0, alternate("asvkugfiugsalddlasguifgukvsa"));
}
