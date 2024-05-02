//https://www.hackerrank.com/challenges/runningtime/problem

#include <gtest/gtest.h>

#include <vector>

int runningTime(std::vector<int> arr) {

	int ret(0);
	for (auto it1 = next(arr.begin()); it1 != arr.end(); ++it1) {
		auto i = static_cast<int>(distance(arr.begin(), it1));
		int current = *it1;

		int j = i - 1;
		while (j >= 0) {
			auto v2 = arr[j];
			if (v2 <= current)
				break;
			arr[j + 1] = arr[j];
			++ret;
			j--;
		}

		arr[j + 1] = current;

	}
	return ret;
}

TEST(runningTime, sample0)
{
	EXPECT_EQ(4, runningTime({2, 1, 3, 1, 2}));
}

TEST(runningTime, sample1)
{
	EXPECT_EQ(0, runningTime({ 1, 1, 2, 2, 3, 3, 5, 5, 7, 7, 9, 9 }));
}

TEST(runningTime, case0)
{
	EXPECT_EQ(4, runningTime({ 2, 1, 3, 1, 2 }));
}

TEST(runningTime, case1)
{
	EXPECT_EQ(0, runningTime({ 1, 1, 2, 2, 3, 3, 5, 5, 7, 7, 9, 9 }));
}