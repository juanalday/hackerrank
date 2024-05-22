// MEDIUM https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <numeric>
#include <string>

namespace {

	int sherlockAndAnagrams(std::string const& s) {

		std::vector<int> freqs(26, 0);
		std::map<std::vector<int>, int> freqsMap;
		std::vector<std::string> substrs;
		for (int len = 1; len < s.size(); ++len) {
			auto last = prev(s.end(), len - 1); // Last will control the end of the sliding window
			for (auto it = s.begin(); it != last; ++it) {
				fill(freqs.begin(), freqs.end(), 0);
				for_each(it, next(it, len), [&freqs](char c) {++freqs[c - 'a']; });
				freqsMap[freqs]++;
			}
		}
		return std::accumulate(freqsMap.begin(), freqsMap.end(), 0, [](int acc, auto const& freq) { return acc + freq.second * (freq.second - 1) / 2; });
	}

}

TEST(SherlockAndAnagrams, example) {
	EXPECT_EQ(2, sherlockAndAnagrams("mom"));
}

TEST(SherlockAndAnagrams, sample0) {
	EXPECT_EQ(4, sherlockAndAnagrams("abba"));
	EXPECT_EQ(0, sherlockAndAnagrams("abcd"));
}

TEST(SherlockAndAnagrams, sample1) {
	EXPECT_EQ(3,  sherlockAndAnagrams("ifailuhkqq"));
	EXPECT_EQ(10, sherlockAndAnagrams("kkkk"));
}

TEST(SherlockAndAnagrams, sample2) {
	EXPECT_EQ(5, sherlockAndAnagrams("cdcd"));
}

TEST(SherlockAndAnagrams, case0) {
	EXPECT_EQ(4, sherlockAndAnagrams("abba"));
	EXPECT_EQ(0, sherlockAndAnagrams("abcd"));
}

TEST(SherlockAndAnagrams, case1) {
	EXPECT_EQ(3, sherlockAndAnagrams("ifailuhkqq"));
	EXPECT_EQ(10, sherlockAndAnagrams("kkkk"));
}

TEST(SherlockAndAnagrams, case5) {
	EXPECT_EQ(1464,   sherlockAndAnagrams("dbcfibibcheigfccacfegicigcefieeeeegcghggdheichgafhdigffgifidfbeaccadabecbdcgieaffbigffcecahafcafhcdg"));
	EXPECT_EQ(2452,   sherlockAndAnagrams("dfcaabeaeeabfffcdbbfaffadcacdeeabcadabfdefcfcbbacadaeafcfceeedacbafdebbffcecdbfebdbfdbdecbfbadddbcec"));
	EXPECT_EQ(873,    sherlockAndAnagrams("gjjkaaakklheghidclhaaeggllagkmblhdlmihmgkjhkkfcjaekckaafgabfclmgahmdebjekaedhaiikdjmfbmfbdlcafamjbfe"));
	EXPECT_EQ(585,    sherlockAndAnagrams("fdbdidhaiqbggqkhdmqhmemgljaphocpaacdohnokfqmlpmiioedpnjhphmjjnjlpihmpodgkmookedkehfaceklbljcjglncfal"));
	EXPECT_EQ(1305,   sherlockAndAnagrams("bcgdehhbcefeeadchgaheddegbiihehcbbdffiiiifgibhfbchffcaiabbbcceabehhiffggghbafabbaaebgediafabafdicdhg"));
	EXPECT_EQ(166650, sherlockAndAnagrams("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_EQ(840,    sherlockAndAnagrams("mhmgmbbccbbaffhbncgndbffkjbhmkfncmihhdhcebmchnfacdigflhhbekhfejblegakjjiejeenibemfmkfjbkkmlichlkbnhc"));
	EXPECT_EQ(2134,   sherlockAndAnagrams("fdacbaeacbdbaaacafdfbbdcefadgfcagdfcgbgeafbfbggdedfbdefdbgbefcgdababafgffedbefdecbaabdaafggceffbacgb"));
	EXPECT_EQ(1571,   sherlockAndAnagrams("bahdcafcdadbdgagdddcidaaicggcfdbfeeeghiibbdhabdhffddhffcdccfdddhgiceciffhgdibfdacbidgagdadhdceibbbcc"));
	EXPECT_EQ(1042,   sherlockAndAnagrams("dichcagakdajjhhdhegiifiiggjebejejciaabbifkcbdeigajhgfcfdgekfajbcdifikafkgjjjfefkdbeicgiccgkjheeiefje"));
}