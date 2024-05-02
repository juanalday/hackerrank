// https://www.hackerrank.com/challenges/insertionsort1/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

std::vector<std::vector<int>> insertionSort1(std::vector<int> arr) {

	std::vector<std::vector<int>> ret;
	auto value = arr.back();

	for (auto rIter = arr.rbegin(); rIter != arr.rend(); ++rIter)
	{ 
		auto prev = next(rIter);
		if (*prev > value)
		{
			*rIter = *prev;
			ret.push_back(arr);
		}
		else if (*prev < value)
		{
			*rIter = value;
			ret.push_back(arr);
			return ret;
		}
	}
	return ret;
}

void insertionSort1(int n, std::vector<int> arr) {

	for (auto const & vec : insertionSort1(arr))
	{
		for_each(vec.begin(), prev(vec.end()), [](int value) {std::cout << value << ' '; });
		std::cout << vec.back() << "\n";
	}
}

TEST(insertionSort1, example)
{
	std::vector<std::vector<int>> output{ {1, 2, 4, 5, 5}, {1, 2, 4, 4, 5}, {1, 2, 3, 4, 5} };
	EXPECT_EQ(output, insertionSort1({1, 2, 4, 5, 3}));
}

TEST(insertionSort1, sample)
{
	std::vector<std::vector<int>> output{ {2, 4, 6, 8, 8}, {2, 4, 6, 6, 8}, {2, 4, 4, 6, 8}, {2, 3, 4, 6, 8} };
	EXPECT_EQ(output, insertionSort1({ 2, 4, 6, 8, 3 }));
}

TEST(insertionSort1, case0)
{
	std::vector<std::vector<int>> output{ {2, 4, 6, 8, 8}, {2, 4, 6, 6, 8}, {2, 4, 4, 6, 8}, {2, 3, 4, 6, 8} };
	EXPECT_EQ(output, insertionSort1({ 2, 4, 6, 8, 3 }));
}
