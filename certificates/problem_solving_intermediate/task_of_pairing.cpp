#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
	int taskOfPairing(std::vector<int> freq) {
		int pairs(0);
		for (auto it = freq.begin(); it != freq.end(); ++it)
		{
			auto count = *it;
			if (count == 0)
				continue;

			pairs += count / 2;

			*it = (count % 2); // Update the count of the current value (if it's odd, we can't pair it with another value

			if (*it == 0)
				continue;

			if (std::next(it) != freq.end())
			{
				++(*std::next(it));
				*it = 0;
			}
		}
		return pairs;
	}
}

TEST(taskOfPairing, example)
{
	EXPECT_EQ(5, taskOfPairing({ 2, 4, 3, 1 }));
}

TEST(taskOfPairing, sample0)
{
	EXPECT_EQ(7, taskOfPairing({ 3, 5, 4, 3 }));
}

TEST(taskOfPairing, sample1)
{
	EXPECT_EQ(6, taskOfPairing({ 5, 6, 2 }));
}

TEST(taskOfPairing, case0)
{
	EXPECT_EQ(7, taskOfPairing({ 3, 5, 4, 3 }));
}

TEST(taskOfPairing, case1)
{
	EXPECT_EQ(6, taskOfPairing({ 5, 6, 2 }));
}

TEST(taskOfPairing, case2)
{
	EXPECT_EQ(7, taskOfPairing({ 6, 5, 3 }));
}
