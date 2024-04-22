#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

int workbook(int k, std::vector<int> arr) {
	int currentPage(1);
	auto special(0);
	for (auto problems : arr)
	{
		int pagesForProblems = (problems / k) + (problems % k == 0 ? 0 : 1);

		for (auto p = 0; p < pagesForProblems; ++p)
		{
			auto firstExercise = 1 + (k * p);
			auto lastExercise = std::min(firstExercise + k - 1, problems);
			if ((currentPage >= firstExercise) && (currentPage <= lastExercise))
				++special;
			++currentPage;
		}

	}

	return special;
}

TEST(workbook, sample)
{
	EXPECT_EQ(1, workbook(3, { 4,2 }));
}
TEST(workbook, case_0)
{
	EXPECT_EQ(4, workbook(3, { 4,2,6,1,10 }));
}
TEST(workbook, case_1)
{
	EXPECT_EQ(8, workbook(5, { 3, 8, 15, 11, 14, 1, 9, 2, 24, 31 }));
}


TEST(workbook, case_10)
{
	EXPECT_EQ(32, workbook(29, { 3, 7, 11, 1, 8, 4, 3, 14, 13, 10, 18, 3, 3, 21, 20, 24, 21, 26, 22, 23, 2, 21, 23, 26, 31, 33, 30, 33, 38, 35, 34, 39, 44, 3, 49, 51, 54, 3, 49, 53, 53, 62, 59, 1, 1, 62, 65, 77, 78, 76, 78, 80, 84, 89, 94, 100, 100, 100, 100, 100, 100, 100, 100, 3, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 2, 100, 100, 100, 100, 100, 2, 100, 100, 100, 100 }));
}