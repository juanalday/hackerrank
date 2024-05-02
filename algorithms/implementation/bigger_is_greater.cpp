// https://www.hackerrank.com/challenges/bigger-is-greater/problem

#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>
#include <string>

std::string biggerIsGreater(std::string w) {

	if (w.size() < 2)
		return "no answer";

	auto findPivot = [](std::string& str)  {
		auto rit = std::next(str.rbegin()); // Start from the second character from the end.
		while (rit != str.rend() && *rit >= *std::prev(rit)) {
			++rit;
		}
		return rit == str.rend() ? str.rend() : std::prev(rit);
		};
	auto rPivot = findPivot(w);

	if (rPivot == w.rend()) return "no answer"; // If no pivot is found, return "no answer".
	++rPivot;
	
	auto rLeast = std::upper_bound(w.rbegin(), rPivot, *rPivot);

	// Perform the swap
	std::iter_swap(rPivot, rLeast);


	std::reverse(w.rbegin(), rPivot);
	return w;

}
TEST(biggerIsGreater, example)
{
	EXPECT_EQ("abdc", biggerIsGreater("abcd"));
}

TEST(biggerIsGreater, sample_0)
{
	EXPECT_EQ("ba", biggerIsGreater("ab"));
	EXPECT_EQ("no answer", biggerIsGreater("bb"));
	EXPECT_EQ("hegf", biggerIsGreater("hefg"));
	EXPECT_EQ("dhkc", biggerIsGreater("dhck"));
	EXPECT_EQ("hcdk", biggerIsGreater("dkhc"));
}

TEST(biggerIsGreater, sample_1)
{
	EXPECT_EQ("lmon", biggerIsGreater("lmno"));
	EXPECT_EQ("no answer", biggerIsGreater("dcba"));
	EXPECT_EQ("no answer", biggerIsGreater("dcbb"));
	EXPECT_EQ("acbd", biggerIsGreater("abdc"));
	EXPECT_EQ("abdc", biggerIsGreater("abcd"));
	EXPECT_EQ("fedcbabdc", biggerIsGreater("fedcbabcd"));
}