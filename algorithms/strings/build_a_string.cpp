// HARD https://www.hackerrank.com/challenges/build-a-string/problem

#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

namespace {
	int buildString(int a, int b, std::string s) {

        std::vector<int> lastpos(26, -1);//last position table
        std::vector<int> prevpos(26, 0);//previous position table
        std::vector<int> dp(s.size() + 1, 0);//reach i pos the best res
        std::vector<int> prevmaxlen(s.size(), 0);//previous max length table

        for (int i = 0; i < s.size(); ++i) {
            prevpos[i] = lastpos[s[i] - 'a'];
            lastpos[s[i] - 'a'] = i;
            dp[i + 1] = dp[i] + a;
            if (prevpos[i] != -1) {//appeared before
                int ii = prevpos[i];
                int maxlen = 1;
                while (ii != -1) {
                    if (ii == i - 1 || ii == 0) prevmaxlen[ii] = 1;
                    else {
                        if (s[i - 1] == s[ii - 1]) {
                            prevmaxlen[ii] = std::min(prevmaxlen[ii - 1] + 1, std::min(i - ii, ii + 1));
                            maxlen = std::max(maxlen, prevmaxlen[ii]);
                        }
                        else prevmaxlen[ii] = 1;
                    }
                    ii = prevpos[ii];
                }
                dp[i + 1] = std::min(dp[i + 1], dp[i - maxlen + 1] + b);
            }
        }

        return dp.back();
	}

}

TEST(BuildString, sample0) {
	EXPECT_EQ(26, buildString(4, 5, "aabaacaba"));
	EXPECT_EQ(42, buildString(8,9, "bacbacacb"));
}
