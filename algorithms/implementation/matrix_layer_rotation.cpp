#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

std::vector<std::vector<int>> doMatrixRotation(std::vector<std::vector<int>> matrix, int r) {

	auto rows = matrix.size();
	auto columns = matrix.front().size();

	auto topRow = matrix.begin();
	auto bottomRow = prev(matrix.end());
	auto lastRowIndex = rows - 1;
	auto lastColumnIndex = columns - 1;

	auto layers = std::min(rows / 2, columns / 2);
	auto columnsToShift = columns - 1; // If originally we have 7 columns, first move will shift 6 elements to the left
	auto rowsToShift = rows - 1; // IF originally we have 5 rows, second move will shift 4 elements upwards in the right-most column

	auto cellsInLayer = rows * columns;

	for (int i = 0; i < layers; ++i)
	{

		// How many rotations do I have to do here?
		// So if I have a 15x15, the outer layer rotates in 2*(14+14) = 56 moves. so r=100 = 44
		// the second layer is 13x13, so rotates in 48 moves. r=100 %48 = 4
		auto rotations = r % (2 * (rowsToShift + columnsToShift));
		while (rotations-- > 0)
		{
			auto topLeftEdge = matrix[i][i];
			// move the elements in the top row to the left
			std::move(next(topRow->begin(), i + 1), prev(topRow->end(), i), next(topRow->begin(), i));

			// shift upwards the values on the last column in my layer
			// We start at the top for this one
			for (auto count = 0; count < rowsToShift; ++count)
			{
				auto colIndex = columns -1 - i;
				auto target = next(topRow, count);
				auto source = next(target);
				(*target)[colIndex] = (*source)[colIndex];
			}

			// Now, move the elements in the bottom row to the right...
			std::move_backward(next(bottomRow->begin(), i), prev(bottomRow->end(), i + 1), prev(bottomRow->end(), i));

			// And finally, left column, we move it from top to bottom...
			// Remember that we saved the top-left element for safekeeping, so we start at the second row in the layer
			for (auto count = 0; count < rowsToShift -1; ++count)
			{
				auto target = prev(bottomRow, count);
				auto source = prev(target);
				(*target)[i] = (*source)[i];
			}
	
 			// And now we restore the value from {0, 0}, but in {1, 0}
			matrix[i + 1][i] = topLeftEdge;
		}
		++topRow;
		--bottomRow;

		rowsToShift -= 2;
		columnsToShift -= 2;

	}
	return matrix;
}

void matrixRotation(std::vector<std::vector<int>> const& matrix, int r) {

	auto result = doMatrixRotation(matrix, r);

	for (auto const& row : result)
	{
		for_each(row.begin(), prev(row.end()), [](int v) {std::cout << v << ' '; });
		std::cout << row.back() << std::endl;
	}
}

TEST(matrixRotation, odd_rows_and_columns)
{
	std::vector<std::vector<int>> input = { { 1, 2, 3, 4, 5 }, { 16, 1, 2, 3, 6 }, { 15, 8, 1, 4, 07 }, { 14, 7, 6, 5, 8 }, {13, 12, 11, 10, 9} };
	std::vector<std::vector<int>> output = { { 2, 3, 4, 5, 6}, {1, 2, 3, 4, 7}, {16, 1, 1, 5, 8}, {15, 8, 7, 6, 9}, {14, 13, 12, 11, 10} };
	EXPECT_EQ(output, doMatrixRotation(input, 1));
}
TEST(matrixRotation, sample1)
{
	std::vector<std::vector<int>> input = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
	std::vector<std::vector<int>> output_r1 = { {2, 3, 4, 8}, {1, 7, 11, 12}, {5, 6, 10, 16}, {9, 13, 14, 15} };
	std::vector<std::vector<int>> output = { {3, 4, 8, 12}, {2, 11, 10, 16}, {1, 7, 6, 15}, {5, 9, 13, 14} };
	EXPECT_EQ(output_r1, doMatrixRotation(input, 1));
	EXPECT_EQ(output, doMatrixRotation(input, 2));
}
TEST(matrixRotation, sample2)
{
	std::vector<std::vector<int>> input = { { 1, 2, 3, 4 }, { 7, 8, 9, 10 }, { 13, 14, 15, 16 }, { 19, 20, 21, 22 }, {25, 26, 27, 28} };
	std::vector<std::vector<int>> output_r1 = { {2, 3, 4, 10 }, {1, 9, 15, 16}, {7, 8, 21, 22}, {13, 14, 20, 28}, {19, 25, 26, 27} };
	std::vector<std::vector<int>> output_r2 = { {3, 4, 10, 16}, {2, 15, 21, 22}, {1, 9, 20, 28}, {7, 8, 14, 27}, {13, 19, 25, 26} };
	std::vector<std::vector<int>> output_r3 = { {4, 10, 16, 22}, {3, 21, 20, 28}, {2, 15, 14, 27}, {1, 9, 8, 26}, {7, 13, 19, 25} };
	std::vector<std::vector<int>> output_r4 = { {10, 16, 22, 28}, {4, 20, 14, 27}, {3, 21, 8, 26}, {2, 15, 9, 25}, {1, 7, 13, 19} };
	std::vector<std::vector<int>> output_r5 = { {16, 22, 28, 27}, {10, 14, 8, 26}, {4, 20, 9, 25}, {3, 21, 15, 19}, {2, 1, 7, 13} };
	std::vector<std::vector<int>> output_r6 = { {22, 28, 27, 26}, {16, 8, 9, 25}, {10, 14, 15, 19}, {4, 20, 21, 13}, {3, 2, 1, 7} };
	std::vector<std::vector<int>> output = { { 28, 27, 26, 25}, {22, 9, 15, 19}, {16, 8, 21, 13}, {10, 14, 20, 7}, {4, 3, 2, 1} };
	EXPECT_EQ(output_r1, doMatrixRotation(input, 1));
	EXPECT_EQ(output_r2, doMatrixRotation(input, 2));
	EXPECT_EQ(output_r3, doMatrixRotation(input, 3));
	EXPECT_EQ(output_r4, doMatrixRotation(input, 4));
	EXPECT_EQ(output_r5, doMatrixRotation(input, 5));
	EXPECT_EQ(output_r6, doMatrixRotation(input, 6));
	EXPECT_EQ(output, doMatrixRotation(input, 7));
}


TEST(matrixRotation, sample3)
{
	std::vector<std::vector<int>> input = { { 1, 1 }, { 1, 1} };
	std::vector<std::vector<int>> output = { { 1, 1 }, { 1, 1} };
	EXPECT_EQ(output, doMatrixRotation(input, 3));
}

