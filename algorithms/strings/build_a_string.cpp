// HARD https://www.hackerrank.com/challenges/build-a-string/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


namespace {

	class SuffixAutomaton {
	public:
		struct State {
			char m_character;
			std::unordered_map<char, int> m_edges;
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
		State & operator[](size_t i) { return m_states[i]; }
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

	int buildString(int a, int b, std::string const& s) {
		
		SuffixAutomaton sa;
		std::vector<int> dp(s.size() + 1, std::numeric_limits<int>::max());
		dp[0] = 0;
		for (int i = 0; i < s.length(); ++i) {
			int j = i;
			int v = 0;

			while (j < s.size() && sa[v].m_edges.count(s[j])) {
				v = sa[v].m_edges[s[j]];
				++j;
			}
			
			dp[j] = std::min(dp[j], dp[i] + b);
			dp[i + 1] = std::min(dp[i + 1], dp[i] + a);
			sa.append(s[i]);
		}
		return dp[s.length()];
		//return StringBuilder(a, b, s).cost();
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
	cabcjpsdaedsasedsascabcjpsdd sdaedsasedsa 1 = 21 I buy a single letter (d). If I buy 'd', then I have a single copyable sequence til the end
	cabcjpsdaedsasedsascabcjpsddsdaedsasedsa  3 = 24 COPIED TIL THE END
	*/
	EXPECT_EQ(45, buildString(2, 3, "cbacojcrojcrlidickjcjcrojcrlijcrojcrrojq"));
}

TEST(BuildString, case5) {
	EXPECT_EQ(65040, buildString(2709, 2712, "caackncaacknggikncaacknggaacknggikncaackggikncaacknggaacknggikncakqoaacknggikncacggihikncaomhikncaom"));
	EXPECT_EQ(126246, buildString(7890, 7891, "acbcrsjcrscrsjcrcbcrsjcrscrsjccbcrsjcrscrsjcrcbcrsjrscrsjcrcbcrsjcrscrsjccbcrsjcrscrsjcrcbcsbcbcrsjh"));
	EXPECT_EQ(268964, buildString(7078, 7078, "abbciabbcabciabbcmabbciabbcahlbchgcmabbcmggcmababciabbcagerafrciabbcsrhgcmcabciabbchgcmabbcmsfabcmsr"));
}

TEST(BuildString, case6) {
	EXPECT_EQ(110890, buildString(4105, 4110, "bbbblcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrblllbbosbqlltblcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrblllbbosbqlltlcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrblllbbosbqlltblcmrblllbbosbqllcalllbbosbqllcalllbbosbqlbosbqllcallblcmrabbosbqllcalllbbosbqlbosbql"));
	EXPECT_EQ(209739, buildString(6765, 6767, "accbaccbiaccbaccbicrnggccbinrcbaccbiaccbaccbicrnggbaccbicrnggccbiaccbaccbicrnggbarccbaccbiaccbaccbicrnggccinggccbinrcbaccbiaccbaccbicrnggbaccbicrnggccbiaccbaccbicrnggbarccbbinrcbaccbiaccbaccbicrnggbaccbicrnpsaccbaccbicrnggbaccbicrnggccbiaccbccbicrnggccbiaccbaccbicrnggbarccbbinrcbaccbiaccbaccncbicrif"));
	EXPECT_EQ(943764, buildString(8987, 8990, "cbcbdbcapcdbcbehbsdkbcapccapcdcbedgscdgscdmhbsdkapccapcdapbcbdbcapcnhcdapbcbdbaedgscdgsclbaedgscdgaegcbdbaedtpbcbdbaedpcaedgscdgaehhmbeoaedtpbcdnbhhmbeocdapblbdbcbcbdbcimhbsdkapccdojbcascdgaehccdnbhhkcdgaqmbhhmbeocdkadiccipridrapcdcbedlblbdbcbcbddojbcascdgbmmhhkcdgaqmbhmbiepccapcdiinrmdcbedlrmcntbfd"));
}

