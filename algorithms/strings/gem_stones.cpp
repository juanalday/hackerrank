// https://www.hackerrank.com/challenges/gem-stones/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

namespace {
	int gemstones(std::vector<std::string> arr) {
		std::vector<int> gem(26, 0);
		std::vector<int> single(gem);
		for (auto const& s : arr) {
			std::fill(single.begin(), single.end(), 0);
			std::for_each(s.begin(), s.end(), [&single](auto c) { single[c - 'a'] = 1; });
			std::transform(gem.begin(), gem.end(), single.begin(), gem.begin(), std::plus<int>());
		}
		return static_cast<int>(std::count(gem.begin(), gem.end(), arr.size()));
	}
}

TEST(GemStones, example) {
	EXPECT_EQ(2, gemstones({ "abc", "abc", "bc" }));
}

TEST(GemStones, sample0) {
	EXPECT_EQ(2, gemstones({ "abcdde", "baccd", "eeabg"}));
}

TEST(GemStones, sample1) {
	EXPECT_EQ(4, gemstones({ "basdfj", "asdlkjfdjsa", "bnafvfnsd", "oafhdlasd" }));

}

TEST(GemStones, sample2) {
	EXPECT_EQ(0, gemstones({ "vtrjvgbj", "mkmjyaeav", "sibzdmsk" }));
}

TEST(GemStones, case27) {
	EXPECT_EQ(2, gemstones({ "abcdde", "baccd", "eeabg" }));
}

TEST(GemStones, case28) {
	EXPECT_EQ(4, gemstones({ "basdfj", "asdlkjfdjsa", "bnafvfnsd", "oafhdlasd" }));

}

TEST(GemStones, case29) {
	EXPECT_EQ(0, gemstones({ "vtrjvgbj", "mkmjyaeav", "sibzdmsk" }));
}

