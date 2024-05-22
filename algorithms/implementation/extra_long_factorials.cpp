// MEDIUM https://www.hackerrank.com/challenges/extra-long-factorials/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

namespace {

    std::vector<int> multiply(std::vector<int> lhs, int n)
    {
        if (n == 0)
            return { 0 };
        if (n == 1)
            return lhs;

        std::vector<int> ret(lhs.size() + 2, 0); // enough size
        auto startIdx(0);

        while (n > 0) {
            int digit = n % 10; // Get the current digit

            int carry = 0;
            int idx = startIdx; // Start at the shifted position based on the current digit of n
            for (int x : lhs) { // Multiply each digit of lhs by the current digit of n
                auto prev = ret[idx];
                int val = x * digit + carry + prev;
                carry = val / 10;
                ret[idx] = val % 10; // Store only the least significant digit
                idx++;
            }

            // If there is any carry left after processing all digits of lhs, store it
            while (carry > 0) {
                ret[idx] += carry;
                carry = ret[idx] / 10;
                ret[idx] %= 10;
                idx++;
            }

            startIdx++; // Increase the start index for the next digit of n (this simulates shifting left)
            n /= 10; // Move to the next higher digit of n
        }

        while (ret.size() > 1 && ret.back() == 0) {
            ret.pop_back();
        }
        return ret;
    }

    std::string extraLongFactorial(int n)
    {
        std::vector<int> ret, tmpVec;
        auto tmp(n);
        while (tmp > 0)
        {
            ret.push_back(tmp % 10);
            tmp /= 10;
        }
        // ret how has a reversed-digits representation fo the highest number. 25 in this case looks like 52
        --n;
        while (n > 1)
        {
            ret = multiply(ret, n--);

        }

        // Let's convert the int values to displayable chars
        for_each(ret.begin(), ret.end(), [](int& i) { i += '0'; });

        return std::string(ret.rbegin(), ret.rend());
    }
 
    void extraLongFactorials(int n)
    {
        std::cout << extraLongFactorial(n) << "\n";
    }

}


TEST(ExtraLongFactorials, example)
{
	EXPECT_EQ("265252859812191058636308480000000", extraLongFactorial(30));
}

TEST(ExtraLongFactorials, sample0)
{
    EXPECT_EQ("15511210043330985984000000", extraLongFactorial(25));
}

TEST(ExtraLongFactorials, sample1)
{
    EXPECT_EQ("119622220865480194561963161495657715064383733760000000000", extraLongFactorial(45));
}

TEST(ExtraLongFactorials, case0)
{
    EXPECT_EQ("15511210043330985984000000", extraLongFactorial(25));
}

TEST(ExtraLongFactorials, case12)
{
    EXPECT_EQ("119622220865480194561963161495657715064383733760000000000", extraLongFactorial(45));
}