// EASY https://www.hackerrank.com/challenges/happy-ladybugs/problem

#include "gtest/gtest.h"

#include <algorithm>
#include <string>

namespace {
	std::string happyLadybugs(std::string b) {

		if (b.empty()) return "YES";

		std::string uniques(b);
		std::sort(uniques.begin(), uniques.end());
		uniques.erase(std::unique(uniques.begin(), uniques.end()), uniques.end());
		bool canMove(false);
		if (uniques.back() == '_') {
			uniques.pop_back();
			canMove = true;
		}
		for (auto x : uniques)
		{
			if (count(b.begin(), b.end(), x) == 1)
				return "NO";
		}
		if (canMove)
			return "YES";

		// Remove underscores for easier processing
		b.erase(std::remove(b.begin(), b.end(), '_'), b.end());
		auto it = adjacent_find(b.begin(), b.end(), std::not_equal_to<>());
		while (it != b.end()) {
			// If it's at the beginning or the character after it is different,
			// and the character before it (if it exists) is different, then it's alone.
			if ((it == b.begin() || *(it - 1) != *it) && (it + 1 == b.end() || *(it + 1) != *it)) {
				return "NO";
			}
			// Move iterator to the next potential group of bugs
			it = adjacent_find(it + 1, b.end(), std::not_equal_to<>());
		}

		return "YES";

	}
}

TEST(HappyLadybugs, example)
{
	EXPECT_EQ("YES", happyLadybugs("YYR_B__BR"));
}

TEST(HappyLadybugs, sample0)
{
	EXPECT_EQ("YES", happyLadybugs("RBY_YBR"));
	EXPECT_EQ("NO", happyLadybugs("X_Y__X"));
	EXPECT_EQ("YES", happyLadybugs("__"));
	EXPECT_EQ("YES", happyLadybugs("B_RRBR"));
}


TEST(HappyLadybugs, sample1)
{
	EXPECT_EQ("NO", happyLadybugs("AABBC"));
	EXPECT_EQ("YES", happyLadybugs("AABBC_C"));
	EXPECT_EQ("YES", happyLadybugs("_"));
	EXPECT_EQ("YES", happyLadybugs("DD__FQ_QQF"));
	EXPECT_EQ("NO", happyLadybugs("AABCBC"));
}

TEST(HappyLadybugs, case0)
{
	EXPECT_EQ("YES", happyLadybugs("RBY_YBR"));
	EXPECT_EQ("NO", happyLadybugs("X_Y__X"));
	EXPECT_EQ("YES", happyLadybugs("__"));
	EXPECT_EQ("YES", happyLadybugs("B_RRBR"));
}

TEST(HappyLadybugs, case2)
{
	EXPECT_EQ("NO", happyLadybugs("G"));
	EXPECT_EQ("NO", happyLadybugs("GR"));
	EXPECT_EQ("NO", happyLadybugs("_GR_"));
	EXPECT_EQ("NO", happyLadybugs("_R_G_"));
	EXPECT_EQ("YES", happyLadybugs("R_R_R"));
	EXPECT_EQ("YES", happyLadybugs("RRGGBBXX"));
	EXPECT_EQ("NO", happyLadybugs("RRGGBBXY"));
}

TEST(HappyLadybugs, case11)
{
	EXPECT_EQ("NO", happyLadybugs("AABBC"));
	EXPECT_EQ("YES", happyLadybugs("AABBC_C"));
	EXPECT_EQ("YES", happyLadybugs("_"));
	EXPECT_EQ("YES", happyLadybugs("DD__FQ_QQF"));
	EXPECT_EQ("NO", happyLadybugs("AABCBC"));
}
