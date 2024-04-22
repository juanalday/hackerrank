#include "gtest/gtest.h"

#include <string>
#include <vector>

std::vector<std::string> cavityMap(std::vector<std::string> grid) {

	std::vector<std::string> ret(grid);

	int len = grid.size();

	for (int r = 1; r < len-1; ++r)
	{
		std::string const& row = grid[r];
		for (int c = 1; c < len-1; ++c)
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

TEST(cavityMap, example)
{
	EXPECT_EQ(std::vector<std::string>({"989", "1X1", "111"}), cavityMap({"989", "191", "111"}));
}


TEST(cavityMap, case_0)
{
	EXPECT_EQ(std::vector<std::string>({ "1112", "1X12", "18X2", "1234" }), cavityMap({ "1112", "1912", "1892", "1234"}));
}


TEST(cavityMap, case_1)
{
	EXPECT_EQ(std::vector<std::string>({ "12", "12" }), cavityMap({ "12", "12"}));
}
