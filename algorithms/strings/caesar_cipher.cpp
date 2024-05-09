// https://www.hackerrank.com/challenges/caesar-cipher-1/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <numeric>
#include <string>

namespace {

	std::string caesarCipher(std::string s, int k) {
		std::array<char, 26> rotated;
		k = k % 26; // To avoid overflow...
		std::iota(rotated.begin(), rotated.end() , 'a');
		std::rotate(rotated.begin(), next(rotated.begin(), k), rotated.end());
		for (auto& x : s)
		{
			if (std::islower(static_cast<unsigned char>(x)))
				x = rotated[x - 'a'];
			else if (std::isupper(static_cast<unsigned char>(x)))
			{
				x = std::toupper(rotated[std::tolower(x) - 'a']);
			}

		}
		return s;

	}
}

TEST(caesar_cipher_1, example)
{
	EXPECT_EQ("Wkhuh'v-d-vwdupdq-zdlwlqj-lq-wkh-vnb", caesarCipher("There's-a-starman-waiting-in-the-sky", 3));
}

TEST(caesar_cipher_1, sample0)
{
	EXPECT_EQ("okffng-Qwvb", caesarCipher("middle-Outz", 2));
}

TEST(caesar_cipher_1, sample1)
{
	EXPECT_EQ("Fqbfdx-Qttp-ts-ymj-Gwnlmy-Xnij-tk-Qnkj", caesarCipher("Always-Look-on-the-Bright-Side-of-Life", 5));
}

TEST(caesar_cipher_1, case5)
{
	EXPECT_EQ("okffng-Qwvb", caesarCipher("middle-Outz", 2));
}

TEST(caesar_cipher_1, case10)
{
	EXPECT_EQ("1Y7U4WsDt23l4ww08E6zR3T19H4sWQ188N9bivyC6k1uNHAt1n10fz7fVk62XW2fyMU4D83am7R80N", caesarCipher("1X7T4VrCs23k4vv08D6yQ3S19G4rVP188M9ahuxB6j1tMGZs1m10ey7eUj62WV2exLT4C83zl7Q80M", 27));
}

TEST(caesar_cipher_1, case11)
{
	EXPECT_EQ("Fqbfdx-Qttp-ts-ymj-Gwnlmy-Xnij-tk-Qnkj", caesarCipher("Always-Look-on-the-Bright-Side-of-Life", 5));
}