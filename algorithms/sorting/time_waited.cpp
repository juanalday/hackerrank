// This test is part of a corporate testing and is not available in hackerrank exercises
// In the original exercise, float was used rather than double. I just changed it to double to remove warnings.

#include <gtest/gtest.h>

#include <iomanip>
#include <string>
#include <vector>
#include <utility>

namespace {
	std::string calculateAvg(int T, double P, std::vector<int> tradeTimes, std::vector<double> tradePrices) {
        auto seconds = T;
        double weightedSum = 0;
        std::pair<int, double> lastTrade = { 0, P };
        std::pair<int, double> currentTrade = lastTrade;
        
		auto itT = tradeTimes.begin();
        auto itP = tradePrices.begin();
		for (; itT != tradeTimes.end() && itP != tradePrices.end(); ++itT, ++itP) {
			currentTrade = { *itT, *itP };
            auto length = (currentTrade.first - lastTrade.first);
            weightedSum += static_cast<double>(lastTrade.second) * (length);
            // And now
            lastTrade = std::move(currentTrade);
        }

        // Add the final segment
        weightedSum += static_cast<double>(lastTrade.second) * (seconds - lastTrade.first);

        std::ostringstream result;
        result << std::fixed << std::setprecision(2) << static_cast<double>(weightedSum) / seconds;

        return result.str();
        
	}
}

TEST(timeWaited, example)
{
    EXPECT_EQ("11.55", calculateAvg(100, 50.4, { 1, 4, 50 }, { 10.12, 10.90, 11.45 }));
}


TEST(timeWaited, case0)
{
    EXPECT_EQ("11.55", calculateAvg(100, 50.4, { 1, 4, 50 }, { 10.12, 10.90, 11.45 }));
}
