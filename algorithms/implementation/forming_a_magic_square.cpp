// https://www.hackerrank.com/challenges/magic-square-forming/problem

#include <gtest/gtest.h>

#include <cmath>
#include <vector>

static std::vector<std::vector<std::vector<int>>> computeMagicSquares()
{
    return { 
        { {8, 1, 6}, {3, 5, 7}, {4, 9, 2} },
        { {6, 1, 8}, {7, 5, 3}, {2, 9, 4} },
        { {4, 9, 2}, {3, 5, 7}, {8, 1, 6} },
        { {2, 9, 4}, {7, 5, 3}, {6, 1, 8} },
        { {8, 3, 4}, {1, 5, 9}, {6, 7, 2} },
        { {4, 3, 8}, {9, 5, 1}, {2, 7, 6} },
        { {6, 7, 2}, {1, 5, 9}, {8, 3, 4} },
        { {2, 7, 6}, {9, 5, 1}, {4, 3, 8} } 
    };
}
int costToConvert(std::vector<std::vector<int>> const & s, std::vector<std::vector<int>> const& magic) {
    int cost = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cost += std::abs(s[i][j] - magic[i][j]);
        }
    }
    return cost;
}

int formingMagicSquare(std::vector<std::vector<int>> s) {
    auto const magics = computeMagicSquares();
    int minCost = std::numeric_limits<int>::max();
    for (const auto& magic : magics) {
        int currentCost = costToConvert(s, magic);
        if (currentCost < minCost) {
            minCost = currentCost;
        }
    }
    return minCost;
}

TEST(formingMagicSquare, sample0)
{
    EXPECT_EQ(1, formingMagicSquare({ {4, 9, 2}, {3, 5, 7}, {8, 1, 5} }));
}

TEST(formingMagicSquare, sample1)
{
    EXPECT_EQ(4, formingMagicSquare({ {4, 8, 2}, {4, 5, 7}, {6, 1, 6} }));
}

TEST(formingMagicSquare, case22)
{
    EXPECT_EQ(4, formingMagicSquare({ {4, 8, 2}, {4, 5, 7}, {6, 1, 6} }));
}