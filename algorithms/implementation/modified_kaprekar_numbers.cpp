// EASY https://www.hackerrank.com/challenges/kaprekar-numbers/problem
#include "gtest/gtest.h"

#include <cmath>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {
    std::string kaprekarNumbers_string(int p, int q) {
        std::ostringstream buffer;

        bool space(false);
        std::string d1, d2;
        long n1, n2;
        while (p <= q)
        {
            long pp = static_cast<long>(p) * p;
            if (pp < 10)
            {
                n1 = pp;
                n2 = 0;
            }
            else
            {
                d2 = std::to_string(pp);
                auto sss = d2.size();
                d1 = d2.substr(0, d2.size() / 2);
                d2.erase(0, d1.size());

                n1 = std::stol(d1);
                n2 = std::stol(d2);
            }
            // 77798^2=6049417284
            auto k1 = n1 + n2;
            if (k1 == p)
            {
                if (space)
                    buffer << ' ';
                buffer << p;
                space = true;
            }
            ++p;
        }
        if (space == false)
            buffer << "INVALID RANGE";

        return buffer.str();
    }

    std::string kaprekarNumbers(int p, int q) {
        std::ostringstream buffer;
        bool space(false);

        auto countDigits = [](long long n) {n = std::abs(n); return 1 + (n == 0 ? 0 : static_cast<int>(std::log10(n))); };

        while (p <= q)
        {
            long pp = static_cast<long>(p) * p;
            int numDigitsPP = countDigits(pp);
            int mid = numDigitsPP / 2; // Calculate mid point for splitting

            // Calculate the divisor based on whether the number of digits is even or odd
            long divisor = static_cast<long>(std::pow(10, numDigitsPP - mid));

            long left = pp / divisor; // Get the first part
            long right = pp % divisor; // Get the second part

            if (left + right == p)
            {
                if (space)
                    buffer << ' ';
                buffer << p;
                space = true;
            }
            ++p;
        }
        if (space == false)
            buffer << "INVALID RANGE";

        return buffer.str();
    }

}

TEST(ModifiedKaprekarNumbers, example)
{
    EXPECT_EQ("1 9 45 55 99", kaprekarNumbers(1, 100));
    EXPECT_EQ("1 9 45 55 99", kaprekarNumbers_string(1, 100));
}

TEST(ModifiedKaprekarNumbers, invalid_range)
{
    EXPECT_EQ("INVALID RANGE", kaprekarNumbers(3, 5));
    EXPECT_EQ("INVALID RANGE", kaprekarNumbers_string(3, 5));
}

TEST(ModifiedKaprekarNumbers, sample0)
{
    EXPECT_EQ("1 9 45 55 99", kaprekarNumbers(1, 100));
    EXPECT_EQ("1 9 45 55 99", kaprekarNumbers_string(1, 100));
}
TEST(ModifiedKaprekarNumbers, sample1)
{
    EXPECT_EQ("297", kaprekarNumbers(100, 300));
    EXPECT_EQ("297", kaprekarNumbers_string(100, 300));
}
TEST(ModifiedKaprekarNumbers, case0)
{
    EXPECT_EQ("1 9 45 55 99", kaprekarNumbers(1, 100));
    EXPECT_EQ("1 9 45 55 99", kaprekarNumbers_string(1, 100));
}
TEST(ModifiedKaprekarNumbers, case1)
{
    EXPECT_EQ("297", kaprekarNumbers(100, 300));
    EXPECT_EQ("297", kaprekarNumbers_string(100, 300));
}