// EASY https://www.hackerrank.com/challenges/jumping-on-the-clouds/problem

#include <gtest/gtest.h>

#include <vector>

namespace {
    int jumpingOnClouds(std::vector<int> const& c) {
        int count = 0;
        int n = static_cast<int>(c.size());
        int i = 0;
        while (i < n - 1) {
            if (i + 2 < n && c[i + 2] == 0) {
                i += 2;
            }
            else {
                i += 1;
            }
            ++count;
        }
        return count;
    }
}

TEST(JumpingOnClouds, example) {
    EXPECT_EQ(3, jumpingOnClouds({0, 1, 0, 0, 0, 1, 0}));
}

TEST(JumpingOnClouds, sample0) {
	EXPECT_EQ(4, jumpingOnClouds({0, 0, 1, 0, 0, 1, 0}));
}

TEST(JumpingOnClouds, sample1) {
	EXPECT_EQ(3, jumpingOnClouds({0, 0, 0, 0, 1, 0}));
}

TEST(JumpingOnClouds, case0) {
    EXPECT_EQ(4, jumpingOnClouds({ 0, 0, 1, 0, 0, 1, 0 }));
}

TEST(JumpingOnClouds, case1) {
    EXPECT_EQ(3, jumpingOnClouds({ 0, 0, 0, 0, 1, 0 }));
}
