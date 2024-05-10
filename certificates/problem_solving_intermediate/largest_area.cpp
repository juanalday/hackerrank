#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <numeric>
#include <vector>

using ::testing::ElementsAre;

namespace {
    std::vector<int> getMaxArea(int w, int h, std::vector<bool> const& isVertical, std::vector<int> const& distance) {
        std::vector<int> maxAreas;
        std::vector<int> verticalLines = { 0, w }; // 0 and w are the left and right boundaries
        std::vector<int> horizontalLines = { 0, h };// 0 and h are the top and bottom boundaries

        for (size_t i = 0; i < isVertical.size(); ++i) {
            if (isVertical[i]) {
                verticalLines.push_back(distance[i]);
            }
            else {
                horizontalLines.push_back(distance[i]);
            }


            std::sort(verticalLines.begin(), verticalLines.end());
            std::sort(horizontalLines.begin(), horizontalLines.end());

            int maxWidth(0);
            for (size_t j = 1; j < verticalLines.size(); ++j) {
                maxWidth = std::max(maxWidth, verticalLines[j] - verticalLines[j - 1]);
            }


            int maxHeight = 0;
            for (size_t j = 1; j < horizontalLines.size(); ++j) {
                maxHeight = std::max(maxHeight, horizontalLines[j] - horizontalLines[j - 1]);
            }

            maxAreas.push_back(maxWidth * maxHeight);

        }
    
   
		return maxAreas;
	}
}

TEST(LargestArea, example)
{
	EXPECT_THAT(getMaxArea(4, 4, { 0, 1 }, { 3, 1 }), ElementsAre(12, 9));
}

TEST(LargestArea, sample0)
{
	EXPECT_THAT(getMaxArea(2, 2, { 0, 1 }, { 1, 1 }), ElementsAre(2, 1));
}

TEST(LargestArea, sample1)
{
	EXPECT_THAT(getMaxArea(4, 3, { 1, 1 }, { 1, 3 }), ElementsAre(9, 6));
}

TEST(LargestArea, case0)
{
	EXPECT_THAT(getMaxArea(2, 2, { 0, 1 }, { 1, 1 }), ElementsAre(2, 1));
}

TEST(LargestArea, case1)
{
	EXPECT_THAT(getMaxArea(4, 3, { 1, 1 }, { 1, 3 }), ElementsAre(9, 6));
}

TEST(LargestArea, case2)
{
	EXPECT_THAT(getMaxArea(4, 4, { 0, 1 }, { 3, 1 }), ElementsAre(12, 9));
}

TEST(LargestArea, case3)
{
	EXPECT_THAT(getMaxArea(4, 4, { 0, 0 }, { 2, 2 }), ElementsAre(8, 8));
}

TEST(LargestArea, case4)
{
    std::vector<int> const output = { 1176870696, 1007340066, 677028774, 629170170, 607585980, 605911860, 362827602, 354771072, 354771072, 306239346, 306239346, 306239346, 306239346, 306239346, 306239346, 306239346, 250147656, 180316620, 180316620, 180316620, 180316620, 180316620, 180316620, 96491745, 96491745, 96491745, 83943195, 83943195, 83943195, 83943195, 73323159, 73323159, 73323159, 73323159, 57168552, 57168552, 57168552, 57168552, 57168552, 57155343, 57155343, 57155343, 36701614, 36701614, 34581114, 34581114, 34581114, 34581114, 34581114, 29452248, 29452248, 24400845, 24400845, 24400845, 24400845, 24400845, 24400845, 24400845, 24400845, 24400845, 22566195, 22566195, 22566195, 22566195, 22566195, 15514605, 15514605, 15312789, 13602959, 13602959, 13602959, 13602959, 13462222, 13462222, 13462222, 13462222, 13462222, 13462222, 13462222, 13462222, 13462222 };
	EXPECT_EQ(output, getMaxArea(64338, 28454,
		{ 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 18292, 15657, 5134, 59790, 15268, 21631, 35803, 35008, 27986, 30219, 45601, 41692, 39471, 1282, 18469, 20971, 24684, 12439, 761, 54723, 42405, 59285, 38381, 11475, 10865, 20332, 10635, 9288, 2970, 2564, 22435, 42794, 5059, 7146, 26763, 4034, 61039, 33390, 46241, 26762, 8618, 7051, 17460, 7979, 26512, 556, 3905, 4848, 8970, 51061, 2677, 21139, 20138, 56195, 7908, 9756, 16904, 23065, 1030, 27355, 11997, 22236, 3441, 62467, 15242, 25196, 24641, 27009, 12607, 44996, 40126, 9976, 14585, 56584, 39298, 27748, 1517, 27018, 30840, 45429, 1505 }
   
    ));
}

TEST(LargestArea, case5)
{
    std::vector<int> const output = { 1384594872, 1379864772, 1272964512, 717177888, 717177888, 464039037, 282781422, 253138851, 253138851, 253138851, 226916235, 181257615, 181257615, 181257615, 181257615, 181257615, 181257615, 181257615, 178326225, 123521475, 123521475, 103004825, 103004825, 103004825, 103004825, 103004825, 103004825, 103004825, 103004825, 103004825, 103004825, 84756650, 84756650, 84756650, 84756650, 84756650, 84756650, 80070230, 80070230, 80070230, 80070230, 80070230, 80070230, 80070230, 80070230, 80070230, 63475855, 63475855, 47587646, 47587646, 38459690, 38459690, 38459690, 38459690, 38459690, 38459690, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 36898905, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 23612571, 22134297, 22134297, 22134297, 21315929, 21315929, 14456224, 14456224, 14456224, 12190771, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11825698, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11780689, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 11480629, 6372941, 6372941, 6372941, 6372941, 6372941, 6372941, 6372941, 6372941, 6372941, 6372941, 6372941, 6372941, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 5769487, 4675811, 4675811, 4675811, 4675811, 4675811, 4675811, 4675811, 4675811, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4592747, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 4066675, 2730729, 2730729, 2730729, 2730729, 2730729, 2730729, 2730729, 2730729, 2730729, 2730729, 2730729, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 2512176, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1990647, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1914957, 1720686, 1720686, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1628616, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1186836, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 1117753, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 901849, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 646011, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 504458, 488819, 488819, 488819, 488819, 488819, 488819, 488819, 488819, 477848, 477848, 477848, 477848, 477848, 477848, 477848, 477848, 477848, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534, 470534 };
    EXPECT_EQ(output, getMaxArea(22619, 87816,
        { 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1 },
        { 15767, 300, 7080, 6884, 2554, 59319, 27485, 53574, 53030, 16434, 77019, 44672, 38681, 2150, 71561, 68780, 22587, 66243, 27155, 10636, 10365, 17875, 6583, 5459, 82387, 43202, 22097, 43874, 70459, 2530, 9538, 13062, 77494, 51593, 79378, 54862, 6447, 8190, 52659, 781, 1799, 31475, 13024, 41233, 5015, 46547, 18750, 3650, 22408, 55718, 20083, 150, 35516, 63407, 47085, 4073, 21831, 37360, 19651, 27634, 11593, 11078, 20960, 7807, 43174, 123, 20880, 42321, 9580, 14476, 579, 75967, 15887, 53266, 76838, 22703, 4058, 50413, 3054, 2129, 6545, 13751, 12908, 82220, 58621, 21826, 46745, 12228, 1806, 25265, 85247, 17525, 9044, 15959, 49259, 7871, 10946, 13159, 5033, 18463, 20472, 20253, 3024, 20343, 16909, 21611, 1941, 15808, 74562, 10738, 9339, 768, 13261, 9140, 75503, 19958, 43179, 44453, 33954, 60438, 7489, 77684, 11370, 25618, 14409, 32612, 1821, 70177, 3727, 76381, 3798, 3325, 59839, 31457, 21588, 53914, 5225, 20226, 4389, 19658, 21037, 64502, 5004, 4504, 38373, 7453, 11514, 11744, 2302, 6776, 8397, 2001, 48860, 50542, 20046, 12884, 2711, 80758, 14619, 49547, 22017, 11589, 578, 42750, 71430, 9613, 19050, 72246, 70928, 7721, 3635, 12680, 19466, 16620, 11262, 22248, 73966, 78862, 65160, 84084, 11607, 12986, 64262, 4395, 5165, 28926, 1184, 1348, 20089, 31759, 70087, 14889, 65828, 44251, 5820, 12014, 23896, 7027, 6689, 18133, 10946, 6754, 6910, 2263, 34321, 16826, 8187, 62338, 26189, 3206, 20366, 59826, 30119, 83414, 8211, 18132, 18447, 10243, 19072, 20737, 2030, 10598, 29, 56788, 32895, 3514, 87769, 7413, 10262, 22060, 15462, 2600, 12704, 59351, 10390, 17621, 7768, 521, 69496, 25963, 1928, 41939, 14945, 12465, 14653, 17936, 4292, 16123, 40618, 7603, 8363, 23470, 15267, 20496, 22097, 5958, 70099, 63114, 20900, 20458, 18065, 65575, 7967, 10169, 20244, 12671, 20949, 64612, 13451, 6242, 36924, 32575, 5293, 35481, 9882, 6537, 80002, 47727, 6969, 11031, 15823, 19029, 12681, 9609, 3056, 76471, 83193, 13389, 8779, 22390, 12918, 15373, 30906, 51072, 9737, 35377, 62631, 19191, 11509, 16343, 26721, 72664, 56694, 53822, 4520, 85732, 6948, 20650, 12674, 14917, 48, 14413, 57796, 14311, 20600, 17328, 11425, 1651, 76026, 22563, 9568, 73373, 6814, 15221, 5929, 17768, 52754, 71617, 10993, 2922, 12629, 54093, 39921, 69354, 607, 21176, 16598, 15554, 14965, 10853, 176, 67192, 11519, 608, 22153, 8497, 4066, 54522, 60393, 15180, 74769, 884, 84749, 1641, 50146, 13820, 40240, 83868, 1195, 66237, 36880, 4643, 14476, 5422, 3916, 83864, 79825, 58741, 17961, 1389, 4598, 1233, 5850, 19735, 3585, 75208, 26793, 5718, 15095, 2595, 20609, 80924, 79281, 54521, 1944, 6374, 68557, 25356, 10408, 25504, 71364, 57992, 21719, 30736, 69206, 11468, 78784, 9049, 65493, 37518, 408, 17411, 16641, 13234, 12794, 64138, 9917, 70788, 4928, 21844, 12113, 12904, 14598, 42638, 10547, 9954, 9775, 67973, 9727, 55672, 30827, 2385, 20132, 35268, 7547, 57737, 17309, 71959, 87427, 5647, 24544, 30407, 9865, 82456, 33355, 33988, 41907, 7701, 8241, 20931, 43536, 68391, 69411, 25845, 7739, 45845, 18885, 24478, 9841, 4155, 9764, 9598, 10848, 6902, 23594, 79286, 9800, 22503, 76139, 433, 14486, 57325, 49422, 9376, 86714, 16069, 8277, 2751, 39020, 8879, 10211, 14048, 534, 20751, 55749, 41467, 2059, 33653, 59544, 20244, 25018, 19146, 9737, 14234, 8046, 6435, 19185, 57724, 17730, 21385, 22456, 20337, 4531, 58690, 1893, 12970, 15716, 18038, 15966, 21115, 22967, 33379, 85151, 19303, 12152, 2941, 19868, 20759, 8639, 17194, 18164, 56602, 21766, 10427, 18331, 12682, 58182, 51538, 25494, 19530, 20448, 10456, 1330, 3200, 35869, 78262, 7285, 177, 14281, 18091, 59126, 15584, 24660, 19322, 17911, 25998, 17537, 5034, 8877, 11276, 76710, 72692, 59585, 22239, 50869, 11988, 70666, 11061, 969, 62738, 12967, 3421, 87431, 31570, 8144, 36190, 10012, 12211, 72733, 84505, 16544, 51937, 19312, 7821, 9271, 4908, 20110, 3101, 13674, 14131, 32342, 2543, 13873, 80692, 61893, 65325, 26345, 3315, 19522, 42536, 17297, 11369, 24994, 6384, 81085, 16899, 10625, 54690, 3652, 14554, 6696, 64687, 198, 7723, 21870, 20536, 13019, 13893, 603, 106, 55154, 18349, 809, 20949, 13025, 56914, 19509, 15590, 2178, 65482, 15330, 13586, 5116, 85130, 3628, 25488, 70740, 4094, 20641, 20044, 29567, 69499, 16417, 18311, 20133, 22310, 27455, 60674, 5061, 72911, 17047, 57057, 51122, 33593, 20306, 11867, 1699, 3540, 27727, 41812, 58324, 26242, 9430, 13757, 12008, 68532, 80839, 17074, 7245, 4877, 54021, 21974, 19471, 21268, 67433, 13263, 12669, 16914, 80452, 67106, 43012, 20973, 36962, 8769, 15431, 19340, 1205, 20689, 22134, 66755, 46872, 16, 56166, 6779, 67422, 13791, 21952, 15330, 14173, 21586, 7768, 14300, 83718, 741, 16138, 21970, 10503, 5985, 21519, 48025, 11571, 11808, 64914, 86332, 11703, 67639, 37124, 59663, 26221, 20251, 15623, 20617, 9783, 63668, 367, 19941, 80900, 24151, 6928, 52645, 67576, 85517, 80743, 62429, 6908, 15276, 68028, 17707, 3605, 67365, 10628, 635, 62002, 8645, 14922, 75696, 279, 17494, 55928, 19741, 30663, 15090, 1381, 65109, 4154, 59487, 2679, 7206, 5191, 9383, 19454, 17949, 63292, 4502, 664, 2392, 26889, 20351, 53693, 20759, 5821, 80793, 1018, 8219, 66083, 20600, 23156, 17339, 18558, 1583, 3998, 14089, 59466, 23019, 1885, 7298, 17446, 11910, 17463, 47902, 87101, 282, 13038, 8458, 48142, 80297, 10717, 7564, 22297, 55990, 3469, 25985, 13628, 68729, 5039, 66692, 68289, 23900, 12671, 72523, 17351, 69105, 71646, 9706, 23191, 10456, 70467, 18834, 14373, 3062, 16904, 55882, 49540, 3166, 21940, 19295, 12503, 12182, 85485, 44562, 6574, 69809, 82230, 3673, 4073, 8885, 10800, 60523, 15645, 72312, 10530, 3502, 6290, 7685, 30221, 20835, 71896, 2017, 13235, 50725, 26852, 25179, 20120, 13769, 39001, 25621, 85178, 78352, 8141, 86314, 58555, 19287, 45830, 18557, 686, 18520, 23222, 3754, 7090, 16474, 75528, 12975, 2442, 9322, 24540, 51171, 12200, 14419, 19239, 4825, 13064, 63298, 15685, 16217, 79200, 43619, 4544, 15174, 20764, 80902, 1461, 18166, 82535, 21542, 52503, 12315, 13380, 2664, 15260, 70393, 31309, 595, 19640, 19062, 17556, 15514, 11027, 14398, 1145, 66563, 20981, 17098, 7023, 18739, 14274, 40817, 18154, 85052, 83549, 275, 47238, 26861, 82028, 38473, 20014, 65067, 12821, 16675, 57990, 58547, 15321, 20773, 22547, 273, 78385, 7677, 21572, 15434, 4863, 28734, 15493, 20014, 4440, 54464, 8430, 5745, 2949, 17141, 21710, 77968, 12485, 6925, 14502, 8678, 59365, 44672, 19912, 7087, 73, 38244, 69391, 19716, 14965 }
    ));
}

TEST(LargestArea, case7)
{
    std::vector<int> const output = { 610459982, 516975250, 477238500, 392091948, 347802257, 347802257, 196220150, 149751700, 115684746, 115684746, 115684746, 106104690, 69622500, 69622500, 69622500, 69622500, 69622500, 69622500, 69622500, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 45672360, 32078400, 32078400, 32078400, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 17456160, 10143732, 10143732, 10143732, 10143732, 10143732, 10143732, 10143732, 10143732, 10143732, 5947673, 5947673, 5947673, 5947673, 5947673, 5947673, 5947673, 5947673, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5716094, 5382544, 5382544, 5382544, 5382544, 5382544, 5382544, 5382544, 5382544, 5382544, 5382544, 5382544, 5337753, 5337753, 5337753, 5337753, 5337753, 4740222, 4740222, 4740222, 4740222, 4740222, 4740222, 4740222, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4633486, 4622050, 4622050, 4622050, 4622050, 3428950, 3428950, 3428950, 3428950, 3428950, 3428950, 3428950, 3063431, 3063431, 3063431, 3063431, 3063431, 3063431, 3063431, 3051412, 3051412, 3051412, 3051412, 3051412, 3051412, 3051412, 3051412, 3051412, 3051412, 3051412, 3051412, 2716294, 2716294, 2716294, 2716294, 2716294, 2716294, 2716294, 2716294, 2716294, 2687307, 2082948, 2082948, 2082948, 2082948, 2082948, 2082948, 2082948, 1848952, 1848952, 1848952, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1815524, 1787028, 1787028, 1787028, 1787028, 1787028, 1787028, 1787028, 1787028, 1692459, 1692459, 1692459, 1692459, 1692459, 1692459, 1692459, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1496799, 1493538, 1493538, 1493538, 1493538, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1426212, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1133496, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1093014, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 1068102, 989898, 989898, 989898, 823886, 823886, 823886, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 576480, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 526038, 415546, 415546, 304999, 304999, 304999, 304999, 304999, 304999, 304999, 304999, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 231647, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 184782, 172731, 171183, 171183, 171183, 171183, 171183, 171183, 171183 };
    EXPECT_EQ(output, getMaxArea(78034, 10336,
        { 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1 },
        { 2513, 3711, 5998, 9154, 14135, 71, 50185, 7865, 34243, 873, 49102, 4055, 5365, 3411, 92, 17407, 39060, 9230, 8388, 6673, 8873, 13806, 320, 8990, 33511, 3850, 8951, 5790, 28051, 3733, 9680, 17386, 4902, 9420, 69745, 8461, 25, 60797, 37310, 64895, 3663, 2691, 12435, 72736, 6078, 37460, 9440, 55822, 10905, 5069, 9389, 13231, 71885, 813, 4977, 7116, 1826, 1839, 6779, 33509, 3041, 10452, 8231, 197, 42861, 23138, 17250, 33290, 8361, 6626, 56800, 8310, 8744, 48080, 7838, 3768, 25031, 4686, 8434, 5802, 7146, 60853, 22296, 9089, 7586, 4906, 71038, 4264, 14843, 8869, 9601, 4388, 19161, 55786, 56551, 26047, 11468, 4853, 2835, 6273, 8866, 7937, 43433, 4733, 59302, 32384, 9139, 64697, 5648, 35481, 9259, 9024, 23653, 38132, 3750, 4815, 5070, 74192, 55871, 674, 46667, 9244, 74003, 571, 53200, 4307, 7912, 18789, 2496, 8502, 10825, 786, 27299, 50885, 3370, 6687, 3550, 46658, 7886, 6707, 16366, 10226, 2934, 5669, 6095, 2105, 4815, 8572, 17923, 8602, 12169, 2728, 5192, 2146, 15906, 3303, 23034, 1580, 3374, 9652, 61509, 8990, 38987, 46494, 67765, 9904, 10109, 23287, 8879, 4205, 6312, 32367, 5098, 5041, 720, 4085, 1925, 590, 48938, 21288, 72930, 4704, 49477, 29989, 57626, 4562, 59851, 2521, 32453, 3322, 72092, 1718, 77566, 1408, 69321, 3564, 2837, 6857, 16020, 7222, 39548, 28097, 61487, 74841, 10358, 2087, 4561, 8316, 11967, 126, 70241, 3266, 11422, 66288, 59576, 3820, 5487, 63723, 9824, 32474, 10196, 26346, 65925, 29375, 5136, 8347, 743, 46853, 2720, 63760, 5086, 4691, 44674, 37603, 2495, 349, 514, 738, 67039, 20660, 5832, 55640, 45590, 9911, 889, 56903, 64102, 866, 39600, 3661, 39213, 56, 256, 73764, 54990, 436, 6168, 7131, 2998, 29543, 4822, 69375, 7078, 1348, 51919, 58784, 70683, 59047, 69992, 6966, 33277, 4066, 18139, 77583, 3577, 9710, 7598, 67274, 66918, 63802, 9131, 945, 54884, 4171, 35244, 42714, 9365, 2380, 8082, 289, 10268, 2016, 8945, 42760, 25144, 46619, 4826, 52343, 17656, 4478, 18301, 53858, 3796, 3252, 14614, 2291, 5153, 3285, 1728, 3986, 62732, 349, 9956, 13606, 67410, 2592, 2989, 365, 4182, 4045, 9155, 39245, 35971, 8582, 15649, 46890, 1288, 76813, 353, 5573, 8447, 4901, 5868, 904, 75992, 48152, 21758, 2585, 5188, 6682, 6411, 9809, 5702, 39041, 5550, 6349, 45094, 5441, 10297, 8057, 31475, 8776, 76485, 8697, 976, 51223, 236, 7002, 59449, 2542, 26307, 3693, 7573, 6812, 56446, 65973, 46267, 52851, 916, 5323, 3265, 21141, 12166, 6293, 55966, 9380, 6722, 6393, 2902, 320, 12946, 9832, 8822, 2287, 3803, 9029, 3641, 9568, 366, 9725, 4675, 7375, 2256, 58323, 4583, 9564, 70269, 8295, 7426, 6610, 8178, 53151, 7999, 7881, 24458, 4089, 8132, 17051, 11359, 20822, 5810, 70281, 8514, 37795, 536, 1874, 2441, 10190, 53275, 4237, 53, 4713, 3291, 55582, 5950, 9262, 67035, 2636, 9601, 5699, 44068, 20488, 38128, 1414, 56818, 32083, 56707, 2296, 58783, 4687, 1777, 70737, 935, 49, 2924, 66231, 58495, 43137, 4214, 7390, 9673, 69008, 43681, 462, 2964, 8005, 11601, 5384, 10358, 2944, 65, 1883, 38436, 30019, 28564, 11207, 5555, 8598, 31492, 21447, 39828, 15974, 5063, 40312, 4349, 5305, 1164, 6695, 50408, 21622, 31058, 10062, 58443, 5407, 10544, 62844, 5339, 9722, 51041, 30596, 708, 2583, 28542, 6492, 2507, 7348, 4218, 5366, 3542, 2889, 2882, 9426, 7891, 49577, 9055, 4188, 9939, 774, 3463, 2019, 361, 800, 6175, 76906, 4982, 34558, 60396, 8004, 7009, 2153, 56463, 9387, 17958, 1253, 1813, 2529, 5474, 3892, 8271, 30156, 2023, 9684, 30999, 8207, 63388, 2880, 30827, 7726, 67889, 16249, 3112, 6930, 5808, 2246, 62644, 3552, 66819, 1540, 181, 10293, 2743, 3596, 9895, 5188, 2929, 1564, 2170, 32122, 6929, 4986, 9996, 8951, 3162, 1392, 46248, 2448, 46774, 53604, 1823, 18476, 9102, 7548, 8149, 70894, 3282, 26149, 6419, 412, 6877, 37605, 3950, 57871, 6310, 73098, 5621, 2688, 4570, 76042, 2443, 4808, 1002, 9545, 42075, 44841, 1071, 9226, 64380, 67324, 1292, 9977, 40834, 3154, 738, 76437, 3945, 38153, 73400, 623, 5972, 9025, 5475, 4992, 1828, 6835, 3483, 7351, 21643, 44301, 6587, 28710, 1538, 76297, 1913, 32819, 6910, 63612, 6828, 27225, 54866, 2445, 6085, 38369, 43700, 2742, 58501, 20534, 48370, 3305, 905, 6758, 21526, 5244, 25931, 63152, 7770, 9667, 2832, 50364, 5975, 9510, 7423, 38394, 4189, 7110, 3690, 21309, 6864, 2593, 10102, 54688, 4693, 23633, 3979, 685, 4526, 30720, 28381, 9569, 9545, 7888, 3241, 4714, 2161, 39113, 725, 33472, 70910, 3842, 42490, 35640, 7806, 709, 3526, 239, 77107, 7477, 4805, 56290, 9297, 44628, 2593, 76207, 57594, 75288, 8027, 60897, 73224, 1278, 6471, 2678, 43052, 2088, 4832, 31511, 9682, 29206, 239, 2829, 1181, 12402, 9990, 5848, 28892, 23710, 7781, 6323, 59628, 9163, 2237, 48038, 1842, 7490, 3634, 8272, 1700, 3545, 10092, 2687, 44330, 50546, 11844, 4568, 5600, 26544, 34851, 43552, 5788, 720, 22178, 34942, 9497, 2677, 56422, 8796, 4064, 5239, 5994, 46257, 21624, 4782, 37519, 76121, 31290, 139, 5688, 239, 44521, 7654, 2474, 7154, 92, 3464, 54987, 58396, 60234, 45080, 1840, 26243, 47963, 51653, 67380, 6893, 8933, 9117, 9136, 10041, 6617, 3674, 6708, 15124, 9551, 2334, 65532, 50832, 1155, 5666, 1186, 8824, 71342, 3083, 1516, 49626, 4314, 64217, 3262, 69373, 5078, 5645, 1366, 20535, 56278, 42055, 10272, 20668, 7437, 2448, 2088, 38862, 10150, 4551, 584, 17171, 2592, 54481, 75385, 23814, 51070, 4623, 32164, 9561, 5953, 32363, 9559, 2428, 55107, 43824, 75839, 6737, 65305, 8921, 4219, 68077, 3206, 5986, 14608, 56804, 3977, 6139, 6737, 57377, 7737, 34370, 67329, 8713, 69887, 7700, 29005, 2808, 5583, 5472, 1755, 3668, 72208, 34852, 14881, 27957, 5777, 31414, 5919, 24444, 30532, 42593, 41439, 15531, 8336, 1972, 59037, 74525, 3958, 5687, 8135, 2881, 686, 59711, 4562, 5136, 48510, 33517, 64864, 5681, 34747, 2075, 21135, 43884, 35566, 1108, 22462, 1984, 6715, 65908, 25175, 42975, 3867, 4912, 4517, 36702, 51586, 3313, 441, 4877, 3949, 75176 }
    ));
}