// EASY https://www.hackerrank.com/challenges/beautiful-binary-string/problem

#include <gtest/gtest.h>

#include <string>

namespace {
	int beautifulBinaryString(std::string b) {
		int ret(0); 
		auto pos = b.find("010");
		
		while (pos != std::string::npos)
		{
			b[pos + 2] = '1';
			++ret;
			pos = b.find("010");
		}
		return ret;
	}
}

TEST(BeautifulBinaryString, example) {
	EXPECT_EQ(1, beautifulBinaryString("010"));
}

TEST(BeautifulBinaryString, sample0) {
	EXPECT_EQ(2, beautifulBinaryString("0101010"));
}

TEST(BeautifulBinaryString, sample1) {
	EXPECT_EQ(0, beautifulBinaryString("01100"));
}

TEST(BeautifulBinaryString, sample2) {
	EXPECT_EQ(3, beautifulBinaryString("0100101010"));
}

TEST(BeautifulBinaryString, case0) {
	EXPECT_EQ(2, beautifulBinaryString("0101010"));
}

TEST(BeautifulBinaryString, case1) {
	EXPECT_EQ(0, beautifulBinaryString("01100"));
}

TEST(BeautifulBinaryString, case11) {
	EXPECT_EQ(3, beautifulBinaryString("0100101010"));
}
