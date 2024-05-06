// https://www.hackerrank.com/challenges/big-sorting/problem

#include <gtest/gtest.h>
#include "gmock/gmock-matchers.h"

#include <string>
#include <vector>

using ::testing::ElementsAre;

std::vector<std::string> bigSorting(std::vector<std::string> unsorted) 
{
	std::sort(unsorted.begin(), unsorted.end(), [](auto const& a, auto const& b)
		{ return (a.size() == b.size()) ? a < b : (a.size() < b.size()); });
	return unsorted;
}

TEST(bigSorting, example)
{
	EXPECT_THAT(bigSorting({ "1", "200", "150", "3" }), ElementsAre("1", "3", "150", "200"));
}

TEST(bigSorting, sample0)
{
	EXPECT_THAT(bigSorting({ "31415926535897932384626433832795", "1", "3", "10", "3", "5" }), ElementsAre("1", "3", "3", "5", "10", "31415926535897932384626433832795"));

}

TEST(bigSorring, sample1)
{
	EXPECT_THAT(bigSorting({ "1", "2", "100", "12303479849857341718340192371", "3084193741082937", "3084193741082938", "111", "200" }), ElementsAre("1", "2", "100", "111", "200", "3084193741082937", "3084193741082938", "12303479849857341718340192371"));
}

TEST(bigSorting, case0)
{
	EXPECT_THAT(bigSorting({ "31415926535897932384626433832795", "1", "3", "10", "3", "5" }), ElementsAre("1", "3", "3", "5", "10", "31415926535897932384626433832795"));

}