// EASY https://www.hackerrank.com/challenges/apple-and-orange/problem

#include <gtest/gtest.h>

#include <numeric>
#include <utility>
#include <vector>

namespace {
    std::pair<int, int> count(int s, int t, int a, int b, std::vector<int> apples, std::vector<int> oranges) {
        auto app = std::accumulate(apples.begin(), apples.end(), 0,
            [&](int init, int apple) {if (s <= (apple + a) && (apple + a) <= t) ++init; return init; }
        );
        auto ora = std::accumulate(oranges.begin(), oranges.end(), 0,
            [&](int init, int orange) {if (s <= (orange + b) && (orange + b) <= t) ++init; return init; }
        );
        return { app, ora };
    }
    void countApplesAndOranges(int s, int t, int a, int b, std::vector<int> apples, std::vector<int> oranges) {
        auto results = count(s, t, a, b, apples, oranges);
        std::cout << results.first << '\n' << results.second << '\n';
    }
}

TEST(AppleAndOrange, example)
{
    EXPECT_EQ(std::make_pair(1, 1), count(7, 11, 5, 15, { -2, 2, 1 }, { 5, -6 }));
}

TEST(AppleAndOrange, sample0)
{
    EXPECT_EQ(std::make_pair(1, 1), count(7, 11, 5, 15, { -2, 2, 1 }, { 5, -6 }));
}

TEST(AppleAndOrange, case0)
{
    EXPECT_EQ(std::make_pair(1, 1), count(7, 11, 5, 15, { -2, 2, 1 }, { 5, -6 }));
}

TEST(AppleAndOrange, case1)
{
    EXPECT_EQ(std::make_pair(0, 0), count(2, 3, 1, 5, { -2 }, { -1 }));
}