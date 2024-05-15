// https://www.hackerrank.com/challenges/tutorial-intro/problem

#include <gtest/gtest.h>

#include <vector>

int introTutorial(int V, std::vector<int> arr) {
	auto iter = find(arr.begin(), arr.end(), V);
	return static_cast<int>(distance(arr.begin(), iter));
}

TEST(introTutorial, example)
{
	EXPECT_EQ(2, introTutorial(3, { 1, 2, 3 }));
}

TEST(introTutorial, sample0)
{
	EXPECT_EQ(1, introTutorial(4, { 1, 4, 5, 7, 9, 12 }));
}

TEST(introTutorial, case0)
{
	EXPECT_EQ(1, introTutorial(4, { 1, 4, 5, 7, 9, 12 }));
}