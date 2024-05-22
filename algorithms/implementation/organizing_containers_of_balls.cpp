// MEDIUM https://www.hackerrank.com/challenges/organizing-containers-of-balls/problem

#include <gtest/gtest.h>

#include <numeric>
#include <string>
#include <vector>

namespace {

    std::string organizingContainers(std::vector<std::vector<int>> container) {
        using namespace std;
        auto const& rowsCols = container.size();
        auto isRangesEqual = 0;
        for (auto row = 0; row != rowsCols; ++row) {
            isRangesEqual ^= std::accumulate(begin(container.at(row)), end(container.at(row)), 0);
            for (auto col = 0; col != rowsCols && row != 0; ++col) {
                container.at(0).at(col) += container.at(row).at(col);
            }
        }
        for (auto& sumOfBallsByType : container.front()) {
            isRangesEqual ^= sumOfBallsByType;
        }
        return isRangesEqual == 0 ? "Possible" : "Impossible";
    }
}

TEST(OrganizingContainers, example) {
	EXPECT_EQ("Impossible", organizingContainers({ {1, 4}, {2, 3} }));
}

TEST(OrganizingContainers, sample0) {
	EXPECT_EQ("Possible",   organizingContainers({ {1, 1}, {1, 1} }));
    EXPECT_EQ("Impossible", organizingContainers({ {0, 2}, {1, 1} }));
}

TEST(OrganizingContainers, sample1) {
    EXPECT_EQ("Impossible", organizingContainers({ {1, 3, 1}, {2, 1, 2}, {3, 3, 3} }));
    EXPECT_EQ("Possible",   organizingContainers({ {0, 2, 1}, {1, 1, 1}, {2, 0, 0} }));
}

TEST(OrganizingContainers, case0) {
    EXPECT_EQ("Possible", organizingContainers({ {1, 1}, {1, 1} }));
    EXPECT_EQ("Impossible", organizingContainers({ {0, 2}, {1, 1} }));
}

TEST(OrganizingContainers, case6) {
    EXPECT_EQ("Impossible", organizingContainers({ {1, 3, 1}, {2, 1, 2}, {3, 3, 3} }));
    EXPECT_EQ("Possible", organizingContainers({ {0, 2, 1}, {1, 1, 1}, {2, 0, 0} }));

}