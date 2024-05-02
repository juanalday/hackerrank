#include <gtest/gtest.h>

#include <algorithm>
#include <vector>
#include <unordered_set>

std::vector<int> climbingLeaderboard(std::vector<int> ranked, std::vector<int> player) {
    std::vector<int> results;

    std::set<int, std::greater<int>> data(ranked.begin(), ranked.end());

    for (auto p : player)
    {
        auto [it, inserted] = data.insert(p);
        results.push_back(1 + static_cast<int>(std::distance(data.begin(), it)));
    }
    return results;
}

TEST(climbingLeaderboard, sample1)
{
    std::vector output = { 6, 4, 2, 1 };
    EXPECT_EQ(output, climbingLeaderboard({ 100, 100, 50, 40, 40, 20, 10 }, { 6, 4, 2, 1 }));
}

TEST(climbingLeaderboard, sample2)
{
    std::vector output = { 6, 5, 4, 2, 1 };
    EXPECT_EQ(output, climbingLeaderboard({ 100, 90, 90, 80, 75, 60}, { 50, 65, 77, 90, 102 }));
}
