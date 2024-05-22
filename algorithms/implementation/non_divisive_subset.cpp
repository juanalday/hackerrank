// MEDIUM https://www.hackerrank.com/challenges/non-divisible-subset/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {

    int nonDivisibleSubset(int k, std::vector<int> const& s) {

        std::vector<int> remainderCount(k, 0);

        // Count the frequency of each remainder
        for_each(s.begin(), s.end(), [&remainderCount, k](int num) { ++remainderCount[num % k]; });

        // Start with considering one element from remainder 0, if any
        int maxSize = remainderCount[0] > 0 ? 1 : 0;

        // Consider pairs of remainders
        for (int i = 1; i < (k / 2) + 1; i++) {
            if (i == k - i) {  // Special case where the two halves meet
                maxSize += (remainderCount[i] > 0) ? 1 : 0;
            }
            else {
                maxSize += std::max(remainderCount[i], remainderCount[k - i]);
            }
        }

        return maxSize;
    }
}

TEST(NonDivisibleSubset, example) {
	EXPECT_EQ(3, nonDivisibleSubset(4, { 19, 10, 12, 10, 24, 25, 22 }));
}

TEST(NonDivisibleSubset, sample0) {
	EXPECT_EQ(3, nonDivisibleSubset(3, { 1, 7, 2, 4 }));
}

TEST(NonDivisibleSubset, sample1) {
	EXPECT_EQ(11, nonDivisibleSubset(7, { 278, 576, 496, 727, 410, 124, 338, 149, 209, 702, 282, 718, 771, 575, 436 }));
}

TEST(NonDivisibleSubset, case0) {
    EXPECT_EQ(3, nonDivisibleSubset(3, { 1, 7, 2, 4 }));
}

TEST(NonDivisibleSubset, case16) {
    EXPECT_EQ(11, nonDivisibleSubset(7, { 278, 576, 496, 727, 410, 124, 338, 149, 209, 702, 282, 718, 771, 575, 436 }));
}