// EASY https://www.hackerrank.com/challenges/jumping-on-the-clouds-revisited/problem

#include <gtest/gtest.h>

#include <vector>

namespace {
    int jumpingOnClouds(std::vector<int> c, int k)
    {
        auto next(0);
        int energy(100);
        while (true)
        {
            next = (next + k) % c.size();
            --energy;
            auto v = c[next];
            if (v == 1)
            {
                energy -= 2;
            }
            if (next == 0)
                break;
        }
        return energy;

    }
}

TEST(JumpingOnCloudsRevisited, example)
{
	EXPECT_EQ(96, jumpingOnClouds({0, 0, 1, 0}, 2));
}

TEST(JumpingOnCloudsRevisited, sample0)
{
    EXPECT_EQ(92, jumpingOnClouds({ 0, 0, 1, 0, 0, 1, 1, 0 }, 2));
}

TEST(JumpingOnCloudsRevisited, sample1)
{
    EXPECT_EQ(80, jumpingOnClouds({ 1, 1, 1, 0, 1, 1, 0, 0, 0, 0 }, 3));
}

TEST(JumpingOnCloudsRevisited, case0)
{
    EXPECT_EQ(92, jumpingOnClouds({ 0, 0, 1, 0, 0, 1, 1, 0 }, 2));
}

TEST(JumpingOnCloudsRevisited, case8)
{
    EXPECT_EQ(80, jumpingOnClouds({ 1, 1, 1, 0, 1, 1, 0, 0, 0, 0 }, 3));
}