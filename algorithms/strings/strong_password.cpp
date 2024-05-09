// https://www.hackerrank.com/challenges/strong-password/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace {


	int minimumNumber(std::string password) {
		int digit{ false }, lower{ false }, upper{ false }, special{ false };
		std::string const specialChars{ "!@#$%^&*()-+" };

		for_each(password.begin(), password.end(), [&](auto c) {
			digit |= std::isdigit(c);
			lower |= std::islower(c);
			upper |= std::isupper(c);
			special |= (specialChars.find_first_of(c) != std::string::npos);
			}
		);

		int ret = digit ? 0 : 1;
		ret += lower ? 0 : 1;
		ret += upper ? 0 : 1;
		ret += special ? 0 : 1;

		return std::max(ret, 6 - static_cast<int>(password.size()));
	}
}

TEST(strong_password, example)
{
	EXPECT_EQ(2, minimumNumber("2bbbb"));
	EXPECT_EQ(1, minimumNumber("2bb#A"));
}

TEST(strong_password, sample0)
{
	EXPECT_EQ(3, minimumNumber("Ab1"));
}

TEST(strong_password, sample1)
{
	EXPECT_EQ(1, minimumNumber("#HackerRank"));
}

TEST(strong_password, case0)
{
	EXPECT_EQ(3, minimumNumber("Ab1"));
}

TEST(strong_password, case1)
{
	EXPECT_EQ(1, minimumNumber("#HackerRank"));
}