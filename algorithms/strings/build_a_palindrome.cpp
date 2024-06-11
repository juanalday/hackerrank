// Advanced https://www.hackerrank.com/challenges/challenging-palindromes/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>

namespace {
	class SuffixAutomaton {
	public:
		struct State {
			char m_character;
			std::map<char, int> m_edges;
			int m_length, m_link;
			int m_size;
			bool m_final;
		};

		SuffixAutomaton() : m_last(0)
		{
			m_states.emplace_back();
			State& state = m_states.back();
			state.m_link = -1;
			state.m_length = 0;
			state.m_size = 1;
			state.m_final = false;
			state.m_character = '$';

		}
		SuffixAutomaton(const std::string& s) : SuffixAutomaton() {
			for (auto c : s)
				append(c);

			finalize();
		}

		SuffixAutomaton& finalize() {
			for (int i = m_last; i != -1; i = m_states[i].m_link)
				m_states[i].m_final = true;

			std::vector<std::vector<int>> statesPerLen(1 + maxLen());
			for (int i = 0; i < static_cast<int>(m_states.size()); ++i)
				statesPerLen[m_states[i].m_length].push_back(i);

			for (auto it = statesPerLen.rbegin(); it != statesPerLen.rend(); ++it)
				for (auto ind : *it)
					if (m_states[ind].m_link != -1)
						m_states[m_states[ind].m_link].m_size += m_states[ind].m_size;
			return *this;
		}

		int traverse(const std::string& s, int stateIndex = 0) const {
			for (auto c : s)
				stateIndex = traverse(c, stateIndex);
			return stateIndex;
		}

		int traverse(char c, int stateIndex) const {
			if (stateIndex == -1)
				return -1;
			auto itNext = m_states[stateIndex].m_edges.find(c);
			if (itNext != end(m_states[stateIndex].m_edges))
				return itNext->second;

			return -1;
		}

		int size(int index) const { return m_states[index].m_size; }

		bool isFinal(int index) const { return index != -1 && m_states[index].m_final; }

		std::vector<State> const& states() const noexcept { return m_states; }

		bool contains(const std::string& s) const { return traverse(s) != -1; }
		bool isSuffix(const std::string& s) const { return isFinal(traverse(s)); }

		bool empty() const noexcept { return m_states.size() < 2; }
		size_t size() const noexcept { return m_states.size(); }
		State const& operator[](size_t i) const { return m_states[i]; }
		State& operator[](size_t i) { return m_states[i]; }
		int count(std::string const& s) const { return size(traverse(s)); }
		int maxLen() const noexcept { return std::max_element(m_states.begin(), m_states.end(), [](State const& lhs, State const& rhs) {return lhs.m_length < rhs.m_length; })->m_length; }

		SuffixAutomaton& append(char c) {
			// We add new state corresponding to s + c
			// It will has index curr.
			m_states.emplace_back();
			int curr = static_cast<int>(m_states.size() - 1);
			{
				State& state = m_states.back();
				state.m_length = m_states[m_last].m_length + 1;
				state.m_link = -2;
				state.m_size = 1;
				state.m_final = false;
				state.m_character = c;
			}

			int p = m_last;
			while (p != -1 && m_states[p].m_edges.count(c) == 0) {
				m_states[p].m_edges[c] = curr;
				p = m_states[p].m_link;
			}
			if (p == -1)
				m_states[curr].m_link = 0;
			else {
				int q = m_states[p].m_edges.at(c);
				if (m_states[p].m_length + 1 == m_states[q].m_length)  // (p, q) is solid edge
					m_states[curr].m_link = q;
				else {
					int clone = static_cast<int>(m_states.size());     // (p, q) is not solid,
					m_states.push_back(m_states[q]);  // we do a split q ---> clone, q
					m_states[clone].m_length = m_states[p].m_length + 1;
					m_states[clone].m_size = 0;
					m_states[curr].m_link = clone;
					m_states[q].m_link = clone;
					for (; p != -1; p = m_states[p].m_link) {
						auto it = m_states[p].m_edges.find(c);
						if (it != end(m_states[p].m_edges) && it->second == q)
							it->second = clone;
						else
							break;
					}
				}
			}

			assert(m_states[curr].m_link != -2);
			m_last = curr;
			return *this;
		}

		std::vector<State> m_states;
		int m_last;
	};

	int findPalindromeEnd(std::string const& s, int start) {
		if (s.empty() || start >= s.size()) {
			return 0; // Handle edge cases
		}

		auto leftIter = next(s.begin(), start);
		auto rightIter = s.end() - 1;
		auto begin = leftIter; // Keep track of the start of the palindrome
		auto end = rightIter;

		// Move rightIter to find the farthest matching palindrome
		while (leftIter <= rightIter) {
			if (*leftIter == *rightIter) {
				// Move both iterators inward
				++leftIter;
				--rightIter;
			}
			else {
				// If characters do not match, reset leftIter and move rightIter inward
				leftIter = begin;
				--rightIter;
				end = rightIter;
			}
		}

		return std::distance(begin, end) + 1;
	}


	std::string findPalindrome(std::string const& a, std::string const& b) {
		SuffixAutomaton sa(a);
		std::string rev(b);
		std::reverse(rev.begin(), rev.end());
		std::string longest_palindrome;
		int v = 0, l = 0, best_len = 0, best_pos = 0, i{ 0 };

		std::map<int, std::pair<int, int>> bestLenAtPos;
		std::vector<std::string> bestCandidates;

		for (auto it = rev.begin(); it != rev.end(); ++it) {
			auto c = *it;
			auto i = static_cast<int>(distance(rev.begin(), it));
			while (v && !sa[v].m_edges.count(c)) { // as long as I can't follow, I go back
				v = sa[v].m_link;
				l = sa[v].m_length;
			}

			if (sa[v].m_edges.count(c)) {
				v = sa[v].m_edges[c];
				++l;
			}
			else {
				v = 0;
				l = 0;
			}
			if (l > 0) {
				bestLenAtPos[i - l + 1] = { l, 0 };
			}
		}

		int maxLen(0);
		for (auto& posEntry : bestLenAtPos) {
			auto pos = posEntry.first;
			auto& lengthPair = posEntry.second;
			l = lengthPair.first;
			lengthPair.second = findPalindromeEnd(rev, pos + l);
			maxLen = std::max(maxLen, 2*l + lengthPair.second);
		}


		// Again, removing the ones we don't need
		for (auto it = bestLenAtPos.begin(); it != bestLenAtPos.end(); ) {
			auto const& lengthPair = it->second;
			
			if ((2*lengthPair.first + lengthPair.second) < maxLen) {
				it = bestLenAtPos.erase(it);
			}
			else {
				++it;
			}
		}
		
		for (auto const& posEntry : bestLenAtPos) {
			auto pos = posEntry.first;
			auto const& lengthPair = posEntry.second;
			l = lengthPair.first;
			std::string result(2*l + lengthPair.second, ' ');
			auto subStrBegin = next(rev.begin(), pos);
			auto subStrEnd = next(subStrBegin, lengthPair.first);

			auto next = copy(subStrBegin, subStrEnd, result.begin());
			// This will not do anything if there is no extra palindrome to append
			next = std::copy(subStrEnd, std::next(subStrEnd, lengthPair.second), next);
			copy(subStrBegin, subStrEnd, next); // This copies the palindrome section from 'a', we have to reverse it
			std::reverse(next, result.end());
			bestCandidates.emplace_back(std::move(result));
		}

		std::sort(bestCandidates.begin(), bestCandidates.end());

		if (bestCandidates.empty())
			return "-1";
		return bestCandidates.front();
	}

	std::string buildPalindrome(std::string a, std::string b) {
		auto str1 = findPalindrome(a, b);
		std::reverse(begin(a), end(a));
		std::reverse(begin(b), end(b));
		auto str2 = findPalindrome(b, a);

		if (str1 == "-1" && str2 == "-1")
			return "-1";

		if (str1 == "-1")
			str1.clear();
		if (str2 == "-1")
			str2.clear();

		if (str1.size() > str2.size())
			return str1;
		if (str1.size() < str2.size())
			return str2;

		return str1 < str2 ? str1 : str2;

	}

}	

TEST(BuildPalindrome, algo) {
	EXPECT_EQ("folpcfblpncetyhtrwxkbosccskxbuvcrosavnpxzoeoyyghbbqkflslfkqbbhgyyoeozxpnvasorcvubxksccsobkxwrthytecnplbfcplof", buildPalindrome("kfnfolpcfblpncetyhtrwxkbosccskxbuvcrosavnpxzoeoyyghbbqkflslfkqbbhgyyjj", "qrxpxnloeozxpnvasorcvubxksccsobkxwrthytecnplbfcplofx"));
	EXPECT_EQ("ablilba", buildPalindrome("ab", "blilbaz"));
	EXPECT_EQ("ablilba", buildPalindrome("ablil", "bbaz"));
	EXPECT_EQ("aba", buildPalindrome("ab", "abz"));
	EXPECT_EQ("aba", buildPalindrome("ab", "a"));
}

TEST(BuildPalindrome, example) {
	EXPECT_EQ("aba", buildPalindrome("bac", "bac"));
	EXPECT_EQ("-1", buildPalindrome("abc", "def"));
	EXPECT_EQ("dfhfd", buildPalindrome("jdfh", "fds"));
}

TEST(BuildPalindrome, sample0) {
	EXPECT_EQ("aba", buildPalindrome("bac", "bac"));
	EXPECT_EQ("-1", buildPalindrome("abc", "def"));
	EXPECT_EQ("dfhfd", buildPalindrome("jdfh", "fds"));
}

TEST(BuildPalindrome, case1)
{
	EXPECT_EQ("-1", buildPalindrome("ottloictodtdtloloollllyocidyiodttoacoctcdcidcdttyoiilocltacdlydaailaiylcttilld", "jevgfsuujwrunvgvgwpfbknkruvwzgxxgksmexqvxbghfffseuugxkwexhzfbpu"));
	EXPECT_EQ("oozlzoo", buildPalindrome("qquhuwqhdswxxrxuzzfhkplwunfagppcoildagktgdarveusjuqfistulgbglwmfgzrnyxryetwzhlnfewczmnoozlqatugmd", "jwgzcfabbkoxyjxkatjmpprswkdkobdagwdwxsufeesrvncbszcepigpbzuzoootorzfskcwbqorvw"));
	EXPECT_EQ("lxsysxl", buildPalindrome("dczatfarqdkelalxzxillkfdvpfpxabqlngdscrentzamztvvcvrtcm", "bqlizijdwtuyfrxolsysxlfebpolcmqsppmrfkyunydtmwbexsngxhwvroandfqjamzkpttslildlrkjoyrpxugiceahgiakev"));
	EXPECT_EQ("folpcfblpncetyhtrwxkbosccskxbuvcrosavnpxzoeoyyghbbqkflslfkqbbhgyyoeozxpnvasorcvubxksccsobkxwrthytecnplbfcplof", buildPalindrome("kfnfolpcfblpncetyhtrwxkbosccskxbuvcrosavnpxzoeoyyghbbqkflslfkqbbhgyyjj", "qrxpxnloeozxpnvasorcvubxksccsobkxwrthytecnplbfcplofx"));
	EXPECT_EQ("rvngnvr", buildPalindrome("mlfcpidlqrvngnvttaifcbopnwezesomkxhaiafmvkbjaisyr", "btultpnxbcrmornqumatserhieqggrivouwfnbnghdfall"));
	EXPECT_EQ("bkkb", buildPalindrome("pb", "kkb"));
	EXPECT_EQ("-1", buildPalindrome("rfq", "xzj"));
	EXPECT_EQ("zlz", buildPalindrome("zlc", "zdw"));
	EXPECT_EQ("-1", buildPalindrome("s", "k"));
	EXPECT_EQ("-1", buildPalindrome("w", "d"));
}