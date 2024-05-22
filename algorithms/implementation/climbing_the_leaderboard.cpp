// MEDIUM  https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <algorithm>
#include <vector>

using ::testing::ElementsAre;

namespace {
    std::vector<int> climbingLeaderboard(std::vector<int> ranked, std::vector<int> player) {
        std::vector<int> results(player.size(), 0);

        std::sort(ranked.begin(), ranked.end(), std::greater<int>());
        ranked.erase(std::unique(ranked.begin(), ranked.end()), ranked.end());


        auto resultIter = results.begin();
        for (int p : player) {
            // Find the position where player's score fits in the ranked list
            auto it = std::lower_bound(ranked.begin(), ranked.end(), p, std::greater<int>());
            // The rank will be the index of iterator + 1 (1-based index)
            *resultIter++ = 1 + static_cast<int>(std::distance(ranked.begin(), it));
        }

        return results;
    }
}

TEST(ClimbingTheLeaderboard, example)
{
    EXPECT_THAT(climbingLeaderboard({ 100, 90, 90, 80}, { 70, 80, 105}), ElementsAre(4, 3, 1));

}

TEST(ClimbingTheLeaderboard, sample0)
{
    EXPECT_THAT(climbingLeaderboard({ 100, 100, 50, 40, 40, 20, 10 }, { 5, 25, 50, 120 }), ElementsAre(6, 4, 2, 1));
}

TEST(ClimbingTheLeaderboard, sample1)
{
    EXPECT_THAT(climbingLeaderboard({ 100, 90, 90, 80, 75, 60}, { 50, 65, 77, 90, 102 }), ElementsAre(6, 5, 4, 2, 1));
}

TEST(ClimbingTheLeaderboard, case0)
{
    EXPECT_THAT(climbingLeaderboard({ 100, 100, 50, 40, 40, 20, 10 }, { 5, 25, 50, 120 }), ElementsAre(6, 4, 2, 1));
}

TEST(ClimbingTheLeaderboard, case11)
{
    EXPECT_THAT(climbingLeaderboard({ 100, 90, 90, 80, 75, 60 }, { 50, 65, 77, 90, 102 }), ElementsAre(6, 5, 4, 2, 1));
}
