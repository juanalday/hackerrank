//

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <vector>
#include <utility>
#include <tuple>

namespace {


    long nearlySimilarRectangles(std::vector<std::vector<long>> sides) {

        std::vector<std::pair<long, long>> pairs(sides.size());
        transform(sides.begin(), sides.end(), pairs.begin(), [](auto const& side) 
            {auto g = std::gcd(side.front(), side.back()); return std::pair{ side.front() / g, side.back() / g}; 
            });
        sort(pairs.begin(), pairs.end());
        
        long counter = 0;
        auto it = pairs.begin();
        while (it != pairs.end()) {
            auto it2 = std::find_if_not(it, pairs.end(), [it](const auto& elem) { return elem == *it; });
            long count = static_cast<long>(std::distance(it, it2));
            if (count > 1) {  // Only count if there are duplicates
                counter += count * (count - 1) / 2;  // Combination of count elements taken 2 at a time
            }
            it = it2;
        }
        return counter;
    }
}

TEST(nearlySimilarRectangles, example)
{
    EXPECT_EQ(2, nearlySimilarRectangles({ {5, 10}, {10, 10}, {3, 6}, {9, 9} }));
}

TEST(nearlySimilarRectangles, sample0)
{
    EXPECT_EQ(3, nearlySimilarRectangles({ {4, 8}, {15, 30}, {25, 50} }));
}

TEST(nearlySimilarRectangles, sample1)
{
    EXPECT_EQ(0, nearlySimilarRectangles({ {2, 1}, {10, 7}, {9, 6}, {6, 9}, {7,3} }));
}