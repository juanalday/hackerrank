// HARD https://www.hackerrank.com/challenges/string-function-calculation/problem

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <algorithm>
#include <numeric>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using ::testing::ElementsAre;

namespace {

	struct SuffixArray {
		int m_len; // Length of the input string
		std::vector<std::vector<int>> m_suffixArray; // 2D vector to store ranks of suffixes at different levels
		std::vector<std::tuple<int, int, int>> m_ranks; // Vector to store tuples for sorting

		// Constructor to initialize the SuffixArray object
		SuffixArray(const std::string& s)
			: m_len(static_cast<int>(s.length()))
			, m_suffixArray(1, std::vector<int>(m_len, 0))
			, m_ranks(m_len)
		{
			// Initialize rank of suffixes based on the first character
			std::transform(s.begin(), s.end(), m_suffixArray[0].begin(), [](auto c) { return static_cast<int>(c); });

			// Build the suffix array
			for (int skip = 1, level = 1; skip < m_len; skip *= 2, level++) {
				m_suffixArray.push_back(std::vector<int>(m_len, 0));

				// Create tuples of (current rank, next rank, index) for each suffix
				for (int i = 0; i < m_len; i++) {
					auto current = m_suffixArray[level - 1][i];
					auto newIndex = i + skip;
					auto newRank = (newIndex < m_len) ? m_suffixArray[level - 1][newIndex] : -1;
					m_ranks[i] = std::make_tuple(current, newRank, i); // current rank, next rank, index
				}

				// Sort the suffix tuples
				std::sort(m_ranks.begin(), m_ranks.end());

				// Assign new rank to the suffixes
				std::tuple<int, int, int> current, previous(m_ranks[0]);
				for (int i = 0; i < m_len; i++) {
					m_suffixArray[level][std::get<2>(m_ranks[i])] = i;
					if (i == 0)
						continue;
					if (std::get<0>(m_ranks[i]) == std::get<0>(m_ranks[i - 1]) &&
						std::get<1>(m_ranks[i]) == std::get<1>(m_ranks[i - 1])) {
						m_suffixArray[level][std::get<2>(m_ranks[i])] = m_suffixArray[level][std::get<2>(m_ranks[i - 1])];
					}
					current = previous;
				}
			}
		}

		// Function to get the suffix array
		std::vector<int> GetSuffixArray() {
			return m_suffixArray.back();
		}

		// Function to find the longest common prefix of suffixes starting at i and j
		int LongestCommonPrefix(int i, int j) {
			int lcpLength = 0;
			if (i == j) return m_len - i;

			// Iterate through levels of suffixRanks from top to bottom
			for (int k = m_suffixArray.size() - 1; k >= 0 && i < m_len && j < m_len; k--) {
				if (m_suffixArray[k][i] == m_suffixArray[k][j]) {
					i += 1 << k;
					j += 1 << k;
					lcpLength += 1 << k;
				}
			}
			return lcpLength;
		}

		// Function to calculate the maximum area of the histogram
		int getMaxArea() {
			std::vector<int> histogram;

			// Build the histogram using the suffix array and LCP
			{
				std::vector<int> suffixArray = GetSuffixArray();
				std::vector<int> rankArray(m_len);
				for (int i = 0; i < suffixArray.size(); i++)
					rankArray[suffixArray[i]] = i;

				for (int i = 0; i < m_len - 1; i++)
					histogram.push_back(LongestCommonPrefix(rankArray[i], rankArray[i + 1]));
			}

			int n = histogram.size();
			std::stack<int> indexStack;
			int maxArea = 0;
			int topIndex;
			int areaWithTop;

			int i = 0;
			while (i < n) {
				if (indexStack.empty() || histogram[indexStack.top()] <= histogram[i]) {
					indexStack.push(i++);
				}
				else {
					topIndex = indexStack.top();
					indexStack.pop();
					areaWithTop = histogram[topIndex] * (indexStack.empty() ? i + 1 : i - indexStack.top());
					if (maxArea < areaWithTop)
						maxArea = areaWithTop;
				}
			}

			while (!indexStack.empty()) {
				topIndex = indexStack.top();
				indexStack.pop();
				areaWithTop = histogram[topIndex] * (indexStack.empty() ? i + 1 : i - indexStack.top());
				if (maxArea < areaWithTop)
					maxArea = areaWithTop;
			}

			return maxArea;
		}
	};

	std::vector<int> bruteForceSuffixArray(std::string const& str) {
		std::vector<std::string> suffixes(str.size());
		std::vector<int> suffixArray(str.size(), str.size());

		// Create suffixes
		for (auto i = 0; i < str.size(); ++i) suffixes[i] = str.substr(i);

		// Sort the suffixes
		std::sort(suffixes.begin(), suffixes.end());

		// Store the starting indices of the sorted suffixes in the suffix array
		std::transform(suffixes.begin(), suffixes.end(), suffixArray.begin(), [len = str.size()](std::string const& s) {return static_cast<int>(len - s.size()); });

		return suffixArray;
	}


	// Prefix-doubling algo to build a suffixArray
	std::vector<int> suffixArray(std::string const& str) {
		int len = static_cast<int>(str.size());

		// I will create a vector of tuples, describing the ranks, the next ranks and the suffixes (meaning rank of the next suffix + k)
		std::vector<std::tuple<int, int, int>> rankedSuffixes(str.size());
		// initial ranks are the ASCII values of the chars, and for id I pick o to n-1. the next-rank is -1 for now
		transform(str.begin(), str.end(), rankedSuffixes.begin(), [i = 0](auto c) mutable {return std::make_tuple(c, -1, i++); });
		// Adjust next-rank to rank of the next element. We won't touch the last one obviously
		// In this case, it means the ascii value of the next char
		for (int i = 0; i < (len - 1); ++i) std::get<1>(rankedSuffixes[i]) = std::get<0>(rankedSuffixes[i + 1]);

		// Since tuple is rank-followingTank-index, this sorts according to rank value
		sort(rankedSuffixes.begin(), rankedSuffixes.end());
		for (int skip = 1; skip < 2*len; skip *= 2)
		{
			std::adjacent_difference(rankedSuffixes.begin(), rankedSuffixes.end(), rankedSuffixes.begin(),
				[&, rank = 0](auto curr, auto const& prev) mutable  {
					rank += ((std::get<0>(prev) == std::get<0>(curr)) && (std::get<1>(prev) == std::get<1>(curr))) ? 0 : 1;
					std::get<0>(curr) = rank;
					std::get<1>(curr) = -1;
					return curr;
				});
			std::get<0>(rankedSuffixes[0]) = 0;


			// I sort according to index, as I will use it to get the next index
			sort(rankedSuffixes.begin(), rankedSuffixes.end(), [](auto const& lhs, auto const& rhs) {return std::get<2>(lhs) < std::get<2>(rhs); });

			// I will now adjust the values of rank[sa[i]+k] for all i's within range
			if (skip < len) {
				std::transform(std::next(rankedSuffixes.begin(), skip), rankedSuffixes.end(), rankedSuffixes.begin(), rankedSuffixes.begin(),
					[](auto const& skipRank, auto  currentRank) {std::get<1>(currentRank) = std::get<0>(skipRank); return currentRank; });
			}
			sort(rankedSuffixes.begin(), rankedSuffixes.end());
			// Optimization: If the last element has rank == len - 1, we can stop
			if (skip > 1 && (std::get<0>(rankedSuffixes[0]) == len - 1) )break;


		}

		std::vector<int> suffixes(len);
		transform(rankedSuffixes.begin(), rankedSuffixes.end(), suffixes.begin(), [](auto const& tup) {return std::get<2>(tup); });
		return suffixes;
	}


	// Check https://visualgo.net/en/suffixarray?slide=1 to generate tests. This one is Kasai.
	std::vector<int> lcpArray(std::string const& str, std::vector<int> const& sa)
	{
		int n = static_cast<int>(sa.size());
		std::vector<int> lcpWithPrev(n); // To store LCP with the previous suffix

		std::vector<int> prevSuffix(n, -1);  // To store the index of the previous suffix in the suffix array
		int lcpLength(0);  // Length of the current longest common prefix

		// Compute the prevSuffix array
		for (int i = 1; i < n; ++i) prevSuffix[sa[i]] = sa[i - 1];

		// Compute lcpWithPrev using the prevSuffix array
		for (int i = 0; i < n; ++i) {
			if (prevSuffix[i] == -1) {
				lcpWithPrev[i] = 0;
				continue;
			}

			// Calculate the longest common prefix length
			while (str[i + lcpLength] == str[prevSuffix[i] + lcpLength]) {
				++lcpLength;
			}
			lcpWithPrev[i] = lcpLength; // Store the LCP length with the previous suffix
			lcpLength = std::max(lcpLength - 1, 0); // Decrease lcpLength for the next iteration
		}

		// Construct the final LCP array from lcpWithPrev
		//for (int i = 0; i < n; ++i) lcp[i] = lcpWithPrev[sa[i]];
		std::vector<int> lcp(n, 0); // To store the final LCP array
		std::transform(sa.begin(), sa.end(), lcp.begin(), [&lcpWithPrev](int i) {return lcpWithPrev[i]; });
		return lcp;
	}

	std::vector<int> lcpArray(std::string const& str) {
		return lcpArray(str, suffixArray(str));
	}

	int maxValue(std::string const& str)
	{
		auto lcp = lcpArray(str);
		int n = static_cast<int>(lcp.size());
		std::stack<int> s;
		int i{ 0 }, maxArea{ 0 };
		while (i < n)
		{
			if (s.empty() || lcp[s.top()] <= lcp[i]) {
				s.push(i++);
			}
			else {
				auto topIndex = s.top();  // store the top index
				s.pop();  // pop the top
				auto currentTop = s.empty() ? -1 : s.top();
				auto first = lcp[topIndex];
				auto multiplier = (s.empty() ? i + 1 : i - s.top());
				if (first == 300)
				{
					first = 300;
				}
				int area = lcp[topIndex] * multiplier;
				maxArea = std::max(area, maxArea);
			}
		}
		while (!s.empty())
		{
			auto topIndex = s.top();  // store the top index
			s.pop();
			auto currentTop = s.empty() ? -1 : s.top();
			auto multiplier = (s.empty() ? i + 1 : i - s.top());
			int area = lcp[topIndex] * multiplier;
			maxArea = std::max(area, maxArea);
		}
		maxArea = std::max(maxArea, static_cast<int>(str.size())); // The whole string


		return maxArea;
	}


}

TEST(StringFunctionCalculation, suffixArray)
{
	EXPECT_THAT(suffixArray("aaaaaa"),           ElementsAre(5, 4, 3, 2, 1, 0));
	EXPECT_THAT(bruteForceSuffixArray("aaaaaa"), ElementsAre(5, 4, 3, 2, 1, 0));
	EXPECT_THAT(SuffixArray("aaaaaa").GetSuffixArray(), ElementsAre(5, 4, 3, 2, 1, 0));
	EXPECT_THAT(suffixArray("aaaaaaa"),           ElementsAre(6, 5, 4, 3, 2, 1, 0));
	EXPECT_THAT(bruteForceSuffixArray("aaaaaaa"), ElementsAre(6, 5, 4, 3, 2, 1, 0));
	EXPECT_THAT(SuffixArray("aaaaaaa").GetSuffixArray(), ElementsAre(6, 5, 4, 3, 2, 1, 0));
	EXPECT_THAT(suffixArray("abaaaa"), ElementsAre(5, 4, 3, 2, 0 , 1));
	EXPECT_THAT(bruteForceSuffixArray("abaaaa"), ElementsAre(5, 4, 3, 2, 0, 1));
	EXPECT_THAT(SuffixArray("abaaaa").GetSuffixArray(), ElementsAre(5, 4, 3, 2, 0, 1));
	EXPECT_THAT(bruteForceSuffixArray("abaaaa"), ElementsAre(5, 4, 3, 2, 0, 1));

	EXPECT_THAT(bruteForceSuffixArray("AAAAA$"), ElementsAre(5, 4, 3, 2, 1, 0));
	EXPECT_THAT(suffixArray("banana"), ElementsAre(5, 3, 1, 0, 4, 2));
	EXPECT_THAT(suffixArray("aaaaaaa"), ElementsAre(6, 5, 4, 3, 2, 1, 0));
	EXPECT_THAT(suffixArray("AAAAAA$"), ElementsAre(6, 5, 4, 3, 2, 1, 0));
	EXPECT_THAT(suffixArray("ABCABCDDD"), ElementsAre(0, 3, 1, 4, 2, 5, 8, 7, 6));
	EXPECT_THAT(suffixArray("ABCABCDDD$"), ElementsAre(9, 0, 3, 1, 4, 2, 5, 8, 7, 6));
	EXPECT_THAT(suffixArray("abcabcddd"), ElementsAre(0, 3, 1, 4, 2, 5, 8, 7, 6));
	EXPECT_THAT(bruteForceSuffixArray("banana"), ElementsAre(5, 3, 1, 0, 4, 2));
	EXPECT_THAT(bruteForceSuffixArray("AAAAAA$"), ElementsAre(6, 5, 4, 3, 2, 1, 0));
	EXPECT_THAT(bruteForceSuffixArray("ABCABCDDD"), ElementsAre(0, 3, 1, 4, 2, 5, 8, 7, 6));
	EXPECT_THAT(bruteForceSuffixArray("ABCABCDDD$"), ElementsAre(9, 0, 3, 1, 4, 2, 5, 8, 7, 6));
	EXPECT_THAT(bruteForceSuffixArray("abcabcddd"), ElementsAre(0, 3, 1, 4, 2, 5, 8, 7, 6));

	std::string input = "aacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccb";
	EXPECT_EQ(suffixArray(input), bruteForceSuffixArray(input));
	auto blah = bruteForceSuffixArray(input);
	auto subString = input.substr(0, 6);

	auto mine = suffixArray(subString);
	auto other = bruteForceSuffixArray(subString);
	auto yours = SuffixArray(subString).GetSuffixArray();
	EXPECT_EQ(mine, yours);
	int counter(0);
	while (mine == yours) {
		++counter;
		if (subString.size() * 2 > input.size())
			subString = input;
		else
			subString = input.substr(0, 2 * subString.size()); // double every time
		mine = suffixArray(subString);
		yours = SuffixArray(subString).GetSuffixArray();
		EXPECT_EQ(mine, yours);
		if (subString == input)
			break;
	}


	subString = "aaaa";
	mine = suffixArray(subString);
	yours = SuffixArray(subString).GetSuffixArray();
	counter = 0;
	while (mine == yours) {
		++counter;
		subString.append(subString.size(), 'a'); // double every time
		mine = suffixArray(subString);
		yours = SuffixArray(subString).GetSuffixArray();
	}
	SuffixArray suffix("aaaaaa");

}

TEST(StringFunctionCalculation, lcpArray)
{
	EXPECT_THAT(lcpArray("banana"), ElementsAre(0, 1, 3, 0, 0, 2));
	EXPECT_THAT(lcpArray("aaaaaa"), ElementsAre(0, 1, 2, 3, 4, 5));
	EXPECT_THAT(lcpArray("AAAAAA$"), ElementsAre(0, 0, 1, 2, 3, 4, 5));
	EXPECT_THAT(lcpArray("abcabcddd"), ElementsAre(0, 3, 0, 2, 0, 1, 0, 1, 2));
}

TEST(StringFunctionCalculation, sample0)
{
	EXPECT_EQ(12, maxValue("aaaaaa"));
	// f('a')      = 1*6 = 6 
	// f('aa')     = 2*5 = 10
	// f('aaa')    = 3*4 = 12
	// f('aaaa')   = 4*3 = 12
	// f('aaaaa')  = 5*2 = 10
	// f('aaaaaa') = 6*1 = 6
}

TEST(StringFunctionCalculation, sample1)
{
	EXPECT_EQ(9, maxValue("abcabcddd"));
	// f('a')         = 1*2 = 2
	// f('b')         = 1*2 = 2
	// f('c')         = 1*2 = 2
	// f('d')         = 1*3 = 3
	// f('dd')        = 2*2 = 4
	// f('ddd')       = 3*1 = 3
	// f('ab')        = 2*2 = 4
	// f('bc')        = 2*2 = 4
	// f('abc')       = 3*2 = 6
	// f('abcabcddd') = 9*1 = 9
}

TEST(StringFunctionCalculation, case0)
{
	EXPECT_EQ(12, maxValue("aaaaaa"));
	// f('a')      = 1*6 = 6 
	// f('aa')     = 2*5 = 10
	// f('aaa')    = 3*4 = 12
	// f('aaaa')   = 4*3 = 12
	// f('aaaaa')  = 5*2 = 10
	// f('aaaaaa') = 6*1 = 6
}

TEST(StringFunctionCalculation, case1)
{
	EXPECT_EQ(9, maxValue("abcabcddd"));
	// f('a')         = 1*2 = 2
	// f('b')         = 1*2 = 2
	// f('c')         = 1*2 = 2
	// f('d')         = 1*3 = 3
	// f('dd')        = 2*2 = 4
	// f('ddd')       = 3*1 = 3
	// f('ab')        = 2*2 = 4
	// f('bc')        = 2*2 = 4
	// f('abc')       = 3*2 = 6
	// f('abcabcddd') = 9*1 = 9
}

TEST(StringFunctionCalculation, case2)
{
	std::string const input = "aacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccbaacbbabbabbbbbaaaaaaabbbbcacacbcabaccaabbbcaaabbccccbbbcbccccbbcaabaaabcbaacbcbaccaaaccbccbcaacbaccb";

	SuffixArray suffix(input);
	auto sa = suffix.GetSuffixArray();

	EXPECT_EQ(900, suffix.getMaxArea());
	EXPECT_EQ(900, SuffixArray(input).getMaxArea());
	EXPECT_EQ(900, maxValue(input));
}

TEST(StringFunctionCalculation, case4)
{
	std::string const input = "abcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"defabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcab"
		"cabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabc"
		"defabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabca"
		"bcdefabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabc"
		"abcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcab"
		"cdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabca"
		"bcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcd"
		"efabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcdefabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefa"
		"bcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabc"
		"abcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabca"
		"bcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabc"
		"abcdefabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcab"
		"cdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefa"
		"bcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabca"
		"bcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabc"
		"abcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcabca"
		"bcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefa"
		"bcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcde"
		"fabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcdefabcabcabcabcdefabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabc"
		"abcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcdefab"
		"cabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabca"
		"bcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"defabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcdefabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcdefabcabcabcabcabcab"
		"cabcabcabcabcdefabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcdefabcabcabcabcabcab"
		"cabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabca"
		"bcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"defabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabc"
		"abcdefabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcab"
		"cabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcd"
		"efabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabc"
		"defabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefab"
		"cabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcdef"
		"abcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcdefabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabc"
		"abcabcdefabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcab"
		"cdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabca"
		"bcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabca"
		"bcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcabcabc"
		"abcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcdefabcabca"
		"bcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabc"
		"abcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabca"
		"bcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"
		"abcabcdefabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabca"
		"bcabcabcabcabcdefabcabcdefabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcab"
		"cdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcdefabcabca"
		"bcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcdefabc"
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcdefabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcdefabcabcabca"
		"bcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcdefabcabcdefabcabcabcabcdefabcabcabcabcabcabcabcabcdef"
		"abcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcab"
		"cabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabcabcabcabcabcabcabcabcdefabcabcabcabcabcabc";
	EXPECT_EQ(69870, maxValue(input));

}
TEST(StringFunctionCalculation, case10)
{
	std::string input = "dsiopgrasijbipisfcgjgoeojtoptldcjdiqjsqtssntnbjleqakkeelptgocbilejtfthqjfjitdskhokjqhghcrfjtgjkckbtjiptortfarptdralegstdpacbjepmrobgkmaterlnmcrbcasblreg"
		"rtisppknketmqllmaogmqpfspdtgaqnjhnicispkcgcljfdjtbnpqtgmcrkpfpemampbdclfbgqclmelnjskaqodoqktmomettfcnrhgdqjgafjnoippqbkksaccgggffehkbhrqpscpdmarmieijolt"
		"gnnntmkqqkgjrpfmnhtqltgdtcebjpmpagalkltgbrpknmoglnpdebsedorejjabpmmfdddqbksoomagrhbcitsegpiheajmnnjirfrsppmkieifmjtmajigqjobbdfoigpfleptthbtejrikimksbro"
		"cdhdsekglrmcbtbahcmddjdnrpehinccqbgogqajnelgefgdhksdtbqjimijfclberhcfalkecqatpphfncrgsshlgqqjhkfrjhcjsfombgmqolohnlgdbnohbdqifbroamekrkdsihhckbcpeikfnfm"
		"oaboromlpehfnjalstkabdcqhchehejnqkinemqlierbfjedjpekkstsnsoacdokncpkglnghkhnmdibkmdbdclqafqojceoqtqcdkakmhpedernibgddrtqpikekpktghbjjcmbbtgqpdceeihastqn"
		"tgjbntamsobhqfjjrhgmciitiitghhlsfatlmadcoqkcoldlkbdmbmdkaoitbartaqkeinhcbrqpaagkbcodgsnsmbrgngfoohkdmrrngojgohihjpkpfpfjjcpcamipltkdqhrdnsbtfchhjroofado"
		"olipprchqekedttrrnqppdcenqkkinedqekmbetjijgljriskrnrmhnfqdhejdtfibrbfqlfsjjtgjrrgdgtkaqgdedehckpqhjbqatobinhrcqefdpidloshrdpmncimlbidaoqatescmctpjhkmoba"
		"dehpjbpnfjcabircinacfonndndhhqhkagsbifpnojfijckjhclnqrslkbsjsslkejemhtrnadbjrdtffcsbtiebjpctnocrpgccrtqjojsmnrjsmtmlhifidhaqbcgrailjttsgjqkogtessibfrsnm"
		"snbthhithmaslsemhosffdpddqaahgfflgqtnfkmjlkabhfandftsaocjpoqntnefjpkggopjrikqfdjaiatbpnkctspldtimpttnfgocgqsltamiadbhilbhbqseitipstapsokekiqcaakndlalook"
		"hcbdkadrkdjfbppfgqnaqncbifclticskdnnpqcflmcehkcfgpfobhqjmkbdspnakgnfpqkgiedhofnmakhnspdcfqgpllpbsbgfridrmgqtljlemsrkfaecqcrtofaegsjpgeellakocbsomqqriaar"
		"djqjgrnepotosdrbqhqsaomecaolagippeeonjsbpkponmhbldtdkdimdopqadlhaibnjmgfcnlhrsjaoaeeeeitsepshtrtttfillnfrqmopbpbclfspfrfjnpjemiddflgrrlgneaarhbtssrfepkf"
		"afgekhtnmcmbldhrtirrhlqgbgdrngdndjjnqatbclcooklgkadrdtpfrtckfrpitqopqnilelrkbiqlatielejapllmjgmapgpltqophlgitotmgtqrpfjkiaojthjonrrfnmmadsapflhlcpasmjaa"
		"cpcbcdhhaqmfafrqpjlmakpdfpbrrnjtidmchlkthoriloetqhlqjhlgoepdseogagbhjlsjrpjjcnasmdgbcstrcomakhtkfajpdieapnbrsnhcroptmoioibhsigbfskansqnojhdtalbjfqjrcjdk"
		"kkbkioqgeitpffbgeesqhtgmihbkqfnthgjqaroqsolplmbhjtdqlbblicnrtgqherdeprbfdeagrbnsnjgqkhhlcmibteapbdainnnirnhghaqmbdimkhdmtdgkhggacsjhlcpaiotphphishabgpfr"
		"slarsssmqhttbgljbkqigpqqojraqdkpoceeacqibphdckepbbdtqlplandrifechithdppedohrfmmgfprbgmetriiffmanmtmpoiajotgtdsrifocetgdqglcepcrhbjphjpregppconkltepsdkpb"
		"njfilcieedlnkajqifscsbfjrbiadporetfpoftsicdkpnhdsrrikcripratmoqqgnlatcstrbkmgrhegqejsojoljfeqbmcgeofsmfhfplmesicoflftmlkoqgkjteppsbfcsntfedjpedjjhgitrkn"
		"frpoqtcdjpilnbdsggtbkcctbjhbssoqhkkpbesltgomircgebtgqngrofknpfjcpljiqhthooaolomhidoeqmnlreqfbrtiajqqqqqccqifkansdtomladaqtfrqrfqgbfcjbrljfrlsccnbifeiiqe"
		"tcbptserabtjoibdokgemirnjdjrdfodthksgghshthbhaqnkdrcdphmkqcfciibplmnrllrklsslhlocbqfqqksmedgmeathenepengheqtlhnnibkqjagcecaismifinbejpcrlsqcrbhsorgekfsg"
		"tkprdpolihhroboflchbpolkmjgooeangpcbkqnsemisgcerfdsmsjcctaqfqildenegkjrgofqatarqqijgjdaaeigaqrpmcmtebikhfhhetrbhfcnofnpbbnokcjcebnjpblcgscdkterqsdkdirfc"
		"ctmeaojoakjbbdamfdcqtlmrgpmpmjrhijlbpmppcqjetjqrekfdnsmafepjoeqofihaacipkrtcshtcjqrcojctfjblnrssfflsatnkiemsldmaajogkrshstleijcogfegqjjennoergqjhkpjtfrk"
		"qiofjilpopokephribnfabghdordtgnqgtnhheobtimppteemrjmkqmnkjqbhbjfmcmagsbrhfmceisjfibhqnbsojtndbspdcpkbrtaceotmniknbrjpstbakpdlfspiorjdibrmpifaipnkmordnsd"
		"efgplqclclmranhmapjbqqogbjpeoftslrgonafimjfeceiomkpigkghlblfscqjtcpfomfsbccphdktnftthfhkskqqfmsegfbasgttjnhqqrhjogbclimbkarpmhmknnllmccbpjjesifnoghrgtsj"
		"mhqehihaosdgmrtttadribkchrlgjbpbilrpmehgocesadstdnqlotfoiqmjrtkrcafoqeadhenhtlscrgfdrcrgsjphisrlkcrsskbfohegsoihbglsiiqtkmskcpnejlcinqnhdkfneobfmmqammto"
		"qsfkfkopnrdgnigqklbprcmjoictnnnjdkajbgqgdlnitlqkosrmajnhkhsdbleecqfpdbngmspejlgebdicenbobtrckcseselnrfmcphsfkebmtbgdohspshjijafaqifnfrhbqfstjllamjesioog"
		"bpglpldlmirrsekokinltqmdfqcfkqlldsotbjcnktdiqnogoirnejrcrththldcjjbctqibhdbdqpjkptqmafosqnjpemrfclanhigolhstotckskclpiblnkgkdphrghcnhiakhkkbbedmordbreml"
		"oknjfaseiarhijsptajbeefkciltmpcsrhacisgitqphrnpjnqcjahtopkotriroqrjqqhehplgnfnckjeacllqsocrllgstqhpeotlckrphdjkmnkoqndohfdtqjrhrqcncneeeoldranbfpibjlhqq"
		"khfmqmbmpphitlefpiopnibjqckhkgdmgiqonstingiejnkenqagebhaprtrqdcodsiqqhqjnfopkqtdmlbjebbmkbjgqlmtcbisiqioboblkagoeipijratscsonkfhdfgecgsdmlholnipnqqcnqod"
		"sejegglkmjogpebtpinscogpkckpkqkjmtfsriajsgpfkjfrrsilmotcibjsjttbkelinerlkfinonkdespqeglmhadqmcjctmkmqaphrpmljognnnbjtmcgfrortdtsqkcekjlhfpkgkqlpcmebfsak"
		"pothssrgaakkbojgjtetipgkildfjdhrsgeiqbgrnqhpcrneispifcknngsojrltdphajfrcoqjqfdagnqossrmddcreajepqdhrjqadnjlsmmqradqkainpcctoddkmhjjigjltlcjpgsnsbjibjnil"
		"ihslladkjnspobgfpiboggmtpnaegahohrskrnatskgnlnktndnljfkekcarcadjrnahhmgfpmksrbrcqkngidckrphtpdbeindprjnmopllqiofltllpfbmabehqreekhmhjrmdmdgbdmggejjtoldh"
		"ehgmekqgkaotrsocbmdqfjdjsmaepdlldkdhamocmancshelmttjickshkocnsgqijqabcdgoqaeqehipgrpjhnijtcoridrstslnnrhbrdrnkriqgdrfifgiibrqepgpfsikphlfkbsaktqrcgodlbd"
		"tcaishgneenommsjothojgcsbifqmgtdallktsppoiksmahgtpmangtghqctcncofgeeqtlctnbdnijmpnfbtetsaojoheamkqispaagfnjtckdjdicoecfqqokpsciasikfadlgqafkciarrombqjse"
		"damodmonartbakhqdehfmtdbnhdcqnslfcfiomopbnqbdprstqqlhlfnsihgnfjsihtclnjmsrnbmcmllipstmljashfqipqpokstmcrjhlckpfndmloeppqfcnncjjkpmipelefshtacfnfjrlgmgcr"
		"aildrmnmqbtmeqspdrpgobdqshccnqloeojnhcgppramnshjhopopkkfrmhdalrffgkeaiapgatlkgajbhdiknghrfkkqthcrrsrgsfekepmdicqpfqflcfaihkqhjkehjontlrkheckmqgaodrrrcrr"
		"kaojjenintbnkkpshjatghtmcrjtlsrbsdkatqifhcksefilgidehcqjlfbpqkigftgehhjobterqmjdbmtagqkkndfjfnqkeoodnqkghoeetftmjkmhgcjmroncabeqilabhcaoqqkpbbhkmmjkotoe"
		"fisfbdojogdnidtqtcemddohpdkccegaeefgtthnrkgffscqagidjcdfsftmbfmgbkebblgtonetlsqdqqsglbdjscnatggaicnjfaatfrliptlmpjkgdfhbtbbsttkhbeihqbsbsjjfiarqbtceqcgp"
		"phfohinaentaosbmhckioteptsmhaspprabqagjeaiqggjlglbgrakflirtbhoiegknticpikmhjbspflncddtpdqgqdmfakhnjppfqfjdgknnhqgctjbgfkmbnqgnhngibnnrlcmrfflenrgmtatqkd"
		"rdaqjtbphcjntmhljmiarbkpgbprrfaobmcklertgsmsktbaekmndoajpqgmnttolnedrcoeasodjpdffpsbctcrhjcainplglgefaagkgbabertlqanhcdgdfgdknpqfbmkoeiekjqefodrcdcbrfhb"
		"cnemhlbenfotcppmemqcsltmonnetafnfbseftisepjscelsitagllsrflbqdsjbmhfrsghpnqnpmefbqghtrsqobkkramsmtpbsbingqsnjptklfjkotsjbatsblifddhnfhsdeqrflqhonqqhqpqjh"
		"ihalpggsftpmrtigqnreaerjaerhngpnfpeanlkscsdmjlsrrhbjlsseohltnsmsojktansolngmqejnecppmftgndggbkfhthhlargdkmpgjqmnshakmmrfppeqrberidibaoectmiiianhtnrmrgjm"
		"nfblgrihaiimpeooqcofpheomnskaioffpqmmqtertqmdkgmfmjatngdgffsfmekhmombnqsefcipimaabmlgtgeqepbqlddpshqdqgibiiqiajanndlechagcncnrrjhfrkbqkoqkkfklrpfbsjpgcb"
		"ipdoemddjmgciqqfhtcjktrhmpjhblacgdqdilgrpmaebibihdjkogrtosspjtjicrlcijaecmapmndaiecollnfkmmtlctflkiaaaqoeijqneibicplobiqfbhqphngjnsbfgpjgqstmsabnietbnpg"
		"ooobbhtlbsmsqaadqkcjipcnpgmqttcfoqgppgsiqlhmdhptrkarfolabpqmpksjsqqnopcksjpbikafmnorhfjanfnihljftftombekcllkoehgrbeqtnrmlkmknbqmshsladbcgneajlhgmlodqlpt"
		"nhkgasllfjcfeptladljgshkbcosnjjhjtfbrimosotockfcfjmlhtcbnqthragsadajmmectpqbgcdldhpktrlmfclodjnpnnerfatqqprcjnfmaapljsegnhbqrodchtleaknirkktphdiaktjjpqc"
		"prkelfgkejgqlteicgtropfofrpgedatakddhbfmkmibdncftndfialgrhmoknndprsdkqpnapgdaijaoercejioinikgnfbcqenmlgmtmptnqlhajbrkcdkplabqgotolegcksbofntcesofalpcofr"
		"rskgqefkpjqklgdrdqrrnpmshpgbcdklnarjrctedhoofsmjgbgtikkisijmladfmngbhsglfarlkbmjckidnkllsmdkeshjlnktlqcjjlmlneahgjktlnkkgfmkelthqcsasajtenlrrlepmhpeargs"
		"dsjtjasfcrfnjgmntpkihhetolpgibfdlgoasnsbkpglokfnghonokeabmhbneffklriehbgdtsrkdcqcijrsfjlrqnlmkiobrdsfqeaqcjgrdcamdjkisoghhjtjjocgjadrfdntmljqfjaiskjiehp"
		"dqhmrnpdohtlecrehindgopoefpmccarstchmjlgqcjbegflhkgnebtatpmnjekadehhnkfkmplrniaaktfgarglekqnphnkdbkrlphecknqknimmgsfdeihofabeoehhoesjdoefhahbatfgrcjnlqa"
		"qjbaprhclemnhhrfgrmtrmrqbtfpkopgdiskgsercqcbptsoilnspkoqktdmnklitbkftoobdrpsinerqshlabacmdpsgssftjctdimgfhrgnbpjlcnmdnghinfoleldnnoicgptgeftrmajonnjstrh"
		"fonqsfldkfemelekpbbmobnihgsfshedbslmpdpfitsmcoorppkjjpsicinapkdqioadjqashsckmrtaebjfrtntttlojgdjadmclmaldonhlmtigjnditoisfohljqdfafqerttmmtprsddtjsaimag"
		"jofmqnpbfnjbcjnonmckcffcodcohcmqijiecqrtjhblqgsbkaemrjoefismcljlajhpffgoetsmfinpirirhobmpmqrpfahpaomrbhbarnsfgnfenodaqhhadqpbrcijjagkthciaansgkolfrlnqkn"
		"ahaneobndnlnnsibsihigjdsgabtjmebteopthacalifjqttqstdhcbgpofegkfrglmfseakpiiqqthmrhpqbicqdaajkfhqqlogiojpormkqlcfksbmsqibqbdsscghnanbgcralbctefehpstnothc"
		"akatmggrtllrgakrnmrrjbeqlpcfhjthttsdsqajalggdidqnmgcoctfsbdrccqnopqedindmljpafmnrshdasbklehnsegelciolnkdftkrqccomjrfisplopfntljcgsijlseikofgrhmbjkgjicad"
		"rfiijrcphkqlbatdofbdeofnelcefptoahobrqqqtmhaehpteqoiktcgdqlilkdekrfhgodfsdrdkeooaicdiqjdfmlqdgmfqsecettccifmmlseabhajjdobgdqnpbjffdjfoehcbmgnkkndknntita"
		"ocjhkkihidjnrnmloerhpamskfdjfdbarkthnahbdqgbbsehdcpkchaefefktscqjcqoodprlnkmlplgjgidgjhdfmfekimlcirqdeforisjdkhmiqhgrojcspsapkmjlbfogcbdktefbmjkaqqrksla"
		"fjbalfjcggjmakqlbaqdegfeonbflefqnsirdrlkpacqcktedpthnqmijffnkcbpbkeetqopijddtctcjkkpgophlaanocjhefmdnskchnrtpqbrgdmejhlbtmongpbkbffopqipbrojnhgllspmrhfq"
		"labjholalqhhehcgfipkpbcsljlaiqilijaiqlatahgqhacmijoqcqgnsjfsgnkgpkgdohcggjcnbrfcgasjiqosgarefhkajjdpqsnctqqafnclfmagbhehtnlemnrccmjskdnjljkqoehajaschcjs"
		"iacaftoimesohlesmgohcntdfrfeloctgfamqgmakkpjothgrnnttmpebajnhlmnierflbrbemlsdkqaqcmhghlihmboqnaekjbbdtohlrrhanhiptpogscgldahimdsorlrisqlpnspsgpgrkaejcka"
		"rctfpoqbdtslrodntbajtqprshbhjdtsfkqmfmfiddmbjpgaiskigfrfnseonefkobdlfimieejflhgtgitmfqjkgortkckqdfiifmqbishtffkdfkqksrbfdsenmgkpdkdbclckbbjhslkdbsgaitrl"
		"jnfbapqprlqtotjqmkdlnfgpqmheleparmbjtjrqanppeqdrssimdgtttgpccldldqndgklsphfapirogrgcdfbodjrramipibkgdcrtbctqlikjrilmffhioqfgagbitehdseolgnhjnktkscoqhnqb"
		"jchbabktfjopfiglnfngpeiggpcoispkmplmqnencsahhglalqttatrsotmdjanohqsdkciebieaohardliplfnfqsagsfafcsamniioqmoctglckajbrdsobtalemigcakpitbqdhkdobrqnhrdcprd"
		"gjglbojpgalolecommjsftolgloasldfmbifhranjdtaibhafqkkhenfhhffkiccbkhiiabrdakdnrdsffbnjosqoqoqqqtstsgtsaqomsrghnensrsimiqsekobtflserrojficesidleijcgjghged"
		"isqtehjarsosepaanadermflkprjnnfblbnhbchkboarbbronmkcqhntckahpfbhtogaqgcracgnpdhbijdqqrhltispntomfaecgslsbslinkjnlfkacjlnrbilncdspamnsqelohmtkbnbspbaeeoo"
		"gofljajeaojlkncqbgplaaeshstecfsatplapneihgtrtnfmampanmsmkjqmggnsbqsrjprqbifmbcrnpefiqqmsrblehqcbemkohhcipanickorgtrdhkbrlebkmpljhbdpirpprieaksjrjhmjjfgm"
		"ctcgogpntsaiqqpfqlftbpiloamdrshtjbgdhbihmjhafcfnodmpkmsqmctcasbjttehnngrcnrthoenjrjtjtpocgqoejqqbmdofjltoakbgppqeqpfhdtjjhqgjmckerecshnmtefftmbdijiqmarn"
		"tntirnkokgqinjmefskekdtlmatemislcjmlpcffbngopklaabrleiorinnabdepniticqfdkdkrobjoogrspdhpinicqmjjaijofhshkiqqbfdpmantenoedsiopgrasijbipisfcgjgoeojtoptldc"
		"jdiqjsqtssntnbjleqakkeelptgocbilejtfthqjfjitdskhokjqhghcrfjtgjkckbtjiptortfarptdralegstdpacbjepmrobgkmaterlnmcrbcasblregrtisppknketmqllmaogmqpfspdtgaqnj"
		"hnicispkcgcljfdjtbnpqtgmcrkpfpemampbdclfbgqclmelnjskaqodoqktmomettfcnrhgdqjgafjnoippqbkksaccgggffehkbhrqpscpdmarmieijoltgnnntmkqqkgjrpfmnhtqltgdtcebjpmp"
		"agalkltgbrpknmoglnpdebsedorejjabpmmfdddqbksoomagrhbcitsegpiheajmnnjirfrsppmkieifmjtmajigqjobbdfoigpfleptthbtejrikimksbrocdhdsekglrmcbtbahcmddjdnrpehincc"
		"qbgogqajnelgefgdhksdtbqjimijfclberhcfalkecqatpphfncrgsshlgqqjhkfrjhcjsfombgmqolohnlgdbnohbdqifbroamekrkdsihhckbcpeikfnfmoaboromlpehfnjalstkabdcqhchehejn"
		"qkinemqlierbfjedjpekkstsnsoacdokncpkglnghkhnmdibkmdbdclqafqojceoqtqcdkakmhpedernibgddrtqpikekpktghbjjcmbbtgqpdceeihastqntgjbntamsobhqfjjrhgmciitiitghhls"
		"fatlmadcoqkcoldlkbdmbmdkaoitbartaqkeinhcbrqpaagkbcodgsnsmbrgngfoohkdmrrngojgohihjpkpfpfjjcpcamipltkdqhrdnsbtfchhjroofadoolipprchqekedttrrnqppdcenqkkined"
		"qekmbetjijgljriskrnrmhnfqdhejdtfibrbfqlfsjjtgjrrgdgtkaqgdedehckpqhjbqatobinhrcqefdpidloshrdpmncimlbidaoqatescmctpjhkmobadehpjbpnfjcabircinacfonndndhhqhk"
		"agsbifpnojfijckjhclnqrslkbsjsslkejemhtrnadbjrdtffcsbtiebjpctnocrpgccrtqjojsmnrjsmtmlhifidhaqbcgrailjttsgjqkogtessibfrsnmsnbthhithmaslsemhosffdpddqaahgff"
		"lgqtnfkmjlkabhfandftsaocjpoqntnefjpkggopjrikqfdjaiatbpnkctspldtimpttnfgocgqsltamiadbhilbhbqseitipstapsokekiqcaakndlalookhcbdkadrkdjfbppfgqnaqncbifcltics"
		"kdnnpqcflmcehkcfgpfobhqjmkbdspnakgnfpqkgiedhofnmakhnspdcfqgpllpbsbgfridrmgqtljlemsrkfaecqcrtofaegsjpgeellakocbsomqqriaardjqjgrnepotosdrbqhqsaomecaolagip"
		"peeonjsbpkponmhbldtdkdimdopqadlhaibnjmgfcnlhrsjaoaeeeeitsepshtrtttfillnfrqmopbpbclfspfrfjnpjemiddflgrrlgneaarhbtssrfepkfafgekhtnmcmbldhrtirrhlqgbgdrngdn"
		"djjnqatbclcooklgkadrdtpfrtckfrpitqopqnilelrkbiqlatielejapllmjgmapgpltqophlgitotmgtqrpfjkiaojthjonrrfnmmadsapflhlcpasmjaacpcbcdhhaqmfafrqpjlmakpdfpbrrnjt"
		"idmchlkthoriloetqhlqjhlgoepdseogagbhjlsjrpjjcnasmdgbcstrcomakhtkfajpdieapnbrsnhcroptmoioibhsigbfskansqnojhdtalbjfqjrcjdkkkbkioqgeitpffbgeesqhtgmihbkqfnt"
		"hgjqaroqsolplmbhjtdqlbblicnrtgqherdeprbfdeagrbnsnjgqkhhlcmibteapbdainnnirnhghaqmbdimkhdmtdgkhggacsjhlcpaiotphphishabgpfrslarsssmqhttbgljbkqigpqqojraqdkp"
		"oceeacqibphdckepbbdtqlplandrifechithdppedohrfmmgfprbgmetriiffmanmtmpoiajotgtdsrifocetgdqglcepcrhbjphjpregppconkltepsdkpbnjfilcieedlnkajqifscsbfjrbiadpor"
		"etfpoftsicdkpnhdsrrikcripratmoqqgnlatcstrbkmgrhegqejsojoljfeqbmcgeofsmfhfplmesicoflftmlkoqgkjteppsbfcsntfedjpedjjhgitrknfrpoqtcdjpilnbdsggtbkcctbjhbssoq"
		"hkkpbesltgomircgebtgqngrofknpfjcpljiqhthooaolomhidoeqmnlreqfbrtiajqqqqqccqifkansdtomladaqtfrqrfqgbfcjbrljfrlsccnbifeiiqetcbptserabtjoibdokgemirnjdjrdfod"
		"thksgghshthbhaqnkdrcdphmkqcfciibplmnrllrklsslhlocbqfqqksmedgmeathenepengheqtlhnnibkqjagcecaismifinbejpcrlsqcrbhsorgekfsgtkprdpolihhroboflchbpolkmjgooean"
		"gpcbkqnsemisgcerfdsmsjcctaqfqildenegkjrgofqatarqqijgjdaaeigaqrpmcmtebikhfhhetrbhfcnofnpbbnokcjcebnjpblcgscdkterqsdkdirfcctmeaojoakjbbdamfdcqtlmrgpmpmjrh"
		"ijlbpmppcqjetjqrekfdnsmafepjoeqofihaacipkrtcshtcjqrcojctfjblnrssfflsatnkiemsldmaajogkrshstleijcogfegqjjennoergqjhkpjtfrkqiofjilpopokephribnfabghdordtgnq"
		"gtnhheobtimppteemrjmkqmnkjqbhbjfmcmagsbrhfmceisjfibhqnbsojtndbspdcpkbrtaceotmniknbrjpstbakpdlfspiorjdibrmpifaipnkmordnsdefgplqclclmranhmapjbqqogbjpeofts"
		"lrgonafimjfeceiomkpigkghlblfscqjtcpfomfsbccphdktnftthfhkskqqfmsegfbasgttjnhqqrhjogbclimbkarpmhmknnllmccbpjjesifnoghrgtsjmhqehihaosdgmrtttadribkchrlgjbpb"
		"ilrpmehgocesadstdnqlotfoiqmjrtkrcafoqeadhenhtlscrgfdrcrgsjphisrlkcrsskbfohegsoihbglsiiqtkmskcpnejlcinqnhdkfneobfmmqammtoqsfkfkopnrdgnigqklbprcmjoictnnnj"
		"dkajbgqgdlnitlqkosrmajnhkhsdbleecqfpdbngmspejlgebdicenbobtrckcseselnrfmcphsfkebmtbgdohspshjijafaqifnfrhbqfstjllamjesioogbpglpldlmirrsekokinltqmdfqcfkqll"
		"dsotbjcnktdiqnogoirnejrcrththldcjjbctqibhdbdqpjkptqmafosqnjpemrfclanhigolhstotckskclpiblnkgkdphrghcnhiakhkkbbedmordbremloknjfaseiarhijsptajbeefkciltmpcs"
		"rhacisgitqphrnpjnqcjahtopkotriroqrjqqhehplgnfnckjeacllqsocrllgstqhpeotlckrphdjkmnkoqndohfdtqjrhrqcncneeeoldranbfpibjlhqqkhfmqmbmpphitlefpiopnibjqckhkgdm"
		"giqonstingiejnkenqagebhaprtrqdcodsiqqhqjnfopkqtdmlbjebbmkbjgqlmtcbisiqioboblkagoeipijratscsonkfhdfgecgsdmlholnipnqqcnqodsejegglkmjogpebtpinscogpkckpkqkj"
		"mtfsriajsgpfkjfrrsilmotcibjsjttbkelinerlkfinonkdespqeglmhadqmcjctmkmqaphrpmljognnnbjtmcgfrortdtsqkcekjlhfpkgkqlpcmebfsakpothssrgaakkbojgjtetipgkildfjdhr"
		"sgeiqbgrnqhpcrneispifcknngsojrltdphajfrcoqjqfdagnqossrmddcreajepqdhrjqadnjlsmmqradqkainpcctoddkmhjjigjltlcjpgsnsbjibjnilihslladkjnspobgfpiboggmtpnaegaho"
		"hrskrnatskgnlnktndnljfkekcarcadjrnahhmgfpmksrbrcqkngidckrphtpdbeindprjnmopllqiofltllpfbmabehqreekhmhjrmdmdgbdmggejjtoldhehgmekqgkaotrsocbmdqfjdjsmaepdll"
		"dkdhamocmancshelmttjickshkocnsgqijqabcdgoqaeqehipgrpjhnijtcoridrstslnnrhbrdrnkriqgdrfifgiibrqepgpfsikphlfkbsaktqrcgodlbdtcaishgneenommsjothojgcsbifqmgtd"
		"allktsppoiksmahgtpmangtghqctcncofgeeqtlctnbdnijmpnfbtetsaojoheamkqispaagfnjtckdjdicoecfqqokpsciasikfadlgqafkciarrombqjsedamodmonartbakhqdehfmtdbnhdcqnsl"
		"fcfiomopbnqbdprstqqlhlfnsihgnfjsihtclnjmsrnbmcmllipstmljashfqipqpokstmcrjhlckpfndmloeppqfcnncjjkpmipelefshtacfnfjrlgmgcraildrmnmqbtmeqspdrpgobdqshccnqlo"
		"eojnhcgppramnshjhopopkkfrmhdalrffgkeaiapgatlkgajbhdiknghrfkkqthcrrsrgsfekepmdicqpfqflcfaihkqhjkehjontlrkheckmqgaodrrrcrrkaojjenintbnkkpshjatghtmcrjtlsrb"
		"sdkatqifhcksefilgidehcqjlfbpqkigftgehhjobterqmjdbmtagqkkndfjfnqkeoodnqkghoeetftmjkmhgcjmroncabeqilabhcaoqqkpbbhkmmjkotoefisfbdojogdnidtqtcemddohpdkccega"
		"eefgtthnrkgffscqagidjcdfsftmbfmgbkebblgtonetlsqdqqsglbdjscnatggaicnjfaatfrliptlmpjkgdfhbtbbsttkhbeihqbsbsjjfiarqbtceqcgpphfohinaentaosbmhckioteptsmhaspp"
		"rabqagjeaiqggjlglbgrakflirtbhoiegknticpikmhjbspflncddtpdqgqdmfakhnjppfqfjdgknnhqgctjbgfkmbnqgnhngibnnrlcmrfflenrgmtatqkdrdaqjtbphcjntmhljmiarbkpgbprrfao"
		"bmcklertgsmsktbaekmndoajpqgmnttolnedrcoeasodjpdffpsbctcrhjcainplglgefaagkgbabertlqanhcdgdfgdknpqfbmkoeiekjqefodrcdcbrfhbcnemhlbenfotcppmemqcsltmonnetafn"
		"fbseftisepjscelsitagllsrflbqdsjbmhfrsghpnqnpmefbqghtrsqobkkramsmtpbsbingqsnjptklfjkotsjbatsblifddhnfhsdeqrflqhonqqhqpqjhihalpggsftpmrtigqnreaerjaerhngpn"
		"fpeanlkscsdmjlsrrhbjlsseohltnsmsojktansolngmqejnecppmftgndggbkfhthhlargdkmpgjqmnshakmmrfppeqrberidibaoectmiiianhtnrmrgjmnfblgrihaiimpeooqcofpheomnskaiof"
		"fpqmmqtertqmdkgmfmjatngdgffsfmekhmombnqsefcipimaabmlgtgeqepbqlddpshqdqgibiiqiajanndlechagcncnrrjhfrkbqkoqkkfklrpfbsjpgcbipdoemddjmgciqqfhtcjktrhmpjhblac"
		"gdqdilgrpmaebibihdjkogrtosspjtjicrlcijaecmapmndaiecollnfkmmtlctflkiaaaqoeijqneibicplobiqfbhqphngjnsbfgpjgqstmsabnietbnpgooobbhtlbsmsqaadqkcjipcnpgmqttcf"
		"oqgppgsiqlhmdhptrkarfolabpqmpksjsqqnopcksjpbikafmnorhfjanfnihljftftombekcllkoehgrbeqtnrmlkmknbqmshsladbcgneajlhgmlodqlptnhkgasllfjcfeptladljgshkbcosnjjh"
		"jtfbrimosotockfcfjmlhtcbnqthragsadajmmectpqbgcdldhpktrlmfclodjnpnnerfatqqprcjnfmaapljsegnhbqrodchtleaknirkktphdiaktjjpqcprkelfgkejgqlteicgtropfofrpgedat"
		"akddhbfmkmibdncftndfialgrhmoknndprsdkqpnapgdaijaoercejioinikgnfbcqenmlgmtmptnqlhajbrkcdkplabqgotolegcksbofntcesofalpcofrrskgqefkpjqklgdrdqrrnpmshpgbcdkl"
		"narjrctedhoofsmjgbgtikkisijmladfmngbhsglfarlkbmjckidnkllsmdkeshjlnktlqcjjlmlneahgjktlnkkgfmkelthqcsasajtenlrrlepmhpeargsdsjtjasfcrfnjgmntpkihhetolpgibfd"
		"lgoasnsbkpglokfnghonokeabmhbneffklriehbgdtsrkdcqcijrsfjlrqnlmkiobrdsfqeaqcjgrdcamdjkisoghhjtjjocgjadrfdntmljqfjaiskjiehpdqhmrnpdohtlecrehindgopoefpmccar"
		"stchmjlgqcjbegflhkgnebtatpmnjekadehhnkfkmplrniaaktfgarglekqnphnkdbkrlphecknqknimmgsfdeihofabeoehhoesjdoefhahbatfgrcjnlqaqjbaprhclemnhhrfgrmtrmrqbtfpkopg"
		"diskgsercqcbptsoilnspkoqktdmnklitbkftoobdrpsinerqshlabacmdpsgssftjctdimgfhrgnbpjlcnmdnghinfoleldnnoicgptgeftrmajonnjstrhfonqsfldkfemelekpbbmobnihgsfshed"
		"bslmpdpfitsmcoorppkjjpsicinapkdqioadjqashsckmrtaebjfrtntttlojgdjadmclmaldonhlmtigjnditoisfohljqdfafqerttmmtprsddtjsaimagjofmqnpbfnjbcjnonmckcffcodcohcmq"
		"ijiecqrtjhblqgsbkaemrjoefismcljlajhpffgoetsmfinpirirhobmpmqrpfahpaomrbhbarnsfgnfenodaqhhadqpbrcijjagkthciaansgkolfrlnqknahaneobndnlnnsibsihigjdsgabtjmeb"
		"teopthacalifjqttqstdhcbgpofegkfrglmfseakpiiqqthmrhpqbicqdaajkfhqqlogiojpormkqlcfksbmsqibqbdsscghnanbgcralbctefehpstnothcakatmggrtllrgakrnmrrjbeqlpcfhjth"
		"ttsdsqajalggdidqnmgcoctfsbdrccqnopqedindmljpafmnrshdasbklehnsegelciolnkdftkrqccomjrfisplopfntljcgsijlseikofgrhmbjkgjicadrfiijrcphkqlbatdofbdeofnelcefpto"
		"ahobrqqqtmhaehpteqoiktcgdqlilkdekrfhgodfsdrdkeooaicdiqjdfmlqdgmfqsecettccifmmlseabhajjdobgdqnpbjffdjfoehcbmgnkkndknntitaocjhkkihidjnrnmloerhpamskfdjfdba"
		"rkthnahbdqgbbsehdcpkchaefefktscqjcqoodprlnkmlplgjgidgjhdfmfekimlcirqdeforisjdkhmiqhgrojcspsapkmjlbfogcbdktefbmjkaqqrkslafjbalfjcggjmakqlbaqdegfeonbflefq"
		"nsirdrlkpacqcktedpthnqmijffnkcbpbkeetqopijddtctcjkkpgophlaanocjhefmdnskchnrtpqbrgdmejhlbtmongpbkbffopqipbrojnhgllspmrhfqlabjholalqhhehcgfipkpbcsljlaiqil"
		"ijaiqlatahgqhacmijoqcqgnsjfsgnkgpkgdohcggjcnbrfcgasjiqosgarefhkajjdpqsnctqqafnclfmagbhehtnlemnrccmjskdnjljkqoehajaschcjsiacaftoimesohlesmgohcntdfrfeloct"
		"gfamqgmakkpjothgrnnttmpebajnhlmnierflbrbemlsdkqaqcmhghlihmboqnaekjbbdtohlrrhanhiptpogscgldahimdsorlrisqlpnspsgpgrkaejckarctfpoqbdtslrodntbajtqprshbhjdts"
		"fkqmfmfiddmbjpgaiskigfrfnseonefkobdlfimieejflhgtgitmfqjkgortkckqdfiifmqbishtffkdfkqksrbfdsenmgkpdkdbclckbbjhslkdbsgaitrljnfbapqprlqtotjqmkdlnfgpqmhelepa"
		"rmbjtjrqanppeqdrssimdgtttgpccldldqndgklsphfapirogrgcdfbodjrramipibkgdcrtbctqlikjrilmffhioqfgagbitehdseolgnhjnktkscoqhnqbjchbabktfjopfiglnfngpeiggpcoispk"
		"mplmqnencsahhglalqttatrsotmdjanohqsdkciebieaohardliplfnfqsagsfafcsamniioqmoctglckajbrdsobtalemigcakpitbqdhkdobrqnhrdcprdgjglbojpgalolecommjsftolgloasldf"
		"mbifhranjdtaibhafqkkhenfhhffkiccbkhiiabrdakdnrdsffbnjosqoqoqqqtstsgtsaqomsrghnensrsimiqsekobtflserrojficesidleijcgjghgedisqtehjarsosepaanadermflkprjnnfb"
		"lbnhbchkboarbbronmkcqhntckahpfbhtogaqgcracgnpdhbijdqqrhltispntomfaecgslsbslinkjnlfkacjlnrbilncdspamnsqelohmtkbnbspbaeeoogofljajeaojlkncqbgplaaeshstecfsa"
		"tplapneihgtrtnfmampanmsmkjqmggnsbqsrjprqbifmbcrnpefiqqmsrblehqcbemkohhcipanickorgtrdhkbrlebkmpljhbdpirpprieaksjrjhmjjfgmctcgogpntsaiqqpfqlftbpiloamdrsht"
		"jbgdhbihmjhafcfnodmpkmsqmctcasbjttehnngrcnrthoenjrjtjtpocgqoejqqbmdofjltoakbgppqeqpfhdtjjhqgjmckerecshnmtefftmbdijiqmarntntirnkokgqinjmefskekdtlmatemisl"
		"cjmlpcffbngopklaabrleiorinnabdepniticqfdkdkrobjoogrspdhpinicqmjjaijofhshkiqqbfdpmantenoedsiopgrasijbipisfcgjgoeojtoptldcjdiqjsqtssntnbjleqakkeelptgocbil"
		"ejtfthqjfjitdskhokjqhghcrfjtgjkckbtjiptortfarptdralegstdpacbjepmrobgkmaterlnmcrbcasblregrtisppknketmqllmaogmqpfspdtgaqnjhnicispkcgcljfdjtbnpqtgmcrkpfpem"
		"ampbdclfbgqclmelnjskaqodoqktmomettfcnrhgdqjgafjnoippqbkksaccgggffehkbhrqpscpdmarmieijoltgnnntmkqqkgjrpfmnhtqltgdtcebjpmpagalkltgbrpknmoglnpdebsedorejjab"
		"pmmfdddqbksoomagrhbcitsegpiheajmnnjirfrsppmkieifmjtmajigqjobbdfoigpfleptthbtejrikimksbrocdhdsekglrmcbtbahcmddjdnrpehinccqbgogqajnelgefgdhksdtbqjimijfclb"
		"erhcfalkecqatpphfncrgsshlgqqjhkfrjhcjsfombgmqolohnlgdbnohbdqifbroamekrkdsihhckbcpeikfnfmoaboromlpehfnjalstkabdcqhchehejnqkinemqlierbfjedjpekkstsnsoacdok"
		"ncpkglnghkhnmdibkmdbdclqafqojceoqtqcdkakmhpedernibgddrtqpikekpktghbjjcmbbtgqpdceeihastqntgjbntamsobhqfjjrhgmciitiitghhlsfatlmadcoqkcoldlkbdmbmdkaoitbart"
		"aqkeinhcbrqpaagkbcodgsnsmbrgngfoohkdmrrngojgohihjpkpfpfjjcpcamipltkdqhrdnsbtfchhjroofadoolipprchqekedttrrnqppdcenqkkinedqekmbetjijgljriskrnrmhnfqdhejdtf"
		"ibrbfqlfsjjtgjrrgdgtkaqgdedehckpqhjbqatobinhrcqefdpidloshrdpmncimlbidaoqatescmctpjhkmobadehpjbpnfjcabircinacfonndndhhqhkagsbifpnojfijckjhclnqrslkbsjsslk"
		"ejemhtrnadbjrdtffcsbtiebjpctnocrpgccrtqjojsmnrjsmtmlhifidhaqbcgrailjttsgjqkogtessibfrsnmsnbthhithmaslsemhosffdpddqaahgfflgqtnfkmjlkabhfandftsaocjpoqntne"
		"fjpkggopjrikqfdjaiatbpnkctspldtimpttnfgocgqsltamiadbhilbhbqseitipstapsokekiqcaakndlalookhcbdkadrkdjfbppfgqnaqncbifclticskdnnpqcflmcehkcfgpfobhqjmkbdspna"
		"kgnfpqkgiedhofnmakhnspdcfqgpllpbsbgfridrmgqtljlemsrkfaecqcrtofaegsjpgeellakocbsomqqriaardjqjgrnepotosdrbqhqsaomecaolagippeeonjsbpkponmhbldtdkdimdopqadlh"
		"aibnjmgfcnlhrsjaoaeeeeitsepshtrtttfillnfrqmopbpbclfspfrfjnpjemiddflgrrlgneaarhbtssrfepkfafgekhtnmcmbldhrtirrhlqgbgdrngdndjjnqatbclcooklgkadrdtpfrtckfrpi"
		"tqopqnilelrkbiqlatielejapllmjgmapgpltqophlgitotmgtqrpfjkiaojthjonrrfnmmadsapflhlcpasmjaacpcbcdhhaqmfafrqpjlmakpdfpbrrnjtidmchlkthoriloetqhlqjhlgoepdseog"
		"agbhjlsjrpjjcnasmdgbcstrcomakhtkfajpdieapnbrsnhcroptmoioibhsigbfskansqnojhdtalbjfqjrcjdkkkbkioqgeitpffbgeesqhtgmihbkqfnthgjqaroqsolplmbhjtdqlbblicnrtgqh"
		"erdeprbfdeagrbnsnjgqkhhlcmibteapbdainnnirnhghaqmbdimkhdmtdgkhggacsjhlcpaiotphphishabgpfrslarsssmqhttbgljbkqigpqqojraqdkpoceeacqibphdckepbbdtqlplandrifec"
		"hithdppedohrfmmgfprbgmetriiffmanmtmpoiajotgtdsrifocetgdqglcepcrhbjphjpregppconkltepsdkpbnjfilcieedlnkajqifscsbfjrbiadporetfpoftsicdkpnhdsrrikcripratmoqq"
		"gnlatcstrbkmgrhegqejsojoljfeqbmcgeofsmfhfplmesicoflftmlkoqgkjteppsbfcsntfedjpedjjhgitrknfrpoqtcdjpilnbdsggtbkcctbjhbssoqhkkpbesltgomircgebtgqngrofknpfjc"
		"pljiqhthooaolomhidoeqmnlreqfbrtiajqqqqqccqifkansdtomladaqtfrqrfqgbfcjbrljfrlsccnbifeiiqetcbptserabtjoibdokgemirnjdjrdfodthksgghshthbhaqnkdrcdphmkqcfciib"
		"plmnrllrklsslhlocbqfqqksmedgmeathenepengheqtlhnnibkqjagcecaismifinbejpcrlsqcrbhsorgekfsgtkprdpolihhroboflchbpolkmjgooeangpcbkqnsemisgcerfdsmsjcctaqfqild"
		"enegkjrgofqatarqqijgjdaaeigaqrpmcmtebikhfhhetrbhfcnofnpbbnokcjcebnjpblcgscdkterqsdkdirfcctmeaojoakjbbdamfdcqtlmrgpmpmjrhijlbpmppcqjetjqrekfdnsmafepjoeqo"
		"fihaacipkrtcshtcjqrcojctfjblnrssfflsatnkiemsldmaajogkrshstleijcogfegqjjennoergqjhkpjtfrkqiofjilpopokephribnfabghdordtgnqgtnhheobtimppteemrjmkqmnkjqbhbjf"
		"mcmagsbrhfmceisjfibhqnbsojtndbspdcpkbrtaceotmniknbrjpstbakpdlfspiorjdibrmpifaipnkmordnsdefgplqclclmranhmapjbqqogbjpeoftslrgonafimjfeceiomkpigkghlblfscqj"
		"tcpfomfsbccphdktnftthfhkskqqfmsegfbasgttjnhqqrhjogbclimbkarpmhmknnllmccbpjjesifnoghrgtsjmhqehihaosdgmrtttadribkchrlgjbpbilrpmehgocesadstdnqlotfoiqmjrtkr"
		"cafoqeadhenhtlscrgfdrcrgsjphisrlkcrsskbfohegsoihbglsiiqtkmskcpnejlcinqnhdkfneobfmmqammtoqsfkfkopnrdgnigqklbprcmjoictnnnjdkajbgqgdlnitlqkosrmajnhkhsdblee"
		"cqfpdbngmspejlgebdicenbobtrckcseselnrfmcphsfkebmtbgdohspshjijafaqifnfrhbqfstjllamjesioogbpglpldlmirrsekokinltqmdfqcfkqlldsotbjcnktdiqnogoirnejrcrththldc"
		"jjbctqibhdbdqpjkptqmafosqnjpemrfclanhigolhstotckskclpiblnkgkdphrghcnhiakhkkbbedmordbremloknjfaseiarhijsptajbeefkciltmpcsrhacisgitqphrnpjnqcjahtopkotriro"
		"qrjqqhehplgnfnckjeacllqsocrllgstqhpeotlckrphdjkmnkoqndohfdtqjrhrqcncneeeoldranbfpibjlhqqkhfmqmbmpphitlefpiopnibjqckhkgdmgiqonstingiejnkenqagebhaprtrqdco"
		"dsiqqhqjnfopkqtdmlbjebbmkbjgqlmtcbisiqioboblkagoeipijratscsonkfhdfgecgsdmlholnipnqqcnqodsejegglkmjogpebtpinscogpkckpkqkjmtfsriajsgpfkjfrrsilmotcibjsjttb"
		"kelinerlkfinonkdespqeglmhadqmcjctmkmqaphrpmljognnnbjtmcgfrortdtsqkcekjlhfpkgkqlpcmebfsakpothssrgaakkbojgjtetipgkildfjdhrsgeiqbgrnqhpcrneispifcknngsojrlt"
		"dphajfrcoqjqfdagnqossrmddcreajepqdhrjqadnjlsmmqradqkainpcctoddkmhjjigjltlcjpgsnsbjibjnilihslladkjnspobgfpiboggmtpnaegahohrskrnatskgnlnktndnljfkekcarcadj"
		"rnahhmgfpmksrbrcqkngidckrphtpdbeindprjnmopllqiofltllpfbmabehqreekhmhjrmdmdgbdmggejjtoldhehgmekqgkaotrsocbmdqfjdjsmaepdlldkdhamocmancshelmttjickshkocnsgq"
		"ijqabcdgoqaeqehipgrpjhnijtcoridrstslnnrhbrdrnkriqgdrfifgiibrqepgpfsikphlfkbsaktqrcgodlbdtcaishgneenommsjothojgcsbifqmgtdallktsppoiksmahgtpmangtghqctcnco"
		"fgeeqtlctnbdnijmpnfbtetsaojoheamkqispaagfnjtckdjdicoecfqqokpsciasikfadlgqafkciarrombqjsedamodmonartbakhqdehfmtdbnhdcqnslfcfiomopbnqbdprstqqlhlfnsihgnfjs"
		"ihtclnjmsrnbmcmllipstmljashfqipqpokstmcrjhlckpfndmloeppqfcnncjjkpmipelefshtacfnfjrlgmgcraildrmnmqbtmeqspdrpgobdqshccnqloeojnhcgppramnshjhopopkkfrmhdalrf"
		"fgkeaiapgatlkgajbhdiknghrfkkqthcrrsrgsfekepmdicqpfqflcfaihkqhjkehjontlrkheckmqgaodrrrcrrkaojjenintbnkkpshjatghtmcrjtlsrbsdkatqifhcksefilgidehcqjlfbpqkig"
		"ftgehhjobterqmjdbmtagqkkndfjfnqkeoodnqkghoeetftmjkmhgcjmroncabeqilabhcaoqqkpbbhkmmjkotoefisfbdojogdnidtqtcemddohpdkccegaeefgtthnrkgffscqagidjcdfsftmbfmg"
		"bkebblgtonetlsqdqqsglbdjscnatggaicnjfaatfrliptlmpjkgdfhbtbbsttkhbeihqbsbsjjfiarqbtceqcgpphfohinaentaosbmhckioteptsmhaspprabqagjeaiqggjlglbgrakflirtbhoie"
		"gknticpikmhjbspflncddtpdqgqdmfakhnjppfqfjdgknnhqgctjbgfkmbnqgnhngibnnrlcmrfflenrgmtatqkdrdaqjtbphcjntmhljmiarbkpgbprrfaobmcklertgsmsktbaekmndoajpqgmntto"
		"lnedrcoeasodjpdffpsbctcrhjcainplglgefaagkgbabertlqanhcdgdfgdknpqfbmkoeiekjqefodrcdcbrfhbcnemhlbenfotcppmemqcsltmonnetafnfbseftisepjscelsitagllsrflbqdsjb"
		"mhfrsghpnqnpmefbqghtrsqobkkramsmtpbsbingqsnjptklfjkotsjbatsblifddhnfhsdeqrflqhonqqhqpqjhihalpggsftpmrtigqnreaerjaerhngpnfpeanlkscsdmjlsrrhbjlsseohltnsms"
		"ojktansolngmqejnecppmftgndggbkfhthhlargdkmpgjqmnshakmmrfppeqrberidibaoectmiiianhtnrmrgjmnfblgrihaiimpeooqcofpheomnskaioffpqmmqtertqmdkgmfmjatngdgffsfmek"
		"hmombnqsefcipimaabmlgtgeqepbqlddpshqdqgibiiqiajanndlechagcncnrrjhfrkbqkoqkkfklrpfbsjpgcbipdoemddjmgciqqfhtcjktrhmpjhblacgdqdilgrpmaebibihdjkogrtosspjtji"
		"crlcijaecmapmndaiecollnfkmmtlctflkiaaaqoeijqneibicplobiqfbhqphngjnsbfgpjgqstmsabnietbnpgooobbhtlbsmsqaadqkcjipcnpgmqttcfoqgppgsiqlhmdhptrkarfolabpqmpksj"
		"sqqnopcksjpbikafmnorhfjanfnihljftftombekcllkoehgrbeqtnrmlkmknbqmshsladbcgneajlhgmlodqlptnhkgasllfjcfeptladljgshkbcosnjjhjtfbrimosotockfcfjmlhtcbnqthrags"
		"adajmmectpqbgcdldhpktrlmfclodjnpnnerfatqqprcjnfmaapljsegnhbqrodchtleaknirkktphdiaktjjpqcprkelfgkejgqlteicgtropfofrpgedatakddhbfmkmibdncftndfialgrhmoknnd"
		"prsdkqpnapgdaijaoercejioinikgnfbcqenmlgmtmptnqlhajbrkcdkplabqgotolegcksbofntcesofalpcofrrskgqefkpjqklgdrdqrrnpmshpgbcdklnarjrctedhoofsmjgbgtikkisijmladf"
		"mngbhsglfarlkbmjckidnkllsmdkeshjlnktlqcjjlmlneahgjktlnkkgfmkelthqcsasajtenlrrlepmhpeargsdsjtjasfcrfnjgmntpkihhetolpgibfdlgoasnsbkpglokfnghonokeabmhbneff"
		"klriehbgdtsrkdcqcijrsfjlrqnlmkiobrdsfqeaqcjgrdcamdjkisoghhjtjjocgjadrfdntmljqfjaiskjiehpdqhmrnpdohtlecrehindgopoefpmccarstchmjlgqcjbegflhkgnebtatpmnjeka"
		"dehhnkfkmplrniaaktfgarglekqnphnkdbkrlphecknqknimmgsfdeihofabeoehhoesjdoefhahbatfgrcjnlqaqjbaprhclemnhhrfgrmtrmrqbtfpkopgdiskgsercqcbptsoilnspkoqktdmnkli"
		"tbkftoobdrpsinerqshlabacmdpsgssftjctdimgfhrgnbpjlcnmdnghinfoleldnnoicgptgeftrmajonnjstrhfonqsfldkfemelekpbbmobnihgsfshedbslmpdpfitsmcoorppkjjpsicinapkdq"
		"ioadjqashsckmrtaebjfrtntttlojgdjadmclmaldonhlmtigjnditoisfohljqdfafqerttmmtprsddtjsaimagjofmqnpbfnjbcjnonmckcffcodcohcmqijiecqrtjhblqgsbkaemrjoefismcljl"
		"ajhpffgoetsmfinpirirhobmpmqrpfahpaomrbhbarnsfgnfenodaqhhadqpbrcijjagkthciaansgkolfrlnqknahaneobndnlnnsibsihigjdsgabtjmebteopthacalifjqttqstdhcbgpofegkfr"
		"glmfseakpiiqqthmrhpqbicqdaajkfhqqlogiojpormkqlcfksbmsqibqbdsscghnanbgcralbctefehpstnothcakatmggrtllrgakrnmrrjbeqlpcfhjthttsdsqajalggdidqnmgcoctfsbdrccqn"
		"opqedindmljpafmnrshdasbklehnsegelciolnkdftkrqccomjrfisplopfntljcgsijlseikofgrhmbjkgjicadrfiijrcphkqlbatdofbdeofnelcefptoahobrqqqtmhaehpteqoiktcgdqlilkde"
		"krfhgodfsdrdkeooaicdiqjdfmlqdgmfqsecettccifmmlseabhajjdobgdqnpbjffdjfoehcbmgnkkndknntitaocjhkkihidjnrnmloerhpamskfdjfdbarkthnahbdqgbbsehdcpkchaefefktscq"
		"jcqoodprlnkmlplgjgidgjhdfmfekimlcirqdeforisjdkhmiqhgrojcspsapkmjlbfogcbdktefbmjkaqqrkslafjbalfjcggjmakqlbaqdegfeonbflefqnsirdrlkpacqcktedpthnqmijffnkcbp"
		"bkeetqopijddtctcjkkpgophlaanocjhefmdnskchnrtpqbrgdmejhlbtmongpbkbffopqipbrojnhgllspmrhfqlabjholalqhhehcgfipkpbcsljlaiqilijaiqlatahgqhacmijoqcqgnsjfsgnkg"
		"pkgdohcggjcnbrfcgasjiqosgarefhkajjdpqsnctqqafnclfmagbhehtnlemnrccmjskdnjljkqoehajaschcjsiacaftoimesohlesmgohcntdfrfeloctgfamqgmakkpjothgrnnttmpebajnhlmn"
		"ierflbrbemlsdkqaqcmhghlihmboqnaekjbbdtohlrrhanhiptpogscgldahimdsorlrisqlpnspsgpgrkaejckarctfpoqbdtslrodntbajtqprshbhjdtsfkqmfmfiddmbjpgaiskigfrfnseonefk"
		"obdlfimieejflhgtgitmfqjkgortkckqdfiifmqbishtffkdfkqksrbfdsenmgkpdkdbclckbbjhslkdbsgaitrljnfbapqprlqtotjqmkdlnfgpqmheleparmbjtjrqanppeqdrssimdgtttgpccldl"
		"dqndgklsphfapirogrgcdfbodjrramipibkgdcrtbctqlikjrilmffhioqfgagbitehdseolgnhjnktkscoqhnqbjchbabktfjopfiglnfngpeiggpcoispkmplmqnencsahhglalqttatrsotmdjano"
		"hqsdkciebieaohardliplfnfqsagsfafcsamniioqmoctglckajbrdsobtalemigcakpitbqdhkdobrqnhrdcprdgjglbojpgalolecommjsftolgloasldfmbifhranjdtaibhafqkkhenfhhffkicc"
		"bkhiiabrdakdnrdsffbnjosqoqoqqqtstsgtsaqomsrghnensrsimiqsekobtflserrojficesidleijcgjghgedisqtehjarsosepaanadermflkprjnnfblbnhbchkboarbbronmkcqhntckahpfbh"
		"togaqgcracgnpdhbijdqqrhltispntomfaecgslsbslinkjnlfkacjlnrbilncdspamnsqelohmtkbnbspbaeeoogofljajeaojlkncqbgplaaeshstecfsatplapneihgtrtnfmampanmsmkjqmggns"
		"bqsrjprqbifmbcrnpefiqqmsrblehqcbemkohhcipanickorgtrdhkbrlebkmpljhbdpirpprieaksjrjhmjjfgmctcgogpntsaiqqpfqlftbpiloamdrshtjbgdhbihmjhafcfnodmpkmsqmctcasbj"
		"ttehnngrcnrthoenjrjtjtpocgqoejqqbmdofjltoakbgppqeqpfhdtjjhqgjmckerecshnmtefftmbdijiqmarntntirnkokgqinjmefskekdtlmatemislcjmlpcffbngopklaabrleiorinnabdep"
		"niticqfdkdkrobjoogrspdhpinicqmjjaijofhshkiqqbfdpmantenoedsiopgrasijbipisfcgjgoeojtoptldcjdiqjsqtssntnbjleqakkeelptgocbilejtfthqjfjitdskhokjqhghcrfjtgjkc"
		"kbtjiptortfarptdralegstdpacbjepmrobgkmaterlnmcrbcasblregrtisppknketmqllmaogmqpfspdtgaqnjhnicispkcgcljfdjtbnpqtgmcrkpfpemampbdclfbgqclmelnjskaqodoqktmome"
		"ttfcnrhgdqjgafjnoippqbkksaccgggffehkbhrqpscpdmarmieijoltgnnntmkqqkgjrpfmnhtqltgdtcebjpmpagalkltgbrpknmoglnpdebsedorejjabpmmfdddqbksoomagrhbcitsegpiheajm"
		"nnjirfrsppmkieifmjtmajigqjobbdfoigpfleptthbtejrikimksbrocdhdsekglrmcbtbahcmddjdnrpehinccqbgogqajnelgefgdhksdtbqjimijfclberhcfalkecqatpphfncrgsshlgqqjhkf"
		"rjhcjsfombgmqolohnlgdbnohbdqifbroamekrkdsihhckbcpeikfnfmoaboromlpehfnjalstkabdcqhchehejnqkinemqlierbfjedjpekkstsnsoacdokncpkglnghkhnmdibkmdbdclqafqojceo"
		"qtqcdkakmhpedernibgddrtqpikekpktghbjjcmbbtgqpdceeihastqntgjbntamsobhqfjjrhgmciitiitghhlsfatlmadcoqkcoldlkbdmbmdkaoitbartaqkeinhcbrqpaagkbcodgsnsmbrgngfo"
		"ohkdmrrngojgohihjpkpfpfjjcpcamipltkdqhrdnsbtfchhjroofadoolipprchqekedttrrnqppdcenqkkinedqekmbetjijgljriskrnrmhnfqdhejdtfibrbfqlfsjjtgjrrgdgtkaqgdedehckp"
		"qhjbqatobinhrcqefdpidloshrdpmncimlbidaoqatescmctpjhkmobadehpjbpnfjcabircinacfonndndhhqhkagsbifpnojfijckjhclnqrslkbsjsslkejemhtrnadbjrdtffcsbtiebjpctnocr"
		"pgccrtqjojsmnrjsmtmlhifidhaqbcgrailjttsgjqkogtessibfrsnmsnbthhithmaslsemhosffdpddqaahgfflgqtnfkmjlkabhfandftsaocjpoqntnefjpkggopjrikqfdjaiatbpnkctspldti"
		"mpttnfgocgqsltamiadbhilbhbqseitipstapsokekiqcaakndlalookhcbdkadrkdjfbppfgqnaqncbifclticskdnnpqcflmcehkcfgpfobhqjmkbdspnakgnfpqkgiedhofnmakhnspdcfqgpllpb"
		"sbgfridrmgqtljlemsrkfaecqcrtofaegsjpgeellakocbsomqqriaardjqjgrnepotosdrbqhqsaomecaolagippeeonjsbpkponmhbldtdkdimdopqadlhaibnjmgfcnlhrsjaoaeeeeitsepshtrt"
		"ttfillnfrqmopbpbclfspfrfjnpjemiddflgrrlgneaarhbtssrfepkfafgekhtnmcmbldhrtirrhlqgbgdrngdndjjnqatbclcooklgkadrdtpfrtckfrpitqopqnilelrkbiqlatielejapllmjgma"
		"pgpltqophlgitotmgtqrpfjkiaojthjonrrfnmmadsapflhlcpasmjaacpcbcdhhaqmfafrqpjlmakpdfpbrrnjtidmchlkthoriloetqhlqjhlgoepdseogagbhjlsjrpjjcnasmdgbcstrcomakhtk"
		"fajpdieapnbrsnhcroptmoioibhsigbfskansqnojhdtalbjfqjrcjdkkkbkioqgeitpffbgeesqhtgmihbkqfnthgjqaroqsolplmbhjtdqlbblicnrtgqherdeprbfdeagrbnsnjgqkhhlcmibteap"
		"bdainnnirnhghaqmbdimkhdmtdgkhggacsjhlcpaiotphphishabgpfrslarsssmqhttbgljbkqigpqqojraqdkpoceeacqibphdckepbbdtqlplandrifechithdppedohrfmmgfprbgmetriiffman"
		"mtmpoiajotgtdsrifocetgdqglcepcrhbjphjpregppconkltepsdkpbnjfilcieedlnkajqifscsbfjrbiadporetfpoftsicdkpnhdsrrikcripratmoqqgnlatcstrbkmgrhegqejsojoljfeqbmc"
		"geofsmfhfplmesicoflftmlkoqgkjteppsbfcsntfedjpedjjhgitrknfrpoqtcdjpilnbdsggtbkcctbjhbssoqhkkpbesltgomircgebtgqngrofknpfjcpljiqhthooaolomhidoeqmnlreqfbrti"
		"ajqqqqqccqifkansdtomladaqtfrqrfqgbfcjbrljfrlsccnbifeiiqetcbptserabtjoibdokgemirnjdjrdfodthksgghshthbhaqnkdrcdphmkqcfciibplmnrllrklsslhlocbqfqqksmedgmeat"
		"henepengheqtlhnnibkqjagcecaismifinbejpcrlsqcrbhsorgekfsgtkprdpolihhroboflchbpolkmjgooeangpcbkqnsemisgcerfdsmsjcctaqfqildenegkjrgofqatarqqijgjdaaeigaqrpm"
		"cmtebikhfhhetrbhfcnofnpbbnokcjcebnjpblcgscdkterqsdkdirfcctmeaojoakjbbdamfdcqtlmrgpmpmjrhijlbpmppcqjetjqrekfdnsmafepjoeqofihaacipkrtcshtcjqrcojctfjblnrss"
		"fflsatnkiemsldmaajogkrshstleijcogfegqjjennoergqjhkpjtfrkqiofjilpopokephribnfabghdordtgnqgtnhheobtimppteemrjmkqmnkjqbhbjfmcmagsbrhfmceisjfibhqnbsojtndbsp"
		"dcpkbrtaceotmniknbrjpstbakpdlfspiorjdibrmpifaipnkmordnsdefgplqclclmranhmapjbqqogbjpeoftslrgonafimjfeceiomkpigkghlblfscqjtcpfomfsbccphdktnftthfhkskqqfmse"
		"gfbasgttjnhqqrhjogbclimbkarpmhmknnllmccbpjjesifnoghrgtsjmhqehihaosdgmrtttadribkchrlgjbpbilrpmehgocesadstdnqlotfoiqmjrtkrcafoqeadhenhtlscrgfdrcrgsjphisrl"
		"kcrsskbfohegsoihbglsiiqtkmskcpnejlcinqnhdkfneobfmmqammtoqsfkfkopnrdgnigqklbprcmjoictnnnjdkajbgqgdlnitlqkosrmajnhkhsdbleecqfpdbngmspejlgebdicenbobtrckcse"
		"selnrfmcphsfkebmtbgdohspshjijafaqifnfrhbqfstjllamjesioogbpglpldlmirrsekokinltqmdfqcfkqlldsotbjcnktdiqnogoirnejrcrththldcjjbctqibhdbdqpjkptqmafosqnjpemrf"
		"clanhigolhstotckskclpiblnkgkdphrghcnhiakhkkbbedmordbremloknjfaseiarhijsptajbeefkciltmpcsrhacisgitqphrnpjnqcjahtopkotriroqrjqqhehplgnfnckjeacllqsocrllgst"
		"qhpeotlckrphdjkmnkoqndohfdtqjrhrqcncneeeoldranbfpibjlhqqkhfmqmbmpphitlefpiopnibjqckhkgdmgiqonstingiejnkenqagebhaprtrqdcodsiqqhqjnfopkqtdmlbjebbmkbjgqlmt"
		"cbisiqioboblkagoeipijratscsonkfhdfgecgsdmlholnipnqqcnqodsejegglkmjogpebtpinscogpkckpkqkjmtfsriajsgpfkjfrrsilmotcibjsjttbkelinerlkfinonkdespqeglmhadqmcjc"
		"tmkmqaphrpmljognnnbjtmcgfrortdtsqkcekjlhfpkgkqlpcmebfsakpothssrgaakkbojgjtetipgkildfjdhrsgeiqbgrnqhpcrneispifcknngsojrltdphajfrcoqjqfdagnqossrmddcreajep"
		"qdhrjqadnjlsmmqradqkainpcctoddkmhjjigjltlcjpgsnsbjibjnilihslladkjnspobgfpiboggmtpnaegahohrskrnatskgnlnktndnljfkekcarcadjrnahhmgfpmksrbrcqkngidckrphtpdbe"
		"indprjnmopllqiofltllpfbmabehqreekhmhjrmdmdgbdmggejjtoldhehgmekqgkaotrsocbmdqfjdjsmaepdlldkdhamocmancshelmttjickshkocnsgqijqabcdgoqaeqehipgrpjhnijtcoridr"
		"stslnnrhbrdrnkriqgdrfifgiibrqepgpfsikphlfkbsaktqrcgodlbdtcaishgneenommsjothojgcsbifqmgtdallktsppoiksmahgtpmangtghqctcncofgeeqtlctnbdnijmpnfbtetsaojoheam"
		"kqispaagfnjtckdjdicoecfqqokpsciasikfadlgqafkciarrombqjsedamodmonartbakhqdehfmtdbnhdcqnslfcfiomopbnqbdprstqqlhlfnsihgnfjsihtclnjmsrnbmcmllipstmljashfqipq"
		"pokstmcrjhlckpfndmloeppqfcnncjjkpmipelefshtacfnfjrlgmgcraildrmnmqbtmeqspdrpgobdqshccnqloeojnhcgppramnshjhopopkkfrmhdalrffgkeaiapgatlkgajbhdiknghrfkkqthc"
		"rrsrgsfekepmdicqpfqflcfaihkqhjkehjontlrkheckmqgaodrrrcrrkaojjenintbnkkpshjatghtmcrjtlsrbsdkatqifhcksefilgidehcqjlfbpqkigftgehhjobterqmjdbmtagqkkndfjfnqk"
		"eoodnqkghoeetftmjkmhgcjmroncabeqilabhcaoqqkpbbhkmmjkotoefisfbdojogdnidtqtcemddohpdkccegaeefgtthnrkgffscqagidjcdfsftmbfmgbkebblgtonetlsqdqqsglbdjscnatgga"
		"icnjfaatfrliptlmpjkgdfhbtbbsttkhbeihqbsbsjjfiarqbtceqcgpphfohinaentaosbmhckioteptsmhaspprabqagjeaiqggjlglbgrakflirtbhoiegknticpikmhjbspflncddtpdqgqdmfak"
		"hnjppfqfjdgknnhqgctjbgfkmbnqgnhngibnnrlcmrfflenrgmtatqkdrdaqjtbphcjntmhljmiarbkpgbprrfaobmcklertgsmsktbaekmndoajpqgmnttolnedrcoeasodjpdffpsbctcrhjcainpl"
		"glgefaagkgbabertlqanhcdgdfgdknpqfbmkoeiekjqefodrcdcbrfhbcnemhlbenfotcppmemqcsltmonnetafnfbseftisepjscelsitagllsrflbqdsjbmhfrsghpnqnpmefbqghtrsqobkkramsm"
		"tpbsbingqsnjptklfjkotsjbatsblifddhnfhsdeqrflqhonqqhqpqjhihalpggsftpmrtigqnreaerjaerhngpnfpeanlkscsdmjlsrrhbjlsseohltnsmsojktansolngmqejnecppmftgndggbkfh"
		"thhlargdkmpgjqmnshakmmrfppeqrberidibaoectmiiianhtnrmrgjmnfblgrihaiimpeooqcofpheomnskaioffpqmmqtertqmdkgmfmjatngdgffsfmekhmombnqsefcipimaabmlgtgeqepbqldd"
		"pshqdqgibiiqiajanndlechagcncnrrjhfrkbqkoqkkfklrpfbsjpgcbipdoemddjmgciqqfhtcjktrhmpjhblacgdqdilgrpmaebibihdjkogrtosspjtjicrlcijaecmapmndaiecollnfkmmtlctf"
		"lkiaaaqoeijqneibicplobiqfbhqphngjnsbfgpjgqstmsabnietbnpgooobbhtlbsmsqaadqkcjipcnpgmqttcfoqgppgsiqlhmdhptrkarfolabpqmpksjsqqnopcksjpbikafmnorhfjanfnihljf"
		"tftombekcllkoehgrbeqtnrmlkmknbqmshsladbcgneajlhgmlodqlptnhkgasllfjcfeptladljgshkbcosnjjhjtfbrimosotockfcfjmlhtcbnqthragsadajmmectpqbgcdldhpktrlmfclodjnp"
		"nnerfatqqprcjnfmaapljsegnhbqrodchtleaknirkktphdiaktjjpqcprkelfgkejgqlteicgtropfofrpgedatakddhbfmkmibdncftndfialgrhmoknndprsdkqpnapgdaijaoercejioinikgnfb"
		"cqenmlgmtmptnqlhajbrkcdkplabqgotolegcksbofntcesofalpcofrrskgqefkpjqklgdrdqrrnpmshpgbcdklnarjrctedhoofsmjgbgtikkisijmladfmngbhsglfarlkbmjckidnkllsmdkeshj"
		"lnktlqcjjlmlneahgjktlnkkgfmkelthqcsasajtenlrrlepmhpeargsdsjtjasfcrfnjgmntpkihhetolpgibfdlgoasnsbkpglokfnghonokeabmhbneffklriehbgdtsrkdcqcijrsfjlrqnlmkio"
		"brdsfqeaqcjgrdcamdjkisoghhjtjjocgjadrfdntmljqfjaiskjiehpdqhmrnpdohtlecrehindgopoefpmccarstchmjlgqcjbegflhkgnebtatpmnjekadehhnkfkmplrniaaktfgarglekqnphnk"
		"dbkrlphecknqknimmgsfdeihofabeoehhoesjdoefhahbatfgrcjnlqaqjbaprhclemnhhrfgrmtrmrqbtfpkopgdiskgsercqcbptsoilnspkoqktdmnklitbkftoobdrpsinerqshlabacmdpsgssf"
		"tjctdimgfhrgnbpjlcnmdnghinfoleldnnoicgptgeftrmajonnjstrhfonqsfldkfemelekpbbmobnihgsfshedbslmpdpfitsmcoorppkjjpsicinapkdqioadjqashsckmrtaebjfrtntttlojgdj"
		"admclmaldonhlmtigjnditoisfohljqdfafqerttmmtprsddtjsaimagjofmqnpbfnjbcjnonmckcffcodcohcmqijiecqrtjhblqgsbkaemrjoefismcljlajhpffgoetsmfinpirirhobmpmqrpfah"
		"paomrbhbarnsfgnfenodaqhhadqpbrcijjagkthciaansgkolfrlnqknahaneobndnlnnsibsihigjdsgabtjmebteopthacalifjqttqstdhcbgpofegkfrglmfseakpiiqqthmrhpqbicqdaajkfhq"
		"qlogiojpormkqlcfksbmsqibqbdsscghnanbgcralbctefehpstnothcakatmggrtllrgakrnmrrjbeqlpcfhjthttsdsqajalggdidqnmgcoctfsbdrccqnopqedindmljpafmnrshdasbklehnsege"
		"lciolnkdftkrqccomjrfisplopfntljcgsijlseikofgrhmbjkgjicadrfiijrcphkqlbatdofbdeofnelcefptoahobrqqqtmhaehpteqoiktcgdqlilkdekrfhgodfsdrdkeooaicdiqjdfmlqdgmf"
		"qsecettccifmmlseabhajjdobgdqnpbjffdjfoehcbmgnkkndknntitaocjhkkihidjnrnmloerhpamskfdjfdbarkthnahbdqgbbsehdcpkchaefefktscqjcqoodprlnkmlplgjgidgjhdfmfekiml"
		"cirqdeforisjdkhmiqhgrojcspsapkmjlbfogcbdktefbmjkaqqrkslafjbalfjcggjmakqlbaqdegfeonbflefqnsirdrlkpacqcktedpthnqmijffnkcbpbkeetqopijddtctcjkkpgophlaanocjh"
		"efmdnskchnrtpqbrgdmejhlbtmongpbkbffopqipbrojnhgllspmrhfqlabjholalqhhehcgfipkpbcsljlaiqilijaiqlatahgqhacmijoqcqgnsjfsgnkgpkgdohcggjcnbrfcgasjiqosgarefhka"
		"jjdpqsnctqqafnclfmagbhehtnlemnrccmjskdnjljkqoehajaschcjsiacaftoimesohlesmgohcntdfrfeloctgfamqgmakkpjothgrnnttmpebajnhlmnierflbrbemlsdkqaqcmhghlihmboqnae"
		"kjbbdtohlrrhanhiptpogscgldahimdsorlrisqlpnspsgpgrkaejckarctfpoqbdtslrodntbajtqprshbhjdtsfkqmfmfiddmbjpgaiskigfrfnseonefkobdlfimieejflhgtgitmfqjkgortkckq"
		"dfiifmqbishtffkdfkqksrbfdsenmgkpdkdbclckbbjhslkdbsgaitrljnfbapqprlqtotjqmkdlnfgpqmheleparmbjtjrqanppeqdrssimdgtttgpccldldqndgklsphfapirogrgcdfbodjrramip"
		"ibkgdcrtbctqlikjrilmffhioqfgagbitehdseolgnhjnktkscoqhnqbjchbabktfjopfiglnfngpeiggpcoispkmplmqnencsahhglalqttatrsotmdjanohqsdkciebieaohardliplfnfqsagsfaf"
		"csamniioqmoctglckajbrdsobtalemigcakpitbqdhkdobrqnhrdcprdgjglbojpgalolecommjsftolgloasldfmbifhranjdtaibhafqkkhenfhhffkiccbkhiiabrdakdnrdsffbnjosqoqoqqqts"
		"tsgtsaqomsrghnensrsimiqsekobtflserrojficesidleijcgjghgedisqtehjarsosepaanadermflkprjnnfblbnhbchkboarbbronmkcqhntckahpfbhtogaqgcracgnpdhbijdqqrhltispntom"
		"faecgslsbslinkjnlfkacjlnrbilncdspamnsqelohmtkbnbspbaeeoogofljajeaojlkncqbgplaaeshstecfsatplapneihgtrtnfmampanmsmkjqmggnsbqsrjprqbifmbcrnpefiqqmsrblehqcb"
		"emkohhcipanickorgtrdhkbrlebkmpljhbdpirpprieaksjrjhmjjfgmctcgogpntsaiqqpfqlftbpiloamdrshtjbgdhbihmjhafcfnodmpkmsqmctcasbjttehnngrcnrthoenjrjtjtpocgqoejqq"
		"bmdofjltoakbgppqeqpfhdtjjhqgjmckerecshnmtefftmbdijiqmarntntirnkokgqinjmefskekdtlmatemislcjmlpcffbngopklaabrleiorinnabdepniticqfdkdkrobjoogrspdhpinicqmjj"
		"aijofhshkiqqbfdpmantenoedsiopgrasijbipisfcgjgoeojtoptldcjdiqjsqtssntnbjleqakkeelptgocbilejtfthqjfjitdskhokjqhghcrfjtgjkckbtjiptortfarptdralegstdpacbjepm"
		"robgkmaterlnmcrbcasblregrtisppknketmqllmaogmqpfspdtgaqnjhnicispkcgcljfdjtbnpqtgmcrkpfpemampbdclfbgqclmelnjskaqodoqktmomettfcnrhgdqjgafjnoippqbkksaccgggf"
		"fehkbhrqpscpdmarmieijoltgnnntmkqqkgjrpfmnhtqltgdtcebjpmpagalkltgbrpknmoglnpdebsedorejjabpmmfdddqbksoomagrhbcitsegpiheajmnnjirfrsppmkieifmjtmajigqjobbdfo"
		"igpfleptthbtejrikimksbrocdhdsekglrmcbtbahcmddjdnrpehinccqbgogqajnelgefgdhksdtbqjimijfclberhcfalkecqatpphfncrgsshlgqqjhkfrjhcjsfombgmqolohnlgdbnohbdqifbr"
		"oamekrkdsihhckbcpeikfnfmoaboromlpehfnjalstkabdcqhchehejnqkinemqlierbfjedjpekkstsnsoacdokncpkglnghkhnmdibkmdbdclqafqojceoqtqcdkakmhpedernibgddrtqpikekpkt"
		"ghbjjcmbbtgqpdceeihastqntgjbntamsobhqfjjrhgmciitiitghhlsfatlmadcoqkcoldlkbdmbmdkaoitbartaqkeinhcbrqpaagkbcodgsnsmbrgngfoohkdmrrngojgohihjpkpfpfjjcpcamip"
		"ltkdqhrdnsbtfchhjroofadoolipprchqekedttrrnqppdcenqkkinedqekmbetjijgljriskrnrmhnfqdhejdtfibrbfqlfsjjtgjrrgdgtkaqgdedehckpqhjbqatobinhrcqefdpidloshrdpmnci"
		"mlbidaoqatescmctpjhkmobadehpjbpnfjcabircinacfonndndhhqhkagsbifpnojfijckjhclnqrslkbsjsslkejemhtrnadbjrdtffcsbtiebjpctnocrpgccrtqjojsmnrjsmtmlhifidhaqbcgr"
		"ailjttsgjqkogtessibfrsnmsnbthhithmaslsemhosffdpddqaahgfflgqtnfkmjlkabhfandftsaocjpoqntnefjpkggopjrikqfdjaiatbpnkctspldtimpttnfgocgqsltamiadbhilbhbqseiti"
		"pstapsokekiqcaakndlalookhcbdkadrkdjfbppfgqnaqncbifclticskdnnpqcflmcehkcfgpfobhqjmkbdspnakgnfpqkgiedhofnmakhnspdcfqgpllpbsbgfridrmgqtljlemsrkfaecqcrtofae"
		"gsjpgeellakocbsomqqriaardjqjgrnepotosdrbqhqsaomecaolagippeeonjsbpkponmhbldtdkdimdopqadlhaibnjmgfcnlhrsjaoaeeeeitsepshtrtttfillnfrqmopbpbclfspfrfjnpjemid"
		"dflgrrlgneaarhbtssrfepkfafgekhtnmcmbldhrtirrhlqgbgdrngdndjjnqatbclcooklgkadrdtpfrtckfrpitqopqnilelrkbiqlatielejapllmjgmapgpltqophlgitotmgtqrpfjkiaojthjo"
		"nrrfnmmadsapflhlcpasmjaacpcbcdhhaqmfafrqpjlmakpdfpbrrnjtidmchlkthoriloetqhlqjhlgoepdseogagbhjlsjrpjjcnasmdgbcstrcomakhtkfajpdieapnbrsnhcroptmoioibhsigbf"
		"skansqnojhdtalbjfqjrcjdkkkbkioqgeitpffbgeesqhtgmihbkqfnthgjqaroqsolplmbhjtdqlbblicnrtgqherdeprbfdeagrbnsnjgqkhhlcmibteapbdainnnirnhghaqmbdimkhdmtdgkhgga"
		"csjhlcpaiotphphishabgpfrslarsssmqhttbgljbkqigpqqojraqdkpoceeacqibphdckepbbdtqlplandrifechithdppedohrfmmgfprbgmetriiffmanmtmpoiajotgtdsrifocetgdqglcepcrh"
		"bjphjpregppconkltepsdkpbnjfilcieedlnkajqifscsbfjrbiadporetfpoftsicdkpnhdsrrikcripratmoqqgnlatcstrbkmgrhegqejsojoljfeqbmcgeofsmfhfplmesicoflftmlkoqgkjtep"
		"psbfcsntfedjpedjjhgitrknfrpoqtcdjpilnbdsggtbkcctbjhbssoqhkkpbesltgomircgebtgqngrofknpfjcpljiqhthooaolomhidoeqmnlreqfbrtiajqqqqqccqifkansdtomladaqtfrqrfq"
		"gbfcjbrljfrlsccnbifeiiqetcbptserabtjoibdokgemirnjdjrdfodthksgghshthbhaqnkdrcdphmkqcfciibplmnrllrklsslhlocbqfqqksmedgmeathenepengheqtlhnnibkqjagcecaismif"
		"inbejpcrlsqcrbhsorgekfsgtkprdpolihhroboflchbpolkmjgooeangpcbkqnsemisgcerfdsmsjcctaqfqildenegkjrgofqatarqqijgjdaaeigaqrpmcmtebikhfhhetrbhfcnofnpbbnokcjce"
		"bnjpblcgscdkterqsdkdirfcctmeaojoakjbbdamfdcqtlmrgpmpmjrhijlbpmppcqjetjqrekfdnsmafepjoeqofihaacipkrtcshtcjqrcojctfjblnrssfflsatnkiemsldmaajogkrshstleijco"
		"gfegqjjennoergqjhkpjtfrkqiofjilpopokephribnfabghdordtgnqgtnhheobtimppteemrjmkqmnkjqbhbjfmcmagsbrhfmceisjfibhqnbsojtndbspdcpkbrtaceotmniknbrjpstbakpdlfsp"
		"iorjdibrmpifaipnkmordnsdefgplqclclmranhmapjbqqogbjpeoftslrgonafimjfeceiomkpigkghlblfscqjtcpfomfsbccphdktnftthfhkskqqfmsegfbasgttjnhqqrhjogbclimbkarpmhmk"
		"nnllmccbpjjesifnoghrgtsjmhqehihaosdgmrtttadribkchrlgjbpbilrpmehgocesadstdnqlotfoiqmjrtkrcafoqeadhenhtlscrgfdrcrgsjphisrlkcrsskbfohegsoihbglsiiqtkmskcpne"
		"jlcinqnhdkfneobfmmqammtoqsfkfkopnrdgnigqklbprcmjoictnnnjdkajbgqgdlnitlqkosrmajnhkhsdbleecqfpdbngmspejlgebdicenbobtrckcseselnrfmcphsfkebmtbgdohspshjijafa"
		"qifnfrhbqfstjllamjesioogbpglpldlmirrsekokinltqmdfqcfkqlldsotbjcnktdiqnogoirnejrcrththldcjjbctqibhdbdqpjkptqmafosqnjpemrfclanhigolhstotckskclpiblnkgkdphr"
		"ghcnhiakhkkbbedmordbremloknjfaseiarhijsptajbeefkciltmpcsrhacisgitqphrnpjnqcjahtopkotriroqrjqqhehplgnfnckjeacllqsocrllgstqhpeotlckrphdjkmnkoqndohfdtqjrhr"
		"qcncneeeoldranbfpibjlhqqkhfmqmbmpphitlefpiopnibjqckhkgdmgiqonstingiejnkenqagebhaprtrqdcodsiqqhqjnfopkqtdmlbjebbmkbjgqlmtcbisiqioboblkagoeipijratscsonkfh"
		"dfgecgsdmlholnipnqqcnqodsejegglkmjogpebtpinscogpkckpkqkjmtfsriajsgpfkjfrrsilmotcibjsjttbkelinerlkfinonkdespqeglmhadqmcjctmkmqaphrpmljognnnbjtmcgfrortdts"
		"qkcekjlhfpkgkqlpcmebfsakpothssrgaakkbojgjtetipgkildfjdhrsgeiqbgrnqhpcrneispifcknngsojrltdphajfrcoqjqfdagnqossrmddcreajepqdhrjqadnjlsmmqradqkainpcctoddkm"
		"hjjigjltlcjpgsnsbjibjnilihslladkjnspobgfpiboggmtpnaegahohrskrnatskgnlnktndnljfkekcarcadjrnahhmgfpmksrbrcqkngidckrphtpdbeindprjnmopllqiofltllpfbmabehqree"
		"khmhjrmdmdgbdmggejjtoldhehgmekqgkaotrsocbmdqfjdjsmaepdlldkdhamocmancshelmttjickshkocnsgqijqabcdgoqaeqehipgrpjhnijtcoridrstslnnrhbrdrnkriqgdrfifgiibrqepg"
		"pfsikphlfkbsaktqrcgodlbdtcaishgneenommsjothojgcsbifqmgtdallktsppoiksmahgtpmangtghqctcncofgeeqtlctnbdnijmpnfbtetsaojoheamkqispaagfnjtckdjdicoecfqqokpscia"
		"sikfadlgqafkciarrombqjsedamodmonartbakhqdehfmtdbnhdcqnslfcfiomopbnqbdprstqqlhlfnsihgnfjsihtclnjmsrnbmcmllipstmljashfqipqpokstmcrjhlckpfndmloeppqfcnncjjk"
		"pmipelefshtacfnfjrlgmgcraildrmnmqbtmeqspdrpgobdqshccnqloeojnhcgppramnshjhopopkkfrmhdalrffgkeaiapgatlkgajbhdiknghrfkkqthcrrsrgsfekepmdicqpfqflcfaihkqhjke"
		"hjontlrkheckmqgaodrrrcrrkaojjenintbnkkpshjatghtmcrjtlsrbsdkatqifhcksefilgidehcqjlfbpqkigftgehhjobterqmjdbmtagqkkndfjfnqkeoodnqkghoeetftmjkmhgcjmroncabeq"
		"ilabhcaoqqkpbbhkmmjkotoefisfbdojogdnidtqtcemddohpdkccegaeefgtthnrkgffscqagidjcdfsftmbfmgbkebblgtonetlsqdqqsglbdjscnatggaicnjfaatfrliptlmpjkgdfhbtbbsttkh"
		"beihqbsbsjjfiarqbtceqcgpphfohinaentaosbmhckioteptsmhaspprabqagjeaiqggjlglbgrakflirtbhoiegknticpikmhjbspflncddtpdqgqdmfakhnjppfqfjdgknnhqgctjbgfkmbnqgnhn"
		"gibnnrlcmrfflenrgmtatqkdrdaqjtbphcjntmhljmiarbkpgbprrfaobmcklertgsmsktbaekmndoajpqgmnttolnedrcoeasodjpdffpsbctcrhjcainplglgefaagkgbabertlqanhcdgdfgdknpq"
		"fbmkoeiekjqefodrcdcbrfhbcnemhlbenfotcppmemqcsltmonnetafnfbseftisepjscelsitagllsrflbqdsjbmhfrsghpnqnpmefbqghtrsqobkkramsmtpbsbingqsnjptklfjkotsjbatsblifd"
		"dhnfhsdeqrflqhonqqhqpqjhihalpggsftpmrtigqnreaerjaerhngpnfpeanlkscsdmjlsrrhbjlsseohltnsmsojktansolngmqejnecppmftgndggbkfhthhlargdkmpgjqmnshakmmrfppeqrber"
		"idibaoectmiiianhtnrmrgjmnfblgrihaiimpeooqcofpheomnskaioffpqmmqtertqmdkgmfmjatngdgffsfmekhmombnqsefcipimaabmlgtgeqepbqlddpshqdqgibiiqiajanndlechagcncnrrj"
		"hfrkbqkoqkkfklrpfbsjpgcbipdoemddjmgciqqfhtcjktrhmpjhblacgdqdilgrpmaebibihdjkogrtosspjtjicrlcijaecmapmndaiecollnfkmmtlctflkiaaaqoeijqneibicplobiqfbhqphng"
		"jnsbfgpjgqstmsabnietbnpgooobbhtlbsmsqaadqkcjipcnpgmqttcfoqgppgsiqlhmdhptrkarfolabpqmpksjsqqnopcksjpbikafmnorhfjanfnihljftftombekcllkoehgrbeqtnrmlkmknbqm"
		"shsladbcgneajlhgmlodqlptnhkgasllfjcfeptladljgshkbcosnjjhjtfbrimosotockfcfjmlhtcbnqthragsadajmmectpqbgcdldhpktrlmfclodjnpnnerfatqqprcjnfmaapljsegnhbqrodc"
		"htleaknirkktphdiaktjjpqcprkelfgkejgqlteicgtropfofrpgedatakddhbfmkmibdncftndfialgrhmoknndprsdkqpnapgdaijaoercejioinikgnfbcqenmlgmtmptnqlhajbrkcdkplabqgot"
		"olegcksbofntcesofalpcofrrskgqefkpjqklgdrdqrrnpmshpgbcdklnarjrctedhoofsmjgbgtikkisijmladfmngbhsglfarlkbmjckidnkllsmdkeshjlnktlqcjjlmlneahgjktlnkkgfmkelth"
		"qcsasajtenlrrlepmhpeargsdsjtjasfcrfnjgmntpkihhetolpgibfdlgoasnsbkpglokfnghonokeabmhbneffklriehbgdtsrkdcqcijrsfjlrqnlmkiobrdsfqeaqcjgrdcamdjkisoghhjtjjoc"
		"gjadrfdntmljqfjaiskjiehpdqhmrnpdohtlecrehindgopoefpmccarstchmjlgqcjbegflhkgnebtatpmnjekadehhnkfkmplrniaaktfgarglekqnphnkdbkrlphecknqknimmgsfdeihofabeoeh"
		"hoesjdoefhahbatfgrcjnlqaqjbaprhclemnhhrfgrmtrmrqbtfpkopgdiskgsercqcbptsoilnspkoqktdmnklitbkftoobdrpsinerqshlabacmdpsgssftjctdimgfhrgnbpjlcnmdnghinfoleld"
		"nnoicgptgeftrmajonnjstrhfonqsfldkfemelekpbbmobnihgsfshedbslmpdpfitsmcoorppkjjpsicinapkdqioadjqashsckmrtaebjfrtntttlojgdjadmclmaldonhlmtigjnditoisfohljqd"
		"fafqerttmmtprsddtjsaimagjofmqnpbfnjbcjnonmckcffcodcohcmqijiecqrtjhblqgsbkaemrjoefismcljlajhpffgoetsmfinpirirhobmpmqrpfahpaomrbhbarnsfgnfenodaqhhadqpbrci"
		"jjagkthciaansgkolfrlnqknahaneobndnlnnsibsihigjdsgabtjmebteopthacalifjqttqstdhcbgpofegkfrglmfseakpiiqqthmrhpqbicqdaajkfhqqlogiojpormkqlcfksbmsqibqbdsscgh"
		"nanbgcralbctefehpstnothcakatmggrtllrgakrnmrrjbeqlpcfhjthttsdsqajalggdidqnmgcoctfsbdrccqnopqedindmljpafmnrshdasbklehnsegelciolnkdftkrqccomjrfisplopfntljc"
		"gsijlseikofgrhmbjkgjicadrfiijrcphkqlbatdofbdeofnelcefptoahobrqqqtmhaehpteqoiktcgdqlilkdekrfhgodfsdrdkeooaicdiqjdfmlqdgmfqsecettccifmmlseabhajjdobgdqnpbj"
		"ffdjfoehcbmgnkkndknntitaocjhkkihidjnrnmloerhpamskfdjfdbarkthnahbdqgbbsehdcpkchaefefktscqjcqoodprlnkmlplgjgidgjhdfmfekimlcirqdeforisjdkhmiqhgrojcspsapkmj"
		"lbfogcbdktefbmjkaqqrkslafjbalfjcggjmakqlbaqdegfeonbflefqnsirdrlkpacqcktedpthnqmijffnkcbpbkeetqopijddtctcjkkpgophlaanocjhefmdnskchnrtpqbrgdmejhlbtmongpbk"
		"bffopqipbrojnhgllspmrhfqlabjholalqhhehcgfipkpbcsljlaiqilijaiqlatahgqhacmijoqcqgnsjfsgnkgpkgdohcggjcnbrfcgasjiqosgarefhkajjdpqsnctqqafnclfmagbhehtnlemnrc"
		"cmjskdnjljkqoehajaschcjsiacaftoimesohlesmgohcntdfrfeloctgfamqgmakkpjothgrnnttmpebajnhlmnierflbrbemlsdkqaqcmhghlihmboqnaekjbbdtohlrrhanhiptpogscgldahimds"
		"orlrisqlpnspsgpgrkaejckarctfpoqbdtslrodntbajtqprshbhjdtsfkqmfmfiddmbjpgaiskigfrfnseonefkobdlfimieejflhgtgitmfqjkgortkckqdfiifmqbishtffkdfkqksrbfdsenmgkp"
		"dkdbclckbbjhslkdbsgaitrljnfbapqprlqtotjqmkdlnfgpqmheleparmbjtjrqanppeqdrssimdgtttgpccldldqndgklsphfapirogrgcdfbodjrramipibkgdcrtbctqlikjrilmffhioqfgagbi"
		"tehdseolgnhjnktkscoqhnqbjchbabktfjopfiglnfngpeiggpcoispkmplmqnencsahhglalqttatrsotmdjanohqsdkciebieaohardliplfnfqsagsfafcsamniioqmoctglckajbrdsobtalemig"
		"cakpitbqdhkdobrqnhrdcprdgjglbojpgalolecommjsftolgloasldfmbifhranjdtaibhafqkkhenfhhffkiccbkhiiabrdakdnrdsffbnjosqoqoqqqtstsgtsaqomsrghnensrsimiqsekobtfls"
		"errojficesidleijcgjghgedisqtehjarsosepaanadermflkprjnnfblbnhbchkboarbbronmkcqhntckahpfbhtogaqgcracgnpdhbijdqqrhltispntomfaecgslsbslinkjnlfkacjlnrbilncds"
		"pamnsqelohmtkbnbspbaeeoogofljajeaojlkncqbgplaaeshstecfsatplapneihgtrtnfmampanmsmkjqmggnsbqsrjprqbifmbcrnpefiqqmsrblehqcbemkohhcipanickorgtrdhkbrlebkmplj"
		"hbdpirpprieaksjrjhmjjfgmctcgogpntsaiqqpfqlftbpiloamdrshtjbgdhbihmjhafcfnodmpkmsqmctcasbjttehnngrcnrthoenjrjtjtpocgqoejqqbmdofjltoakbgppqeqpfhdtjjhqgjmck"
		"erecshnmtefftmbdijiqmarntntirnkokgqinjmefskekdtlmatemislcjmlpcffbngopklaabrleiorinnabdepniticqfdkdkrobjoogrspdhpinicqmjjaijofhshkiqqbfdpmantenoe";
	EXPECT_EQ(90000, maxValue(input));
}