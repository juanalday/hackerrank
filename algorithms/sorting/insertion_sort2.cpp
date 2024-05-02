// https://www.hackerrank.com/challenges/insertionsort2/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

std::vector<std::vector<int>> insertionSort2(std::vector<int> arr) {

	std::vector<std::vector<int>> ret;

	
	for (auto it1 = next(arr.begin()); it1 != arr.end(); ++it1) {
		auto i = static_cast<int>(distance(arr.begin(), it1));
		int current = *it1;
		
		int j = i - 1;
		while (j >= 0) {
			auto v2 = arr[j];
			if (v2 <= current)
				break;
			arr[j + 1] = arr[j];
			j--;
		}
		
		arr[j + 1] = current;

		ret.push_back(arr);
	}
	return ret;
}

void insertionSort2(int n, std::vector<int> arr) {

	auto vs = insertionSort2(arr);
	for (auto const & vec : vs)
	{
		for_each(vec.begin(), prev(vec.end()), [](int value) {std::cout << value << ' '; });
		std::cout << vec.back() << "\n";
	}
}

TEST(insertionSort2, example)
{
	std::vector<std::vector<int>> output{ 
		{3, 4, 7, 5, 6, 2, 1}, 
		{3, 4, 7, 5, 6, 2, 1}, 
		{3, 4, 5, 7, 6, 2, 1}, 
		{3, 4, 5, 6, 7, 2, 1}, 
		{2, 3, 4, 5, 6, 7, 1}, 
		{1, 2, 3, 4, 5, 6, 7} };
	EXPECT_EQ(output, insertionSort2({3, 4, 7, 5, 6, 2, 1}));
}

TEST(insertionSort2, sample)
{
	std::vector<std::vector<int>> output{ 
		{1, 4, 3, 5, 6, 2}, 
		{1, 3, 4, 5, 6, 2}, 
		{1, 3, 4, 5, 6, 2}, 
		{1, 3, 4, 5, 6, 2},
		{1, 2, 3, 4, 5, 6}
	};
	EXPECT_EQ(output, insertionSort2({ 1, 4, 3, 5, 6, 2 }));
}

TEST(insertionSort2, case0)
{
	std::vector<std::vector<int>> output{
		{1, 4, 3, 5, 6, 2},
		{1, 3, 4, 5, 6, 2},
		{1, 3, 4, 5, 6, 2},
		{1, 3, 4, 5, 6, 2},
		{1, 2, 3, 4, 5, 6}
	};
	EXPECT_EQ(output, insertionSort2({ 1, 4, 3, 5, 6, 2 }));
}


TEST(insertionSort2, case5)
{
	std::vector<std::vector<int>> const output{ 
		{7 ,8 ,6 ,5 ,4 ,3 ,2 ,1},
		{6 ,7 ,8 ,5 ,4 ,3 ,2 ,1},
		{5 ,6 ,7 ,8 ,4 ,3 ,2 ,1},
		{4 ,5 ,6 ,7 ,8 ,3 ,2 ,1},
		{3 ,4 ,5 ,6 ,7 ,8 ,2 ,1},
		{2 ,3 ,4 ,5 ,6 ,7 ,8 ,1},
		{1 ,2 ,3 ,4 ,5 ,6 ,7 ,8} };
	EXPECT_EQ(output, insertionSort2({ 8, 7, 6, 5, 4, 3, 2, 1 }));
}
