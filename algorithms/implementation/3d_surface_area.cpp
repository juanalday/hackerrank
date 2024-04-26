#include "gtest/gtest.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

int surfaceArea(std::vector<std::vector<int>> grid) {
    auto rows = grid.size();
	auto columns = grid.front().size();

	auto top = std::accumulate(grid.begin(), grid.end(), 0, [](int total, auto const& rows) 
		{return std::accumulate(rows.begin(), rows.end(), total, [](int t, int n) {return t + (n > 0 ? 1 : 0); });
		});

    auto area = 2 * top;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            auto height = grid[i][j];
            area += (i == 0 ? height :  std::max(0, height - grid[i - 1][j])); // with special case for left...

            area += (i == rows -1 ? height : std::max(0, height - grid[i + 1][j])); // with special case for right...
   
            area += (j == 0 ? height : std::max(0, height - grid[i][j - 1])); // Up

            area += (j == columns -1 ? height : std::max(0, height - grid[i][j + 1])); // Down
        }
    }

	return area;
}

TEST(surfaceArea, sample0)
{
	EXPECT_EQ(1, surfaceArea({ {1} }));
}

TEST(surfaceArea, sample1)
{
	EXPECT_EQ(60, surfaceArea({ {1,3,4}, {2,2,3}, {1,2,4} }));
}

TEST(surfaceArea, case_0)
{
    EXPECT_EQ(1, surfaceArea({ {1} }));
}

TEST(surfaceArea, case_25)
{
    EXPECT_EQ(60, surfaceArea({ {1,3,4}, {2,2,3}, {1,2,4} }));
}