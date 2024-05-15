// https://www.hackerrank.com/challenges/separate-the-numbers/problem

#include <gtest/gtest.h>

#include <cmath>
#include <string>

namespace {
	constexpr auto toNum = [](auto begin, auto end) {
		long long number = 0;
		while (begin != end) {
			number = number * 10 + (*begin - '0');
			++begin;
		}
		return number;
		};

	bool isValidSequence(long long initial, std::string::const_iterator it, std::string::const_iterator end) {
		auto num = initial;

		while (it != end) {
			++num;
			int nextLength = static_cast<int>(std::log10(num)) + 1;

			if (std::distance(it, end) < nextLength || *it == '0') {
				return false;
			}

			if (toNum(it, it + nextLength) != num) {
				return false;
			}

			it += nextLength;
		}
		return true;
	}

	std::string separateNumbers(std::string s) {

		for (int l = 1; l <= s.size() / 2; ++l) {
			auto initial = toNum(s.begin(), s.begin() + l);
			if (isValidSequence(initial, s.begin() + l, s.end())) {
				return "YES " + std::string(s.begin(), s.begin() + l);
			}
		}
		return "NO";
	}
}

TEST(separateNumbers, example)
{
	EXPECT_EQ(separateNumbers("1234"), "YES 1");
}

TEST(separateNumbers, sample0)
{
	EXPECT_EQ(separateNumbers("1234"), "YES 1");
	EXPECT_EQ(separateNumbers("91011"), "YES 9");
	EXPECT_EQ(separateNumbers("99100"), "YES 99");
	EXPECT_EQ(separateNumbers("101103"), "NO");
	EXPECT_EQ(separateNumbers("010203"), "NO");
	EXPECT_EQ(separateNumbers("13"), "NO");
	EXPECT_EQ(separateNumbers("1"), "NO");
}

TEST(separateNumbers, sample1)
{
	EXPECT_EQ(separateNumbers("99910001001"), "YES 999");
	EXPECT_EQ(separateNumbers("7891011"), "YES 7");
	EXPECT_EQ(separateNumbers("9899100"), "YES 98");
	EXPECT_EQ(separateNumbers("999100010001"), "NO");
}

TEST(separateNumbers, case0)
{
	EXPECT_EQ(separateNumbers("1234"), "YES 1");
	EXPECT_EQ(separateNumbers("91011"), "YES 9");
	EXPECT_EQ(separateNumbers("99100"), "YES 99");
	EXPECT_EQ(separateNumbers("101103"), "NO");
	EXPECT_EQ(separateNumbers("010203"), "NO");
	EXPECT_EQ(separateNumbers("13"), "NO");
	EXPECT_EQ(separateNumbers("1"), "NO");
}

TEST(separateNumbers, case20)
{
	EXPECT_EQ(separateNumbers("429496729542949672964294967297"), "YES 4294967295");
	EXPECT_EQ(separateNumbers("429496729542949672964294967296"), "NO");
	EXPECT_EQ(separateNumbers("429496729542949672964294967287"), "NO");
	EXPECT_EQ(separateNumbers("429496729542949672964294967197"), "NO");
	EXPECT_EQ(separateNumbers("42949672954294967296429496729"), "NO");
	EXPECT_EQ(separateNumbers("4294967295429496729642949672"), "NO");
	EXPECT_EQ(separateNumbers("429496729500000000000000000001"), "NO");
	EXPECT_EQ(separateNumbers("42949672950123456789"), "NO");
	EXPECT_EQ(separateNumbers("4294967295000010020030000456789"), "NO");
	EXPECT_EQ(separateNumbers("4294967295000102003004005"), "NO");
}

TEST(separateNumbers, case21)
{
	EXPECT_EQ(separateNumbers("99910001001"), "YES 999");
	EXPECT_EQ(separateNumbers("7891011"), "YES 7");
	EXPECT_EQ(separateNumbers("9899100"), "YES 98");
	EXPECT_EQ(separateNumbers("999100010001"), "NO");
}