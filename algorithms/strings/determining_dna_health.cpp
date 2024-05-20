// HARD https://www.hackerrank.com/challenges/determining-dna-health/problem
// Note: This exercise is a mess. You have to manually modify main to call this function, and also redirect output to fout.

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace {



	class BasicTrie {
	public:
		std::unordered_map<char, std::unique_ptr<BasicTrie>> children;
		std::vector<std::pair<int, unsigned long>> scores;

		using iterator = std::unordered_map<char, std::unique_ptr<BasicTrie>>::iterator;
		using const_iterator = std::unordered_map<char, std::unique_ptr<BasicTrie>>::const_iterator;

		BasicTrie() noexcept = default;
		BasicTrie(std::vector<std::string> const& genes, std::vector<int> const& health) noexcept {
			for (int i = 0; i < genes.size(); ++i)
			{
				add(std::string_view(genes[i]), i, health[i]);

			}
		}
		unsigned long score(int first, int last) const noexcept {
			unsigned long score = 0;
			for (std::pair<int, unsigned long> s : scores) {
				if (s.first < first)
					continue;
				if (s.first > last) { // scores are sorted by position so no need to continue after this one
					return score;
				}
				score += s.second;

			}
			return score;
		}

		BasicTrie const* get_child(char c) const noexcept {
			auto it = children.find(c);
			if (it != children.end()) {
				return it->second.get();
			}
			return nullptr;
		}

		BasicTrie& add(char c) noexcept {
			auto iter = children.emplace(c, std::make_unique<BasicTrie>()).first;
			return *iter->second;
		}

		void add(int position, unsigned long score) noexcept {
			scores.emplace_back(position, score);
		}

		void add(std::string_view str, int position, unsigned long score) noexcept {
			if (str.empty())
			{
				add(position, score);
			}
			else
			{
				auto c = str.front();
				str.remove_prefix(1);
				add(c).add(str, position, score);
			}
		}

		unsigned long score(std::string_view const& dna, int first, int last) const {
			unsigned long value = 0;
			for (size_t i = 0; i < dna.size(); ++i) {
				BasicTrie const* node = this;
				for (auto j = i; j < dna.size(); ++j) {
					node = node->get_child(dna[j]);
					if (node == nullptr) {
						break;
					}
					value += node->score(first, last);

				}
			}
			return value;
		}


		std::pair<unsigned long, unsigned long> score(std::vector<std::vector<std::string>> queries)
		{
			std::pair<unsigned long, unsigned long> scores{ ULONG_MAX, 0 };

			for (auto const& q : queries)
			{
				int first = stoi(q[0]);
				int last = stoi(q[1]);
				std::string_view query = q[2];
				auto value = score(query, first, last);
				scores.first = std::min(scores.first, value);
				scores.second = std::max(scores.second, value);

			}

			return scores;
		}
	};
}

TEST(DeterminingDnaHealth, example) {
	EXPECT_EQ(std::pair(0UL, 19UL), BasicTrie({ "a", "b", "c", "aa", "d", "b" }, { 1, 2, 3, 4, 5, 6 }).score({ {"1", "5", "caaab"}, {"0", "4", "xyz"}, {"2", "4", "bcdybc"} }));

}

TEST(DeterminingDnaHealth, sample0) {
	EXPECT_EQ(std::pair(0UL, 19UL), BasicTrie({ "a", "b", "c", "aa", "d", "b" }, { 1, 2, 3, 4, 5, 6 }).score({ {"1", "5", "caaab"}, {"0", "4", "xyz"}, {"2", "4", "bcdybc"} }));

}

