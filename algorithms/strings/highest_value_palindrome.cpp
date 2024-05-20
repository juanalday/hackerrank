// MEDIUM https://www.hackerrank.com/challenges/richie-rich/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>

namespace {
	std::string highestValuePalindrome(std::string s, int k) {

		auto alreadyPalindrome = 0;
		auto halfSize = s.size() / 2;
		for (auto it = s.begin(), it2 = prev(s.end()); it < it2; ++it, --it2) {
			if (*it == *it2) {
				++alreadyPalindrome;
			}
		}

		auto requiredChanges = halfSize - alreadyPalindrome; // This is the minimum changes to make in the first half to make it palindrome
		auto spareChanges = k - requiredChanges; // This is the extra number of changes I can make in the first half
		// This loop will make the string a palindrome (if I have enough changes for it)
		for (auto it = s.begin(), it2 = prev(s.end()); it < it2; ++it, --it2) 
		{
			// The letters are different, so let's change that
			if (*it != *it2) 
			{
				// If none are nine, and I have a spare change, I can make the left one a '9'
				if ((spareChanges > 0) && (*it != '9') && (*it2 != '9')) 
				{
					*it = '9';
					--spareChanges;
					--k;

				}
				// And now, either the left or the right will change to the highest value of the two...
				*it = *it2 = std::max(*it, *it2);
				--k;
			}
			else if ((spareChanges >= 2) && (*it != '9')) // Both letters are the same, but they are not nine, and I have Ks to make them 9
			{
				*it = *it2 = '9';
				spareChanges -= 2;
				k -= 2;
			}
		}

		// So the letter is a palindrome...
		// If I have an extra k, I will use one to move the middle letter to 9, if it is odd ...
		if ((k > 0) && (s.size() % 2 == 1)) {
			s[s.size() / 2] = '9';
		}

		if (k < 0) {
			return "-1";
		}

		return s;
	}
}

TEST(HighestValuePalindrome, debug_tests) {
	EXPECT_EQ(highestValuePalindrome("3943", 1), "3993");
	EXPECT_EQ(highestValuePalindrome("092282", 3), "992299");
	EXPECT_EQ(highestValuePalindrome("0011", 1), "-1");
	EXPECT_EQ(highestValuePalindrome("5", 1), "9");
	EXPECT_EQ(highestValuePalindrome("12321", 1), "12921");
	EXPECT_EQ(highestValuePalindrome("12321", 2), "92329");
	EXPECT_EQ(highestValuePalindrome("12321", 3), "92929");
	EXPECT_EQ(highestValuePalindrome("12321", 4), "99399");
	EXPECT_EQ(highestValuePalindrome("12321", 5), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 6), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 7), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 8), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 9), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 10), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 11), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 12), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 13), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 14), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 15), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 16), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 17), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 18), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 19), "99999");
	EXPECT_EQ(highestValuePalindrome("12321", 20), "99999");
}


TEST(HighestValuePalindrome, example)
{
	EXPECT_EQ(highestValuePalindrome("1231", 3), "9339");
	EXPECT_EQ(highestValuePalindrome("12321", 1), "12921");
}

TEST(HighestValuePalindrome, sample0)
{
	EXPECT_EQ(highestValuePalindrome("3943", 1), "3993");
}

TEST(HighestValuePalindrome, sample1)
{
	EXPECT_EQ(highestValuePalindrome("092282", 3), "992299");
}

TEST(HighestValuePalindrome, sample2)
{
	EXPECT_EQ(highestValuePalindrome("0011", 1), "-1");
}

TEST(HighestValuePalindrome, case0)
{
	EXPECT_EQ(highestValuePalindrome("3943", 1), "3993");
}
	
TEST(HighestValuePalindrome, case31)
{
	EXPECT_EQ(highestValuePalindrome("092282", 3), "992299");
}

TEST(HighestValuePalindrome, case32)
{
	EXPECT_EQ(highestValuePalindrome("0011", 1), "-1");
}