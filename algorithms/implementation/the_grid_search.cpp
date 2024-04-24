#include "gtest/gtest.h"

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

std::string gridSearch(std::vector<std::string> G, std::vector<std::string> P) {

	if (G.size() < P.size())
		return "NO";

	auto const& first = P.front();
	size_t patternSize = P.front().size();
	auto const& firstPattern = P.front();
	auto const gridEnd = std::prev(G.end(), P.size() - 1); // We can 'end' searching only this 
	for (auto gridIter = G.begin(); gridIter != gridEnd; ++gridIter)
	{
		// Improbably, but...
		// If the line is empty or shorter than the size of the pattern, we continue
		if (gridIter->empty() || (gridIter->size() < first.size()))
			continue;
		// If the pattern is not present in this row of the grid, continue
		// The row can contain the pattern multiple times (i.e. 11111111 contains several 11's
		// For each one, try to find if all patterns match at the specific offset
		size_t loc = gridIter->find(firstPattern);
		while (loc != std::string::npos)
		{
			auto gIter = gridIter;
			auto success(true);
			for(auto const & pattern : P)
			{
				auto rowLine = gIter->substr(loc, patternSize);
				if (rowLine != pattern)
				{
					success = false;
					break;
				}
				++gIter;
			}
			if (success)
				return "YES";
			loc = gridIter->find(firstPattern, loc + 1);

		}

	}

	return "NO";
}

TEST(gridSearch, sample)
{
	EXPECT_EQ("YES", gridSearch({ "7283455864", "6731158619", "8988242643", "3830589324", "2229505813", "5633845374", "6473530293", "7053106601", "0834282956", "4607924137" }, { "9505", "3845", "3530" }));
	EXPECT_EQ("NO", gridSearch({ "400453592126560", "114213133098692", "474386082879648", "522356951189169", "887109450487496", "252802633388782", "502771484966748", "075975207693780", "511799789562806", "404007454272504", "549043809916080", "962410809534811", "445893523733475", "768705303214174", "650629270887160" }, { "99", "99" }));
}

TEST(gridSearch, case_0)
{
	EXPECT_EQ("NO", gridSearch({ "34889246430321978567", "58957542800420926643", "35502505614464308821", "14858224623252492823", "72509980920257761017", "22842014894387119401", "01112950562348692493", "16417403478999610594", "79426411112116726706", "65175742483779283052", "89078730337964397201", "13765228547239925167", "26113704444636815161", "25993216162800952044", "88796416233981756034", "14416627212117283516", "15248825304941012863", "88460496662793369385", "59727291023618867708", "19755940017808628326" }, { "1641", "7942", "6517", "8907", "1376", "2691", "2599" }));
	EXPECT_EQ("YES", gridSearch({ "7652157548860692421022503", "9283597467877865303553675", "4160389485250089289309493", "2583470721457150497569300", "3220130778636571709490905", "3588873017660047694725749", "9288991387848870159567061", "4840101673383478700737237", "8430916536880190158229898", "8986106490042260460547150", "2591460395957631878779378", "1816190871689680423501920", "0704047294563387014281341", "8544774664056811258209321", "9609294756392563447060526", "0170173859593369054590795", "6088985673796975810221577", "7738800757919472437622349", "5474120045253009653348388", "3930491401877849249410013", "1486477041403746396925337", "2955579022827592919878713", "2625547961868100985291514", "3673299809851325174555652", "4533398973801647859680907" }, { "5250", "1457", "8636", "7660", "7848" }));
}

TEST(gridSearch, case_13)
{
	EXPECT_EQ("YES", gridSearch({ "123456", "567890", "234567", "194729" }, { "2345", "6789", "3456", "9472" }));
}


TEST(gridSearch, case_15)
{
	EXPECT_EQ("YES", gridSearch({ "111111111111111", "111111111111111", "111111111111111", "111111011111111", "111111111111111", "111111111111111", "101010101010101" }, { "11111", "11111", "11111", "11110" }));
}