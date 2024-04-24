#include "gtest/gtest.h"

#include <algorithm>
#include <string>

std::string happyLadybugs(std::string b) {
	if (b.empty()) return "YES";


	std::string uniques(b);
	std::sort(uniques.begin(), uniques.end());
	uniques.erase(std::unique(uniques.begin(), uniques.end()), uniques.end());
	bool canMove(false);
	if (uniques.back() == '_') {
		uniques.pop_back();
		canMove = true;
	}
	for (auto x : uniques)
	{
		if (count(b.begin(), b.end(), x)  == 1)
			return "NO";
	}
	if (canMove)
		return "YES";

	// Remove underscores for easier processing
	b.erase(std::remove(b.begin(), b.end(), '_'), b.end());
	auto it = adjacent_find(b.begin(), b.end(), std::not_equal_to<>());
	while (it != b.end()) {
		// If it's at the beginning or the character after it is different,
		// and the character before it (if it exists) is different, then it's alone.
		if ((it == b.begin() || *(it - 1) != *it) && (it + 1 == b.end() || *(it + 1) != *it)) {
			return "NO";
		}
		// Move iterator to the next potential group of bugs
		it = adjacent_find(it + 1, b.end(), std::not_equal_to<>());
	}

	return "YES";
	// Now I can remove the '_' from the original string, I no longer need them for this part
	b.erase(remove(b.begin(), b.end(), '_'), b.end());
	auto i2 = std::adjacent_find(b.begin(), b.end(), std::less<char>());
	if (i2 == b.end())
		return "YES";
	return "NO";

	if (b.empty()) return "YES";
  
    b.erase(std::remove(b.begin(), b.end(), '_'), b.end());

    if (canMove) {
        std::sort(b.begin(), b.end());
        return std::adjacent_find(b.begin(), b.end(), std::not_equal_to<>()) == b.end() ? "YES" : "NO";
    } else {
        for (int i = 0; i < b.size(); ) {
            int start = i++;
            while (i < b.size() && b[i] == b[start]) ++i;
            if (i - start == 1) return "NO";
        }
        return "YES";
    }


	// Sort the bugs to group similar ones together, making it easier to count.
	std::string orig(b);
	std::sort(b.begin(), b.end());

	// Check for the ability to move (presence of underscores).
	if (!canMove && (orig != b))
		return "NO";
	char curr = '0';
	int counter(0);
	int minCounter(9);
	bool isolatedBug(false);

	for (auto x : b)
	{
		if (x == '_')
			continue;

		if (x == curr)
		{
			++counter;
		}
		else // they are different...
		{
			if (counter == 1)
				isolatedBug = 1;
			curr = x;
			counter = 1; // This is the first element, , that is an odd number


		}

	}
	if (counter == 1)
		return "NO";
	if ((counter > 1) && !canMove && (b != orig))
		return "NO";
	return "YES";

}

TEST(happyLadybugs, example)
{
	EXPECT_EQ("YES", happyLadybugs("YYR_B__BR"));
}

TEST(happyLadybugs, sample)
{
	EXPECT_EQ("YES", happyLadybugs("RBY_YBR"));
	EXPECT_EQ("NO", happyLadybugs("X_Y__X"));
	EXPECT_EQ("YES", happyLadybugs("__"));
	EXPECT_EQ("YES", happyLadybugs("B_RRBR"));
}


TEST(happyLadybugs, sample_case1)
{
	EXPECT_EQ("NO", happyLadybugs("AABBC"));
	EXPECT_EQ("YES", happyLadybugs("AABBC_C"));
	EXPECT_EQ("YES", happyLadybugs("_"));
	EXPECT_EQ("YES", happyLadybugs("DD__FQ_QQF"));
	EXPECT_EQ("NO", happyLadybugs("AABCBC"));
}

TEST(happyLadybugs, case2)
{
	EXPECT_EQ("NO", happyLadybugs("G"));
	EXPECT_EQ("NO", happyLadybugs("GR"));
	EXPECT_EQ("NO", happyLadybugs("_GR_"));
	EXPECT_EQ("NO", happyLadybugs("_R_G_"));
	EXPECT_EQ("YES", happyLadybugs("R_R_R"));
	EXPECT_EQ("YES", happyLadybugs("RRGGBBXX"));
	EXPECT_EQ("NO", happyLadybugs("RRGGBBXY"));
}