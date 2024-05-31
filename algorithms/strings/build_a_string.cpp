// HARD https://www.hackerrank.com/challenges/build-a-string/problem

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {
	int buildString(int a, int b, std::string s) {
        int n = static_cast<int>(s.size());
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;  // Cost to build an empty string is 0

        for (int i = 1; i <= n; ++i) {
            // Cost of appending a single character
            dp[i] = dp[i - 1] + a;

            // Cost of copying a substring
            for (int j = 1; j <= i / 2; ++j) {
                if (s.substr(i - j, j) == s.substr(i - 2 * j, j)) {
                    dp[i] = std::min(dp[i], dp[i - j] + b);
                }
            }
        }

        return dp[n];
	}

}

TEST(BuildString, DISABLED_sample0) {
	EXPECT_EQ(26, buildString(4, 5, "aabaacaba"));
	EXPECT_EQ(42, buildString(8,9, "bacbacacb"));
}
