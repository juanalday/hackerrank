// MEDIUM https://www.hackerrank.com/challenges/queens-attack-2/problem

#include <gtest/gtest.h>

#include <vector>

namespace {
    int queensAttack(int n, int k, int r_q, int c_q, std::vector<std::vector<int>> obstacles) {
        // Define max movements in all 8 possible directions
        int up = n - r_q;
        int down = r_q - 1;
        int left = c_q - 1;
        int right = n - c_q;
        int upRight = std::min(up, right);
        int upLeft = std::min(up, left);
        int downRight = std::min(down, right);
        int downLeft = std::min(down, left);

        // Adjust based on obstacles
        for (const auto& obs : obstacles) {
            int r_o = obs[0];
            int c_o = obs[1];

            if (r_o == r_q) { // Same row
                if (c_o > c_q) right = std::min(right, c_o - c_q - 1);
                else left = std::min(left, c_q - c_o - 1);
            }
            else if (c_o == c_q) { // Same column
                if (r_o > r_q) up = std::min(up, r_o - r_q - 1);
                else down = std::min(down, r_q - r_o - 1);
            }
            else if (abs(r_o - r_q) == abs(c_o - c_q)) { // Diagonal
                if (r_o > r_q) {
                    if (c_o > c_q) upRight = std::min(upRight, r_o - r_q - 1);
                    else upLeft = std::min(upLeft, r_o - r_q - 1);
                }
                else {
                    if (c_o > c_q) downRight = std::min(downRight, r_q - r_o - 1);
                    else downLeft = std::min(downLeft, r_q - r_o - 1);
                }
            }
        }

        // Sum up all valid moves
        return up + down + left + right + upRight + upLeft + downRight + downLeft;

    }

}

TEST(QueensAttack2, example) {
    EXPECT_EQ(24, queensAttack(8, 1, 4, 4, {{ 3, 5 }}));
}

TEST(QueensAttack2, sample0) {
	EXPECT_EQ(10, queensAttack(5, 3, 4, 3, {{5, 5}, {4, 2}, {2, 3}}));
}

TEST(QueensAttack2, sample1) {
	EXPECT_EQ(0, queensAttack(1, 0, 1, 1, {}));
}

TEST(QueensAttack2, case0) {
    EXPECT_EQ(10, queensAttack(5, 3, 4, 3, { {5, 5}, {4, 2}, {2, 3} }));
}

TEST(QueensAttack2, case1) {
    EXPECT_EQ(0, queensAttack(1, 0, 1, 1, {}));
}