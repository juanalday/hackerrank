#include "gtest/gtest.h"

#include <cmath>

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

TEST(strangeCounter, sample)
{
	EXPECT_EQ(6, strangeCounter(4));
}

TEST(strangeCounter, sample_case0)
{
	EXPECT_EQ(6, strangeCounter(4));
}

TEST(strangeCounter, sample_case1)
{
	EXPECT_EQ(5, strangeCounter(17));
}

TEST(strangeCounter, sample_case11)
{
	EXPECT_EQ(5, strangeCounter(17));
}