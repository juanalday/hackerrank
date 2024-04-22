#include "gtest/gtest.h"

#include <algorithm>
#include <vector>

int workbook(int k, std::vector<int> arr) {
	int currentPage(1);
	auto special(0);
	for (auto problems : arr)
	{
		int pagesForProblems = (problems / k) + ( problems % k == 0 ? 0 : 1);

		for (auto p = 0; p < pagesForProblems; ++p)
		{
			auto firstExercise = 1 + (k * p);
			auto lastExercise = std::min(firstExercise + k -1, problems);
			if ((currentPage >= firstExercise) && (currentPage <= lastExercise))
				++special;
			++currentPage;
		}

	}

	return special;
}

TEST(workbook, sample)
{
	EXPECT_EQ(1, workbook(3, {4,2}));
}
TEST(workbook, case_0)
{
	EXPECT_EQ(4, workbook(3, { 4,2,6,1,10 }));
}
TEST(workbook, case_1)
{
	EXPECT_EQ(8, workbook(5, { 3, 8, 15, 11, 14, 1, 9, 2, 24, 31 }));
}
