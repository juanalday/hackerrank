#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
	int niceTeams(std::vector<int> rating, int minDiff) {
        std::sort(rating.begin(), rating.end());

        auto n = rating.size();

        auto leftIter = rating.begin();
        auto rightIter = next(leftIter);
        int pairs = 0;

        while (rightIter < rating.end()) {
            // Find a valid pair with the left pointer
            auto diff = *rightIter - *leftIter;
            if (diff >= minDiff) {
                ++pairs;
                ++leftIter;  // Move left pointer to the next element
                ++rightIter; // Move right pointer to the next element
            }
            else {
                ++rightIter; // Move right pointer to find a valid pair
            }

            // Ensure the left pointer is always behind the right pointer
            if (leftIter == rightIter) {
                ++rightIter;
            }
        }

        return pairs;

	}
}

TEST(niceTeams, example)
{
	EXPECT_EQ(2, niceTeams({ 1, 2, 3, 4, 5, 6 }, 4));
}

TEST(niceTeams, sample0)
{
	EXPECT_EQ(0, niceTeams({ 1, 1, 1, 1 }, 1));
}

TEST(niceTeams, sample1)
{
	EXPECT_EQ(2, niceTeams({ 3, 4, 5, 2, 1, 1 }, 3));
}

TEST(niceTeams, case0)
{
    EXPECT_EQ(0, niceTeams({ 1, 1, 1, 1 }, 1));
}

TEST(niceTeams, case1)
{
    EXPECT_EQ(2, niceTeams({ 3, 4, 5, 2, 1, 1 }, 3));
}

TEST(niceTeams, case2)
{
    EXPECT_EQ(0, niceTeams({ 76747402, 403380408, 801605449, 417846906, 274385224, 738031431, 21677517, 54770001, 396389085, 410040373, 66487560, 557886252, 273596334, 364059083 }, 866259468));
}

TEST(niceTeams, case3)
{
    EXPECT_EQ(5, niceTeams({ 25107191, 123232501, 151290765, 183012194, 473251358, 579542802, 689345248, 709552565, 803612259, 862726097, 994391793 }, 440987423));
}

TEST(niceTeams, case4)
{
    EXPECT_EQ(8, niceTeams({ 58938146, 219080001,290589043,306989605,318554335,345194195,376420327,509674780,802573599, 939226418}, 22586934));
}

TEST(niceTeams, case5)
{
    EXPECT_EQ(6, niceTeams({ 9176499, 16542169, 54397053, 90517182, 137497188, 199020027, 222817738, 342312501, 609983570, 715066757, 791805692, 808479481, 833709039, 985585792}, 463574357));
}

TEST(niceTeams, case6)
{
    EXPECT_EQ(1, niceTeams({ 23203911, 492930001, 605163057, 609897342, 690726610, 732048773, 771998092, 830083522, 893005429, 952945114 }, 763949691));
}