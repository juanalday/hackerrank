// EASY https://www.hackerrank.com/challenges/cavity-map/problem

#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

#include <string>
#include <vector>

using ::testing::ElementsAre;

namespace {
	std::vector<std::string> cavityMap(std::vector<std::string> grid) {

		std::vector<std::string> ret(grid);

		size_t len = grid.size();

		for (size_t r = 1; r < len - 1; ++r)
		{
			std::string const& row = grid[r];
			for (size_t c = 1; c < len - 1; ++c)
			{
				auto value = row[c];
				if ((value <= row[c - 1]) || (value <= row[c + 1])) // compare left and right...
					continue;
				if ((value > grid[r - 1][c]) && (value > grid[r + 1][c])) //compare top to bottom
					ret[r][c] = 'X';
			}
		}
		return ret;
	}

}

TEST(CavityMap, example)
{
	EXPECT_THAT(cavityMap({"989", "191", "111"}), ElementsAre("989", "1X1", "111"));
}

TEST(CavityMap, sample0)
{
	EXPECT_THAT(cavityMap({ "1112", "1912", "1892", "1234"}), ElementsAre("1112", "1X12", "18X2", "1234"));
}


TEST(CavityMap, sample1)
{
	EXPECT_THAT(cavityMap({ "12", "12"}), ElementsAre("12", "12"));
}

TEST(CavityMap, case0)
{
	EXPECT_THAT(cavityMap({ "12", "12" }), ElementsAre("12", "12"));
}


TEST(CavityMap, case1)
{
	EXPECT_THAT(cavityMap({ "12", "12" }), ElementsAre("12", "12"));
}
