//

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
	int longestSubarray(std::vector<int> arr) {
		if (arr.size() == 1)
			return 1;
		int longest(0);
		auto numbers(arr);
		std::sort(numbers.begin(), numbers.end());
		numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end());

		for (auto it1 = numbers.begin(); it1 != numbers.end(); ++it1)
		{
			for (auto it2 = it1; it2 != numbers.end(); ++it2)
			{
				if (it1 == it2)
					continue;
				if ((*it2 - *it1) > 1)
					continue;
				auto n = 0;
				for (auto x : arr)
				{
					if ((x != *it1) && (x != *it2))
					{
						n = 0;
						continue;
					}
					else
					{
						++n;
					}
					longest = std::max(n, longest);
				}


			}
		}
        return longest;
	}
}

TEST(longestSubarray, example)
{
	EXPECT_EQ(4, longestSubarray({ 0, 1, 2, 1, 2, 3 }));
	EXPECT_EQ(4, longestSubarray({ 1, 1, 1, 3, 3, 2, 2 }));
}

TEST(longestSubarray, sample0)
{
	EXPECT_EQ(2, longestSubarray({ 0, 1, 2, 3, 4, 5 }));
}

TEST(longestSubarray, sample1)
{
	EXPECT_EQ(3, longestSubarray({ 2, 2, 1 }));
}

TEST(longestSubarray, case0)
{
	EXPECT_EQ(2, longestSubarray({ 1, 2, 3, 4, 5 }));
}

TEST(longestSubarray, case1)
{
	EXPECT_EQ(3, longestSubarray({ 2, 2, 1 }));
}

TEST(longestSubarray, case2)
{
	EXPECT_EQ(1, longestSubarray({ 295331535 }));
}
