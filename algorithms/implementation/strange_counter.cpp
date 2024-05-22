// EASY https://www.hackerrank.com/challenges/strange-code/problem

#include "gtest/gtest.h"

#include <cmath>

namespace {
	long strangeCounter(long t) {
		int cycle = 0;
		long start(1);
		long startNumber(3);
		while (true)
		{
			long size = (cycle == 0 ? 3 : 3 * static_cast<long>(std::pow(2, cycle)));
			long end = start + size;
			if ((t >= start) and (t < end))
			{
				auto n = (t - start);
				n = startNumber - n;
				return n;
			}
			startNumber *= 2;
			start = end;
			++cycle;

		}
		return -1;
	}
}

TEST(StrangeCounter, example)
{
	EXPECT_EQ(6, strangeCounter(4));
}

TEST(StrangeCounter, sample0)
{
	EXPECT_EQ(6, strangeCounter(4));
}

TEST(StrangeCounter, sample1)
{
	EXPECT_EQ(5, strangeCounter(17));
}

TEST(StrangeCounter, case0)
{
	EXPECT_EQ(6, strangeCounter(4));
}

TEST(StrangeCounter, case1)
{
	EXPECT_EQ(5, strangeCounter(17));
}