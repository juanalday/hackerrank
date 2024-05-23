// MEDIUM https://www.hackerrank.com/challenges/bear-and-steady-gene/problem	

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>

namespace {

	int steadyGene(std::string const& gene) {
		auto stableCount = gene.size() / 4; // Once we have this many of each letter, we have a stable gene

		std::map<char, int> geneCount;
		std::for_each(gene.begin(), gene.end(), [&geneCount](char c) { geneCount[c]++; });
		auto isStable = [&]() {return std::all_of(geneCount.begin(), geneCount.end(), [stableCount](auto const& p) { return p.second <= stableCount; }); };

		// If we already have a stable gene, we can return 0
		if (isStable())
			return 0;

		int minLen = INT_MAX;
		auto leftIter = gene.begin();
		for (auto rightIter = gene.begin(); rightIter != gene.end(); ++rightIter) {
			--geneCount[*rightIter];

			while (isStable())
			{
				minLen = std::min(minLen, static_cast<int>(std::distance(leftIter, rightIter) + 1));
				++geneCount[*leftIter];
				++leftIter;
			}
		}
		return minLen;
	}
}

TEST(BearAndSteadyGene, example) {
	EXPECT_EQ(2, steadyGene("ACTGAAAG"));
}

TEST(BearAndSteadyGene, sample0) {
	EXPECT_EQ(5, steadyGene("GAAATAAA"));
}

TEST(BearAndSteadyGene, sample1) {
	EXPECT_EQ(5, steadyGene("TGATGCCGTCCCCTCAACTTGAGTGCTCCTAATGCGTTGC"));
}