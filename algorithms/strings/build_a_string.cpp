// HARD https://www.hackerrank.com/challenges/build-a-string/problem

#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

namespace {
	int buildString(int a, int b, std::string s) {
        std::vector<int> lastPosition(26, -1);  // Last position of each character in the string
        std::vector<int> previousPosition(s.size(), -1);  // Previous position of each character in the string
        std::vector<int> dp(s.size() + 1, INT_MAX);  // DP array to store minimum cost to reach each position
        std::vector<int> maxLength(s.size(), 0);  // Maximum length of substring ending at each position

        std::vector<std::pair<int, int>> positions(26, { -1, -1 }); // current and previous position of each character in the string
        dp[0] = 0;  // Initial cost to build an empty string is 0

        int currentCost{ 0 };
        std::vector<int> costHistory(1 + s.size(), 0);

        for (int i = 0; i < s.size(); ++i) {
            auto currentChar = s[i];
            int currentCharIndex = (currentChar - 'a');
            positions[currentCharIndex].second = positions[currentCharIndex].first;
            positions[currentCharIndex].first = i;
            previousPosition[i] = lastPosition[currentCharIndex];
            lastPosition[currentCharIndex] = i;

            // Cost to append the current character
            dp[i + 1] = dp[i] + a;
            auto costToAppend = a; // Cost to append the current character

            if (positions[currentCharIndex].second != -1) // If the current char has appeared before, we can try copying the substring. Let's evaluate the cost
            { 
                auto previousCharIndex = positions[currentCharIndex].second;
            }

            currentCost += costToAppend;



            if (previousPosition[i] != -1) {  // If the character has appeared before
                int previousIndex = previousPosition[i];
                int currentMaxLen = 1;

                while (previousIndex != -1) {
                    if (previousIndex == i - 1 || previousIndex == 0) {
                        maxLength[previousIndex] = 1;
                    }
                    else {
                        if (s[i - 1] == s[previousIndex - 1]) {
                            maxLength[previousIndex] = std::min(maxLength[previousIndex - 1] + 1, std::min(i - previousIndex, previousIndex + 1));
                            currentMaxLen = std::max(currentMaxLen, maxLength[previousIndex]);
                        }
                        else {
                            maxLength[previousIndex] = 1;
                        }
                    }
                    previousIndex = previousPosition[previousIndex];
                }

                // Cost to copy the substring
                dp[i + 1] = std::min(dp[i + 1], dp[i - currentMaxLen + 1] + b);
            }
        }

        return dp.back();
	}

}

TEST(BuildString, sample0) {
	EXPECT_EQ(26, buildString(4, 5, "aabaacaba"));
	EXPECT_EQ(42, buildString(8,9, "bacbacacb"));
}
