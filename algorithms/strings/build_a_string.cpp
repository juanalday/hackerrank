// HARD https://www.hackerrank.com/challenges/build-a-string/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

namespace {
	inline std::vector<int> suffixArray(std::string const& str) {
		int len = static_cast<int>(str.size());

		// I will create a vector of tuples, describing the ranks, the next ranks and
		// the suffixes (meaning rank of the next suffix + k)
		std::vector<std::tuple<int, int, int>> rankedSuffixes(str.size());
		// initial ranks are the ASCII values of the chars, and for id I pick 0 to
		// n-1. the next-rank is -1 for now
		std::transform(
			str.cbegin(), str.cend(), rankedSuffixes.begin(),
			[i = 0](auto c) mutable noexcept { return std::make_tuple(c, -1, i++); });

		// Adjust next-rank to rank of the next element. We won't touch the last one
		// obviously In this case, it means the ascii value of the next char
		std::transform(rankedSuffixes.begin(), prev(rankedSuffixes.end()),
			next(rankedSuffixes.cbegin()), rankedSuffixes.begin(),
			[](auto& current, auto const& next) noexcept {
				std::get<1>(current) = std::get<0>(next);
				return current;
			});

		// Since tuple is rank-followingTank-index, this sorts according to rank value
		sort(rankedSuffixes.begin(), rankedSuffixes.end());

		for (int skip = 1; skip < len; skip *= 2) {
			std::adjacent_difference(
				rankedSuffixes.cbegin(), rankedSuffixes.cend(), rankedSuffixes.begin(),
				[rank = 0](auto curr, auto const& prev) mutable noexcept {
					rank += ((std::get<0>(prev) == std::get<0>(curr)) &&
						(std::get<1>(prev) == std::get<1>(curr)))
						? 0
						: 1;
					std::get<0>(curr) = rank;
					std::get<1>(curr) = -1;
					return curr;
				});
			std::get<0>(rankedSuffixes[0]) = 0;

			// I will sort according to the index, so I can use the index to find the
			// next element This is faster than doing find_if for every index to find
			// where is the index+skip value
			sort(rankedSuffixes.begin(), rankedSuffixes.end(),
				[](auto const& lhs, auto const& rhs) noexcept {return std::get<2>(lhs) < std::get<2>(rhs); });

			// I will now adjust the values of rank[sa[i]+k] for all i's within range
			std::transform(std::next(rankedSuffixes.cbegin(), skip),
				rankedSuffixes.cend(), rankedSuffixes.cbegin(),
				rankedSuffixes.begin(),
				[](auto const& skipRank, auto currentRank) noexcept {
					std::get<1>(currentRank) = std::get<0>(skipRank);
					return currentRank;
				});

			// And I sort again, according to ranks...
			sort(rankedSuffixes.begin(), rankedSuffixes.end());
			// Optimization: If the last element has rank == len - 1, we can stop
			if (std::get<0>(rankedSuffixes[0]) == len - 1) break;
		}

		std::vector<int> suffixes(len);
		std::transform(rankedSuffixes.cbegin(), rankedSuffixes.cend(),
			suffixes.begin(),
			[](auto const& tup) noexcept { return std::get<2>(tup); });
		return suffixes;
	}

	std::vector<int> findAllOccurrences(std::string const& s, std::string const& pattern, std::vector<int> const& suffixes) {
		// Binary search to find the starting position of the range
		auto lower = std::lower_bound(suffixes.cbegin(), suffixes.cend(), 0, [&](int idx, int) {return s.compare(idx, pattern.size(), pattern) < 0; });
		auto upper = std::upper_bound(suffixes.cbegin(), suffixes.cend(), 0, [&](int idx, int) {return s.compare(idx, pattern.size(), pattern) <= 0; });

		std::vector<int> result(lower, upper);
		std::vector<int> res;
		for (auto it = lower; it != upper; ++it) {
			res.push_back(*it);
		}

		return result;
	}
	int buildString2(int a, int b, std::string s) {
		std::vector<int> lastPosition(26, -1);  // Last position of each character in the string
		std::vector<int> previousPosition(s.size(), -1);  // Previous position of each character in the string
		std::vector<int> dp(s.size() + 1, INT_MAX);  // DP array to store minimum cost to reach each position
		std::vector<int> maxLength(s.size(), 0);  // Maximum length of substring ending at each position

		std::vector<std::pair<int, int>> positions(26, { -1, -1 });  // current and previous position of each character in the string
		dp[0] = 0;  // Initial cost to build an empty string is 0

		int currentCost{ 0 };
		std::vector<int> costHistory(1 + s.size(), 0);

		auto costToAppend = a;  // Cost to append the current character
		for (int i = 0; i < s.size(); ++i) {
			auto currentChar = s[i];
			int currentCharIndex = (currentChar - 'a');

			if (positions[currentCharIndex].second !=
				-1) {  // If the character has appeared before, the cost to insert it is
				// the smallest of a and b
				costToAppend = std::min(a, b);
			}

			positions[currentCharIndex].second = positions[currentCharIndex].first;
			positions[currentCharIndex].first = i;
			previousPosition[i] = lastPosition[currentCharIndex];
			lastPosition[currentCharIndex] = i;

			// Cost to append the current character
			dp[i + 1] = dp[i] + a;

			if (positions[currentCharIndex].second !=
				-1)  // If the current char has appeared before, we can try copying the
				// substring. Let's evaluate the cost
			{
				auto previousCharIndex = positions[currentCharIndex].second;
			}

			currentCost += costToAppend;

			if (previousPosition[i] != -1) {  // If the character has appeared before
				int previousIndex = previousPosition[i];
				int currentMaxLen = 1;

				while (previousIndex != -1) {
					if (previousIndex == i - 1 || previousIndex == 0) {
						maxLength[previousIndex] = 1;
					}
					else {
						if (s[i - 1] == s[previousIndex - 1]) {
							maxLength[previousIndex] =
								std::min(maxLength[previousIndex - 1] + 1,
									std::min(i - previousIndex, previousIndex + 1));
							currentMaxLen = std::max(currentMaxLen, maxLength[previousIndex]);
						}
						else {
							maxLength[previousIndex] = 1;
						}
					}
					previousIndex = previousPosition[previousIndex];
				}

				// Cost to copy the substring
				dp[i + 1] = std::min(dp[i + 1], dp[i - currentMaxLen + 1] + b);
			}
		}

		return dp.back();
	}

	struct StringBuilder {
		int m_copyCost;
		std::vector<int> m_buyCost;
		std::string m_target;

		StringBuilder(int a, int b, std::string const& str)
			: m_buyCost(26, a)
			, m_copyCost(b)
			, m_target(str)
		{
		}
	};
	int buildString(int a, int b, std::string const& s) {
		if (s.size() == 1)
			return a; // If I only have a letter, I have to buy it

		std::vector<int> charBuyPrice(26, a); // I use this to store the price of buying each character. Once I buy it, if cheaper, I will change it to b
		auto buyPrice = [a, b](std::vector<int>& storage, char c) { int index = c - 'a'; auto ret = std::min(a, b); std::swap(ret, storage[index]); return ret;  };

		std::vector<int> cost(s.size() + 1, 0);
		int partialCost = 0;
		auto costIter = cost.begin();
		*costIter++ = buyPrice(charBuyPrice, s.front()); // We always have to buy at least a letter
		// The second letter is either a copy or a buy, whatever is cheaper
		*costIter++ = buyPrice(charBuyPrice, s.front());
		std::string targetStr(s.begin(), next(s.begin(), 2));
		std::string_view remaining(s);
		remaining.remove_prefix(2);
		while (!remaining.empty()) {
			std::string_view partial;
			for (int j = 0; j < remaining.size(); ++j)
			{
				partial = remaining.substr(0, j + 1);
				//auto occurrences = findAllOccurrences(s, std::string(partial), suffixes);
				auto isthere = targetStr.find(partial);
				if (isthere == std::string::npos)
				{
					partial.remove_suffix(1); // I can't find the substring in the target string. But if it has any information, that part has been found
					break;
				}
			}
			if (partial.empty()) {
				partial = remaining.substr(0, 1); // 1 char
			}

			// I make a copy of the charBuyPrice vector here. Don't forget it. 
			// This is a fake calculation to give me the estimate, but if I don't perform it I don't alter the stats
			auto estimatedCost = std::accumulate(partial.cbegin(), partial.cend(), 0, [&, charBuyPrice](int acc, char c) mutable {return acc + buyPrice(charBuyPrice, c); });
			// Here is the deal: If it is cheaper to buy individual chars, I am NOT copying. I will buy a char at a time
			// and see how it goes on the next iteration. Maybe by doing it I wll find a larger movable string
			// Also, if I have a single char, the 'buyPrice' function will return the best price anyways...
			if ((partial.size() == 1) || (estimatedCost < b)) // I will handle JUST ONE CHAR
			{
				*costIter++ = buyPrice(charBuyPrice, partial.front());
				remaining.remove_prefix(1);
				targetStr.push_back(partial.front());
			}
			else {
				remaining.remove_prefix(partial.size());
				targetStr.append(partial);
				*costIter++ = b; // If the price is the same, I always buy individuals, so it has to be 'b'
			}
			partialCost = std::accumulate(cost.begin(), cost.end(), 0);
		}
		return std::accumulate(cost.begin(), cost.end(), 0);
	}
}  // namespace

TEST(BuildString, sample0) {
	EXPECT_EQ(26, buildString(4, 5, "aabaacaba"));
	EXPECT_EQ(42, buildString(8, 9, "bacbacacb"));
}

TEST(BuildString, case0) {
	EXPECT_EQ(26, buildString(4, 5, "aabaacaba"));
	EXPECT_EQ(42, buildString(8, 9, "bacbacacb"));
}

TEST(BuildString, case3) {
	EXPECT_EQ(20, buildString(1, 2, "cbaasgcbiikaegcbiidcbaasgcbiikaegcbiidir"));
	/*
	cbaasgcbiikaegcbiidcbaasgcbiikaegcbiidir 0
	c baasgcbiikaegcbiidcbaasgcbiikaegcbiidir 1 = 1
	cb aasgcbiikaegcbiidcbaasgcbiikaegcbiidir 1 = 2
	cba asgcbiikaegcbiidcbaasgcbiikaegcbiidir 1 = 3
	cbaa sgcbiikaegcbiidcbaasgcbiikaegcbiidir 1 = 4
	cbaas gcbiikaegcbiidcbaasgcbiikaegcbiidir 1 = 5
	cbaasg cbiikaegcbiidcbaasgcbiikaegcbiidir 1 = 6
	cbaasgcb iikaegcbiidcbaasgcbiikaegcbiidir 2 = 8 // * bought 2 letters rather than moving 2 chars
	cbaasgcbi ikaegcbiidcbaasgcbiikaegcbiidir 1 = 9
	cbaasgcbii kaegcbiidcbaasgcbiikaegcbiidir 1 = 10
	cbaasgcbiik aegcbiidcbaasgcbiikaegcbiidir 1 = 11
	cbaasgcbiika egcbiidcbaasgcbiikaegcbiidir 1 = 12
	cbaasgcbiikae gcbiidcbaasgcbiikaegcbiidir 1 = 13
	cbaasgcbiikaegcbii dcbaasgcbiikaegcbiidir 2 = 15 (moved 5)
	cbaasgcbiikaegcbiid cbaasgcbiikaegcbiidir 1 = 16
	cbaasgcbiikaegcbiidcbaasgcbiikaegcbiid ir 2 = 18 (moved 19)
	cbaasgcbiikaegcbiidcbaasgcbiikaegcbiidi r 1 = 19
	cbaasgcbiikaegcbiidcbaasgcbiikaegcbiidir  1 = 20
	*/
	EXPECT_EQ(24, buildString(1, 3, "cabcjpsdaedsasedsascabcjpsddsdaedsasedsa"));
	/*
	cabcjpsdaedsasedsascabcjpsddsdaedsasedsa 0
	c abcjpsdaedsasedsascabcjpsddsdaedsasedsa 1 = 1
	ca bcjpsdaedsasedsascabcjpsddsdaedsasedsa 1 = 2
	cab cjpsdaedsasedsascabcjpsddsdaedsasedsa 1 = 3
	cabc jpsdaedsasedsascabcjpsddsdaedsasedsa 1 = 4
	cabcj psdaedsasedsascabcjpsddsdaedsasedsa 1 = 5
	cabcjp sdaedsasedsascabcjpsddsdaedsasedsa 1 = 6
	cabcjps daedsasedsascabcjpsddsdaedsasedsa 1 = 7
	cabcjpsd aedsasedsascabcjpsddsdaedsasedsa 1 = 8
	cabcjpsda edsasedsascabcjpsddsdaedsasedsa 1 = 9
	cabcjpsdae dsasedsascabcjpsddsdaedsasedsa 1 = 10
	cabcjpsdaed sasedsascabcjpsddsdaedsasedsa 1 = 11
	cabcjpsdaeds asedsascabcjpsddsdaedsasedsa 1 = 12
	cabcjpsdaedsa sedsascabcjpsddsdaedsasedsa 1 = 13
	cabcjpsdaedsas edsascabcjpsddsdaedsasedsa 1 = 14
	cabcjpsdaedsasedsas cabcjpsddsdaedsasedsa 3 = 17 (moved 5)
	cabcjpsdaedsasedsascabcjpsd dsdaedsasedsa 3 = 20 (moved 8) -- After this move there is a good example. 
	cabcjpsdaedsasedsascabcjpsdd sdaedsasedsa 1 = 21 I can either buy a single letter (d) or copy 'ds'. If I buy 'd', then I have a single copyable sequence til the end
	cabcjpsdaedsasedsascabcjpsddsdaedsasedsa  3 = 24 COPIED TIL THE END
	*/
	EXPECT_EQ(45, buildString(2, 3, "cbacojcrojcrlidickjcjcrojcrlijcrojcrrojq"));
}

TEST(BuildString, case5) {
	EXPECT_EQ(65040, buildString(2709, 2712, "cbaasgcbiikaegcbiidcbaasgcbiikaegcbiidir"));
	EXPECT_EQ(126246, buildString(7890, 7891, "cabcjpsdaedsasedsascabcjpsddsdaedsasedsa"));
	EXPECT_EQ(268964, buildString(7078, 7078, "cbacojcrojcrlidickjcjcrojcrlijcrojcrrojq"));
}

TEST(BuildString, case6) {
	EXPECT_EQ(300, buildString(4105, 4110, "bbbblcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrblllbbosbqlltblcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrblllbbosbqlltlcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrblllbbosbqlltblcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrabbosbqllcalllbbosbqlbosbql"));
	EXPECT_EQ(300, buildString(6765, 6767, "accbaccbiaccbaccbicrnggccbinrcbaccbiaccbaccbicrnggbaccbicrnggccbiaccbaccbicrnggbarccbaccbiaccbaccbicrnggccinggccbinrcbaccbiaccbaccbicrnggbaccbicrnggccbiaccbaccbicrnggbarccbbinrcbaccbiaccbaccbicrnggbaccbicrnpsaccbaccbicrnggbaccbicrnggccbiaccbccbicrnggccbiaccbaccbicrnggbarccbbinrcbaccbiaccbaccncbicrif"));
	EXPECT_EQ(300, buildString(8987, 8990, "cbcbdbcapcdbcbehbsdkbcapccapcdcbedgscdgscdmhbsdkapccapcdapbcbdbcapcnhcdapbcbdbaedgscdgsclbaedgscdgaegcbdbaedtpbcbdbaedpcaedgscdgaehhmbeoaedtpbcdnbhhmbeocdapblbdbcbcbdbcimhbsdkapccdojbcascdgaehccdnbhhkcdgaqmbhhmbeocdkadiccipridrapcdcbedlblbdbcbcbddojbcascdgbmmhhkcdgaqmbhmbiepccapcdiinrmdcbedlrmcntbfd"));
}

