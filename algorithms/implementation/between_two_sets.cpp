#include "gtest/gtest.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <vector>

std::vector<int> findFactors(int num) {
    std::vector<int> factors;
    for (int i = 1; i <= std::sqrt(num); ++i) {
        if (num % i == 0) { // If i is a factor
            factors.push_back(i);
            if (i != num / i) { // Add the corresponding divisor if it's not the square root
                factors.push_back(num / i); // Add the corresponding divisor
            }
        }
    }
    sort(factors.begin(), factors.end()); // Sort the vector to have factors in ascending order
    return factors;
}

int getTotalX(std::vector<int> const& a, std::vector<int> const& b) {

    // What is the gcd of b?
    int b_gcd = std::accumulate(b.begin(), b.end(), 0, [](int a, int b) {return std::gcd(a, b); });
    // Now all the factors of this gcd are common to all elements of vector b
    std::vector<int> b_factors = findFactors(b_gcd);

    auto ret = std::count_if(b_factors.begin(), b_factors.end(), [&a](int x) {
        return std::all_of(a.begin(), a.end(), [x](int factor) { return x % factor == 0; });
        });
    return static_cast<int>(ret);
}

TEST(between_two_sets, findFactors)
{
    EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 6, 12}), findFactors(12));
}
TEST(between_two_sets, example)
{
    EXPECT_EQ(2, getTotalX({2,6}, {24, 36}));
}

TEST(between_two_sets, case_0)
{
    EXPECT_EQ(3, getTotalX({2,4}, { 16, 32, 96}));
}

TEST(between_two_sets, case_7)
{
    EXPECT_EQ(8, getTotalX({1 }, {72,48}));
}

TEST(between_two_sets, case_8)
{
    EXPECT_EQ(2, getTotalX({ 3,4 }, { 24, 48 }));
}