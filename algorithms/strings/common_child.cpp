// MEDIUM https://www.hackerrank.com/challenges/common-child/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

namespace {
	int commonChild(std::string const& s1, std::string const& s2) {

		// Matrix, with row and columns...
		// A 2D vector(matrix) with 2 rows and s1.size() + 1 columns.
		// This matrix is used to store the lengths of the common subsequences found during the iteration.
		// Only 2 rows are used to save memory, as we only need the current and the previous row to compute the LCS.

		std::vector<std::vector<int>> matrix(2, std::vector<int>(s1.size() + 1, 0));

		// Now, let's fill the matrix
		size_t row = 1;
		size_t col = 1;
		bool isLastRow = true;
		// Remember, I just need to know the number of combinations, not the actual combinations...
		for (auto c1 : s1) {
			row = isLastRow ? 1 : 0;
			col = 1;
			for (auto c2 : s2) {
				auto value(0);
				if (c1 == c2) { // we have found a common character in both strings
					//I take and increment the value from the diagonal cell (up and to the left)
					value = 1 + matrix.at(isLastRow ? row - 1 : row + 1).at(col - 1);
				}
				else {
					// I take the max value from either the cell above or the cell to the left
					value = std::max(matrix.at(isLastRow ? row - 1 : row + 1).at(col), matrix.at(row).at(col - 1));
				}
				// And I set the value... I do it in two steps (creating variable, then setting it here to debug easily)
				matrix.at(row).at(col) = value;
				++col;
			}
			isLastRow = !isLastRow; // and I switch the row for the next iteration
		}
		// Return the LCS length, which is found in the last cell of the row that was not just updated.
		// If isLastRow is true, the result is in the front row's last column (matrix.front().back());
		// otherwise, it is in the back row's last column(matrix.back().back()).
		return isLastRow ? matrix.front().back() : matrix.back().back();

	}
}

TEST(CommonChild, example) {
	EXPECT_EQ(3, commonChild("ABCD", "ABDC"));
}

TEST(CommonChild, sample0) {
	EXPECT_EQ(2, commonChild("HARRY", "SALLY"));
}

TEST(CommonChild, sample1) {
	EXPECT_EQ(0, commonChild("AA", "BB"));
}

TEST(CommonChild, sample2) {
	EXPECT_EQ(3, commonChild("SINCHAN", "NOHARAA"));
}

TEST(CommonChild, case6) {
	EXPECT_EQ(2, commonChild("HARRY", "SALLY"));
}

TEST(CommonChild, case7) {
	EXPECT_EQ(0, commonChild("AA", "BB"));
}

TEST(CommonChild, case14) {
	EXPECT_EQ(3, commonChild("SINCHAN", "NOHARAA"));
}