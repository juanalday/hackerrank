// HARD https://www.hackerrank.com/challenges/count-strings/problem

#include <gtest/gtest.h>

#include <string>

namespace {
	int countStrings(std::string r, int l) {
		return 0;
	}
}
TEST(CountStrings, DISABLED_sample0) {
	EXPECT_EQ(2, countStrings("((ab)|(ba))", 2));
	EXPECT_EQ(32, countStrings("((a|b)*)", 5));
	EXPECT_EQ(100, countStrings("((a*)(b(a*)))", 100));

}