// MEDIUM https://www.hackerrank.com/challenges/two-pluses/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

namespace {
	bool isAvailable(std::set<std::pair<int, int>> const& badCells, std::tuple<int, int, int> const& cross) noexcept
	{
		auto mid = std::get<0>(cross) / 2;

		for (int i = 0; i < std::get<0>(cross); ++i)
		{
			if (badCells.count({ std::get<1>(cross) - mid + i, std::get<2>(cross) }) || badCells.count({ std::get<1>(cross), std::get<2>(cross) - mid + i }))
				return false;
		}
		return true;
	}
	// Check if two crosses cross each other
	bool cross(std::tuple<int, int, int> x1, std::tuple<int, int, int> x2, std::set<std::pair<int, int>> data)
	{
		// adjust first one
		auto mid = std::get<0>(x1) / 2;
		for (int i = 0; i < std::get<0>(x1); ++i)
		{
			data.insert({ std::get<1>(x1) - mid + i, std::get<2>(x1) });
			data.insert({ std::get<1>(x1),           std::get<2>(x1) - mid + i });
		}
		return isAvailable(data, x2);
	}

	int twoPluses(std::vector<std::string> grid) {

		std::pair const gridLimit = { grid.size(), grid.front().size() };
		auto maxLen = static_cast<int>(std::min(gridLimit.first, gridLimit.second));
		if (maxLen % 2 == 0) // Maxlen has to be an odd number
			maxLen -= 1;

		std::set<std::pair<int, int>> badCells;
		// Let's fill the set of bad cells
		for (int r = 0; r < grid.size(); ++r)
		{
			std::string const& tmp = grid[r];
			for (int c = 0; c < tmp.size(); ++c)
			{
				if (tmp[c] == 'B')
				{
					badCells.emplace(r, c);
				}
			}
		}

		// Let's precompute all crosses that are available in the grid, starting with the max len we can do;
		std::vector<std::tuple<int, int, int>> centers;
		std::tuple<int, int, int> crossTuple; // Will hold length, row and column for center of cross...
		for (int crossLen = maxLen; crossLen >= 3; crossLen--)
		{
			if (crossLen % 2 == 0)
				continue;
			std::get<0>(crossTuple) = crossLen; // size of the cross

			auto mid = crossLen / 2; // This is the min distance the center of the cross is from the edge of the grid 

			for (auto row = mid; row < gridLimit.first - mid; ++row)
			{
				std::get<1>(crossTuple) = row; // row of the center of the cross

				for (auto column = mid; column < gridLimit.second - mid; ++column)
				{
					std::get<2>(crossTuple) = column; // column of the center of the cross

					auto good = isAvailable(badCells, crossTuple);
					if (good)
						centers.push_back(crossTuple);
				}
			}


		}

		if (centers.empty())
			return 1;

		int maxProduct = (2 * std::get<0>(centers.front())) - 1;

		for (auto it = centers.begin(); it != std::prev(centers.end()); ++it)
		{
			auto area1 = (2 * std::get<0>(*it)) - 1;
			maxProduct = std::max(maxProduct, area1);
			for (auto it2 = std::next(it); it2 != centers.end(); ++it2)
			{
				auto area2 = (2 * std::get<0>(*it2)) - 1;
				maxProduct = std::max(maxProduct, area2);

				if (cross(*it, *it2, badCells))
				{
					if (maxProduct < area1 * area1)
					{
						maxProduct = std::max(maxProduct, area1 * area2);
					}
				}
			}

		}

		return maxProduct;
	}
}

TEST(TwoPluses, sample0)
{
	EXPECT_EQ(5, twoPluses({ "GGGGGG", "GBBBGB", "GGGGGG", "GGBBGB", "GGGGGG" }));

}

TEST(TwoPluses, sample1)
{
	EXPECT_EQ(25, twoPluses({ "BGBBGB", "GGGGGG", "BGBBGB", "GGGGGG", "BGBBGB", "BGBBGB" }));
}

TEST(TwoPluses, case0)
{
	EXPECT_EQ(5, twoPluses({ "GGGGGG", "GBBBGB", "GGGGGG", "GGBBGB", "GGGGGG" }));

}

TEST(TwoPluses, case1)
{
	EXPECT_EQ(25, twoPluses({ "BGBBGB", "GGGGGG", "BGBBGB", "GGGGGG", "BGBBGB", "BGBBGB" }));
}

TEST(TwoPluses, case6)
{
	EXPECT_EQ(1, twoPluses({ "GGGGGGGGG","GBBBGGBGG","GBBBGGBGG","GBBBGGBGG","GBBBGGBGG","GBBBGGBGG","GBBBGGBGG","GGGGGGGGG" }));
}


TEST(TwoPluses, case21)
{
	EXPECT_EQ(377, twoPluses({ "BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","GGGGGGGGGGGGGGG","GGGGGGGGGGGGGGG","BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","GGGGGGGGGGGGGGG","BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","BBGBGGGGGBBGGBB","GGGGGGGGGGGGGGG" }));
}

TEST(TwoPluses, case22)
{
	EXPECT_EQ(81, twoPluses({ "BBBGBGBBB", "BBBGBGBBB", "BBBGBGBBB", "GGGGGGGGG", "BBBGBGBBB", "BBBGBGBBB", "GGGGGGGGG", "BBBGBGBBB", "BBBGBGBBB", "BBBGBGBBB" }));
}