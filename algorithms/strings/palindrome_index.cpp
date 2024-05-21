// EASY https://www.hackerrank.com/challenges/palindrome-index/problem

#include <gtest/gtest.h>

#include <string>

namespace {
	int palindromeIndex(std::string s) {

		auto it = s.begin();
		auto itEnd = prev(s.end());

		for (; it < itEnd; ++it, --itEnd) {
			if (*it != *itEnd) { // first mismatch
				if ((*next(it) == *itEnd) && (*next(it, 2) == *prev(itEnd))) // check if removing left char makes palindrome
					return static_cast<int>(distance(s.begin(), it));
				else // So removing right char makes palindrome
					return static_cast<int>(distance(s.begin(), itEnd));
			}
		}
		return -1;

	}
}

TEST(PalindromeIndex, example)
{
	EXPECT_EQ(0, palindromeIndex("bcbc"));
}

TEST(PalindromeIndex, sample)
{
	EXPECT_EQ(3, palindromeIndex("aaab"));
	EXPECT_EQ(0, palindromeIndex("baa"));
	EXPECT_EQ(-1, palindromeIndex("aaa"));
}

TEST(PalindromeIndex, case0)
{
	EXPECT_EQ(3, palindromeIndex("aaab"));
	EXPECT_EQ(0, palindromeIndex("baa"));
	EXPECT_EQ(-1, palindromeIndex("aaa"));
}

TEST(PalindromeIndex, case3)
{
	EXPECT_EQ(8,  palindromeIndex("fyjwtatuieusvfqaeynaaiiaanyeaqfvsueutatwjyf"));
	EXPECT_EQ(20, palindromeIndex("qaaiyrpadovfjrmgkildtkseysejdtrpltptujlxxljutptlprtdjesyeskdlikgmrjfvodapryiaaq"));
	EXPECT_EQ(5,  palindromeIndex("llhrxcreddwkcronujfkwbdswoowsdbwkfjunorckwdderxrhll"));
	EXPECT_EQ(16, palindromeIndex("qasfhkfcojhntlfkaydtepsfsleipymwsopposwmypielsfspetdykfltnhjocfkhfsaq"));
	EXPECT_EQ(5,  palindromeIndex("broifqivnnvifiorb"));
	EXPECT_EQ(-1, palindromeIndex("bglgcwnmpobohqefrglsaaaaslgrfeqhobopmnwcglgb"));
	EXPECT_EQ(11, palindromeIndex("bthvmywukfwrkslaiialskwfkuwymvhtb"));
	EXPECT_EQ(28, palindromeIndex("uxxdlselxmwyiguugtpsypfudffswvwyswyyiiyywsywvsffdufpysptguugiywmxlesldxxu"));
	EXPECT_EQ(17, palindromeIndex("rvscdpyljqglgmiktfndsmfnkgmubrruloqptgohsgneocoyyocoengshogtpqolurrbumgknfmsdntkimglgqjlypdcsvr"));
	EXPECT_EQ(3,  palindromeIndex("qmdpbsswvmqtyhkobqeijjieqbokhytqmvwssbdmq"));
}