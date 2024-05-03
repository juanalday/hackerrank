//https://www.hackerrank.com/challenges/countingsort4/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace {
	namespace {
		std::string sortData(std::vector<std::vector<std::string>> arr) {
			std::multimap<int, std::string> counter;
			for_each(arr.begin(), next(arr.begin(), arr.size() / 2), [](auto& data) {data.back() = "-"; });
			for_each(arr.begin(), arr.end(), [&counter](auto& pairVec) {counter.insert({ std::stoi(pairVec.front()), std::move(pairVec.back()) });});
			std::ostringstream buffer;
			for_each(counter.begin(), prev(counter.end()), [&buffer](auto const& pair) {buffer << pair.second << ' '; });
			buffer << prev(counter.end())->second;
			return buffer.str();
		}

		void countSort(std::vector<std::vector<std::string>> const& arr) {
			std::cout << sortData(arr) << std::endl;
		}
	}
}


TEST(fullCountingSort, example)
{
	EXPECT_EQ("- c - d", sortData({ {"0", "a"}, {"1", "b"}, {"0", "c"}, {"1", "d"} }));
}

TEST(fullCountingSort, sample_case0)
{
	EXPECT_EQ("- - - - - to be or not to be - that is the question - - - -",
		sortData({ {"0", "ab"},{"6", "cd"},{"0", "ef"},{"6", "gh"},{"4", "ij"},{"0", "ab"},{"6", "cd"},{"0", "ef"},{"6", "gh"},{"0", "ij"},{"4", "that"},{"3", "be"},{"0", "to"},{"1", "be"},{"5", "question"},{"1", "or"},{"2", "not"},{"4", "is"},{"2", "to"},{"4", "the"} }));
}

TEST(fullCountingSort, sample_case1)
{
	EXPECT_EQ("- - f e b c - a - -",
		sortData({{"1", "e"}, {"2", "a"},{"1", "b"},{"3", "a"},{"4", "f"},{"1", "f"},{"2", "a"},{"1", "e"},{"1", "b"},	{"1", "c"} }));
}

TEST(fullCountingSort, case0)
{
	EXPECT_EQ("- - - - - to be or not to be - that is the question - - - -",
		sortData({ {"0", "ab"},{"6", "cd"},{"0", "ef"},{"6", "gh"},{"4", "ij"},{"0", "ab"},{"6", "cd"},{"0", "ef"},{"6", "gh"},{"0", "ij"},{"4", "that"},{"3", "be"},{"0", "to"},{"1", "be"},{"5", "question"},{"1", "or"},{"2", "not"},{"4", "is"},{"2", "to"},{"4", "the"} }));
}

TEST(fullCountingSort, case6)
{
	EXPECT_EQ("- - f e b c - a - -",
		sortData({ {"1", "e"}, {"2", "a"},{"1", "b"},{"3", "a"},{"4", "f"},{"1", "f"},{"2", "a"},{"1", "e"},{"1", "b"},	{"1", "c"} }));
}