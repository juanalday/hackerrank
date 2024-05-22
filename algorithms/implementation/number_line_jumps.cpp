// EASY https://www.hackerrank.com/challenges/kangaroo/problem

#include <gtest/gtest.h>

#include <cmath>
#include <string>

namespace {
    std::string kangaroo(int x1, int v1, int x2, int v2) {
        if (x1 == x2) {
            return "YES";
        }
        else  if ((x1 < x2 && v1 > v2) || (x1 > x2 && v1 < v2)) {
            float t;
            t = (float)(x2 - x1) / (float)(v1 - v2);
            if (floor(t) == t) {
                return "YES";
            }
        }
        return "NO";
    }
}

TEST(Kangaroo, example) {
	EXPECT_EQ("YES", kangaroo(2, 1, 1, 2));
}

TEST(Kangaroo, sample0) {
	EXPECT_EQ("YES", kangaroo(0, 3, 4, 2));
}

TEST(Kangaroo, sample1) {
	EXPECT_EQ("NO", kangaroo(0, 2, 5, 3));
}

TEST(Kangaroo, case0) {
    EXPECT_EQ("YES", kangaroo(0, 3, 4, 2));
}

TEST(Kangaroo, case1) {
    EXPECT_EQ("NO", kangaroo(0, 2, 5, 3));
}

