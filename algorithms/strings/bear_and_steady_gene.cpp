// MEDIUM https://www.hackerrank.com/challenges/bear-and-steady-gene/problem	

#include <gtest/gtest.h>

#include <algorithm>
#include <string>

namespace {

	int steadyGene(std::string const& gene) {
		
		auto stableCount = gene.size() / 4; // Once we have this many of each letter, we have a stable gene

		std::map<char, int> geneCount;
		std::for_each(gene.begin(), gene.end(), [&geneCount](char c) { geneCount[c]++; });
		// If we already have a stable gene, we can return 0
		if (std::all_of(geneCount.begin(), geneCount.end(), [stableCount](auto const& p) { return p.second == stableCount; })) {
			return 0;
		}
		// Otherwise we need to find the smallest substring that contains all the letters
		// We can do this by using a sliding window
		size_t left{ 0 }, right{ 0 };
		auto leftIter = gene.begin();
		auto rightIter = gene.begin();
		auto minLen{ gene.size() }; // Initialize the window
		while (right < gene.size()) {
			// Expand the window
			// Move the right pointer until we have a stable gene
			geneCount[gene[right]]--;
			++right;
			++rightIter;

			// Move the left pointer until we no longer have a stable gene
			while (std::all_of(geneCount.begin(), geneCount.end(), [stableCount](auto const& p) { return p.second <= stableCount; })) {
				minLen = std::min(minLen, right - left + 1);
				geneCount[gene[left]]++;
				left++;
				++leftIter;
			}
		}


		return minLen;

	}
}

TEST(BearAndSteadyGene, DISABLED_example) {
	EXPECT_EQ(3, steadyGene("ACTGAAAG"));
}

TEST(BearAndSteadyGene, DISABLED_sample0) {
	EXPECT_EQ(5, steadyGene("GAAATAAA"));
}

TEST(BearAndSteadyGene, DISABLED_sample1) {
	EXPECT_EQ(0, steadyGene("TGATGCCGTCCCCTCAACTTGAGTGCTCCTAATGCGTTGC"));
}