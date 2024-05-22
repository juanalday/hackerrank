//EASY https://www.hackerrank.com/challenges/beautiful-triplets/problem

#include "gtest/gtest.h"

#include <unordered_map>
#include <vector>

namespace {
	int beautifulTriplets_brute_force(int d, std::vector<int> const& arr) {
		int n = static_cast<int>(arr.size());
		int counter(0);
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
			{
				if ((arr[j] - arr[i]) != d)
					continue;
				for (int k = j + 1; k < n; ++k) {
					if ((arr[k] - arr[j]) == d)
						++counter;
				}
			}

		return counter;
	}
	int beautifulTriplets(int d, std::vector<int> const& arr) {
		std::unordered_map<int, int> value_counts;
		int counter = 0;

		for (int num : arr) { // How many times do I get each element in the sequence?
			value_counts[num]++;
		}

		// Now, look for potential triplets
		for (int num : arr) {
			if (value_counts[num + d] > 0 && value_counts[num + 2 * d] > 0) {
				counter += value_counts[num + d] * value_counts[num + 2 * d];
			}
		}


		return counter;
	}
}

TEST(BeautifulTriplets, example)
{
	EXPECT_EQ(3, beautifulTriplets_brute_force(1, { 2, 2, 3, 4, 5 }));
	EXPECT_EQ(3, beautifulTriplets(1, { 2, 2, 3, 4, 5 }));
	// 1. 0,2,4 [2,3,4] 4-3 == 3-2 == 1
	// 2. 1,2,4 [2,3,4] 4-3 == 3-2 == 1
	// 3. 2,3,4 [3,4,5] 5-4 == 4-3 == 1
}

TEST(BeautifulTriplets, sample0)
{
	EXPECT_EQ(3, beautifulTriplets_brute_force(3, { 1, 2, 4, 5, 7, 8, 10 }));
	EXPECT_EQ(3, beautifulTriplets(3, { 1, 2, 4, 5, 7, 8, 10 }));
	// 1. 0,2,4 [1,4,7] 7-4 == 4-1 == 3
	// 2. 1,3,5 [2,5,8] 8-5 == 5-2 == 3
	// 3. 2,4,6 [4,7,10]  10-7 == 7-4 == 3
}

TEST(BeautifulTriplets, sample1)
{
	EXPECT_EQ(3, beautifulTriplets_brute_force(2, { 1, 6, 7, 7, 8, 10, 12, 13, 14, 19 }));
	EXPECT_EQ(3, beautifulTriplets(2, { 1, 6, 7, 7, 8, 10, 12, 13, 14, 19 }));
	// 1. 2,5,7 [7,10,13]
	// 2. 3,5,7 [7,10,13]
}

TEST(BeautifulTriplets, case0)
{
	EXPECT_EQ(3, beautifulTriplets_brute_force(3, { 1, 2, 4, 5, 7, 8, 10 }));
	EXPECT_EQ(3, beautifulTriplets(3, { 1, 2, 4, 5, 7, 8, 10 }));
	// 1. 0,2,4 [1,4,7] 7-4 == 4-1 == 3
	// 2. 1,3,5 [2,5,8] 8-5 == 5-2 == 3
	// 3. 2,4,6 [4,7,10]  10-7 == 7-4 == 3
}

TEST(BeautifulTriplets, case1)
{
	EXPECT_EQ(3, beautifulTriplets_brute_force(2, { 1, 6, 7, 7, 8, 10, 12, 13, 14, 19 }));
	EXPECT_EQ(3, beautifulTriplets(2, { 1, 6, 7, 7, 8, 10, 12, 13, 14, 19 }));
	// 1. 2,5,7 [7,10,13]
	// 2. 3,5,7 [7,10,13]
}