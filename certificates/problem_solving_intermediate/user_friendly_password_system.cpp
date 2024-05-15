#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <cmath>
#include <array>
#include <numeric>
#include <string>
#include <vector>

using ::testing::ElementsAre;

namespace {
	constexpr std::array<double, 9> const powersOf131 = {
		1,                     // 131^0
		131,                   // 131^1
		17161,                 // 131^2
		2248091,               // 131^3
		294499921,             // 131^4
		38579489651,           // 131^5
		5053913144281,         // 131^6
		662062621900811,       // 131^7
	};
	constexpr double pow131(auto n) {
		if (n < 8)
			return powersOf131[n];
		return std::pow(131, n);
	};

	constexpr unsigned long long stagedPow131(char c, auto pos) {
		return static_cast<unsigned long long>(pow131(pos) * c);
	}

	unsigned long long plainHasherFunc(std::string const& value) {
		auto len = value.size();
		unsigned long long ret(0);
		for (auto x : value)
		{
			--len;
			ret += stagedPow131(x, len);
		}
		return ret;
	}

	int hasherFunc(std::string const& value) {
		return static_cast<int>(plainHasherFunc(value) % 1000000007);
	}

	std::pair<int, int> hashPair(std::string str) {
		return { hasherFunc(str), hasherFunc(str + " ") - 32 };
	}

	std::vector<int> authEvents(std::vector<std::vector<std::string>> events) {
		
		std::pair<int, int> passwordHash = { 0, 0 };

		std::vector<int> ret;
		for (auto const& x : events) {
			if (x[0] == "setPassword") {
				passwordHash = hashPair(x[1]);
			}
			else if (x[0] == "authorize") {
				auto hash = std::stoi(x[1]);
				auto h1 = passwordHash.first;
				auto h2 = passwordHash.second;
				auto h3 = hash - passwordHash.second;
				if (hash == passwordHash.first)
					ret.push_back(1);
				else if (std::abs(hash - passwordHash.second) < 127) {
					ret.push_back(1);
				}
				else {
					ret.push_back(0);
				}
			}
		}
		return ret;
	}
}

TEST(UserFriendlyPasswordSystem, pow131)
{
	EXPECT_EQ(pow131(0), 1);
	EXPECT_EQ(pow131(1), 131);
	EXPECT_EQ(pow131(2), 17161);
	EXPECT_EQ(pow131(3), 2248091);
	EXPECT_EQ(pow131(4), 294499921);
	EXPECT_EQ(pow131(5), 38579489651);
	EXPECT_EQ(pow131(6), 5053913144281);
	EXPECT_EQ(pow131(7), 662062621900811);
	EXPECT_EQ(pow131(8), 86730203469006241);
};

TEST(UserFriendlyPasswordSystem, stagedPow131)
{
	EXPECT_EQ(stagedPow131('c', 0), 99);
	EXPECT_EQ(stagedPow131('c', 1), 12969);
	EXPECT_EQ(stagedPow131('c', 2), 1698939);
	EXPECT_EQ(stagedPow131('c', 3), 222561009);
	EXPECT_EQ(stagedPow131('c', 4), 29155492179);
	EXPECT_EQ(stagedPow131('c', 5), 3819369475449);
	EXPECT_EQ(stagedPow131('c', 6), 500337401283819);
	EXPECT_EQ(stagedPow131('c', 7), 65544199568180288);
	EXPECT_EQ(stagedPow131('c', 8), 8586290143431617536);
	EXPECT_EQ(stagedPow131('A', 0), 65);
	EXPECT_EQ(stagedPow131('A', 1), 8515);
	EXPECT_EQ(stagedPow131('A', 2), 1115465);
	EXPECT_EQ(stagedPow131('A', 3), 146125915);
	EXPECT_EQ(stagedPow131('A', 4), 19142494865);
	EXPECT_EQ(stagedPow131('r', 0), 114);
	EXPECT_EQ(stagedPow131('r', 1), 14934);
	EXPECT_EQ(stagedPow131('r', 2), 1956354);
	EXPECT_EQ(stagedPow131('r', 3), 256282374);
	EXPECT_EQ(stagedPow131('r', 4), 33572990994);
	EXPECT_EQ(stagedPow131('1', 0), 49);
	EXPECT_EQ(stagedPow131('1', 1), 6419);
	EXPECT_EQ(stagedPow131('1', 2), 840889);
	EXPECT_EQ(stagedPow131('1', 3), 110156459);
	EXPECT_EQ(stagedPow131('1', 4), 14430496129);
}

TEST(UserFriendlyPasswordSystem, plainHasherFunc) {
	EXPECT_EQ(plainHasherFunc("c"), 99);
	EXPECT_EQ(plainHasherFunc("cA"), 13034); // 131*99 + 65 = 12969 + 65 = 13034
	EXPECT_EQ(plainHasherFunc("cAr"), 1707568); // 17161*99 + 131*65 + 114 = 1699399 + 8515 + 114 = 1707568
	EXPECT_EQ(plainHasherFunc("cAr1"), 223691457); // 2248091*99 + 17161*65 + 131*114 + 49 = 223691457
}

TEST(UserFriendlyPasswordSystem, hash) {
	EXPECT_EQ(hashPair("c").first, 99);
	EXPECT_EQ(hashPair("cA").first, 13034); // 131*99 + 65 = 12969 + 65 = 13034
	EXPECT_EQ(hashPair("cAr").first, 1707568); // 17161*99 + 131*65 + 114 = 1699399 + 8515 + 114 = 1707568
	EXPECT_EQ(hasherFunc("cAr1"), 223691457); // 2248091*99 + 17161*65 + 131*114 + 49 = 223691457
	EXPECT_EQ(hashPair("cAr1").first, 223691457); // 2248091*99 + 17161*65 + 131*114 + 49 = 223691457
	EXPECT_EQ(hashPair("cAr1a").first, 303580761); // 294499921*99 + 2248091*65 + 17161*114 + 131*49 + 97 = 303580761
	EXPECT_EQ(hashPair("cAr1"), std::pair(223691457, 303580664));
	EXPECT_EQ(hashPair("000A").first, 108738449);
}

TEST(UserFriendlyPasswordSystem, example) {
	EXPECT_THAT(authEvents({
		{"setPassword", "cAr1"},
		{"authorize", "223691457"},
		{"authorize", "303580761"},
		{"authorize", "100"},
		{"setPassword", "d"},
		{ "authorize", "100" } }
	), ElementsAre(1, 1, 0, 1));
}

TEST(UserFriendlyPasswordSystem, sample0) {
	EXPECT_THAT(authEvents({
		{"setPassword", "000A"},
		{"authorize", "108738450"},
		{"authorize", "108738449"},
		{ "authorize", "244736787" } }
	),ElementsAre(0, 1, 1));
}

TEST(UserFriendlyPasswordSystem, sample1) {
	EXPECT_THAT(authEvents({
		{"setPassword", "1"},
		{"setPassword", "2"},
		{"setPassword", "3"},
		{"authorize", "49"},
		{ "authorize", "50" } }
	),ElementsAre(0, 0));
}

TEST(UserFriendlyPasswordSystem, case0) {
	EXPECT_THAT(authEvents({
		{"setPassword", "000A"},
		{"authorize", "108738450"},
		{"authorize", "108738449"},
		{ "authorize", "244736787" } }
	), ElementsAre(0, 1, 1));
}

TEST(UserFriendlyPasswordSystem, case1) {
	EXPECT_THAT(authEvents({
		{"setPassword", "1"},
		{"setPassword", "2"},
		{"setPassword", "3"},
		{"authorize", "49"},
		{ "authorize", "50" } }
	), ElementsAre(0, 0));
}

TEST(UserFriendlyPasswordSystem, case2) {
	EXPECT_THAT(authEvents({
		{"setPassword", "a"},
		{"authorize", "97"},
		{"authorize", "12756"},
		{"authorize", "12804"},
		{"authorize", "12829"},
		{"authorize", "12772"},
		{"authorize", "12797"},
		{"authorize", "98"} }
	), ElementsAre(1, 1, 1, 1, 1, 1, 0));
}

TEST(UserFriendlyPasswordSystem, case3) {
	EXPECT_THAT(authEvents({
		{"setPassword", "brnTP3"},
		{"setPassword", "bnFb"},
		{"setPassword", "HnKYaX" },
		{"authorize", "776923238" },
		{"setPassword", "f" },
		{"authorize", "84" },
		{"setPassword", "eog" },
		{"setPassword", "wwmq6O" },
		{"authorize", "251714951" },
		{"setPassword", "NIQ0Wobtq"}
		}), ElementsAre(1, 0, 1));
}
TEST(UserFriendlyPasswordSystem, case4) {
	EXPECT_THAT(authEvents({
		{"setPassword", "62"},
		{"setPassword", "y4CqpI" },
		{"setPassword", "3yn9Ff" },
		{"setPassword", "M" },
		{"authorize",   "77" },
		{"authorize",   "455618105" },
		{"authorize",   "77" },
		{"authorize",   "782787455" },
		{"authorize",   "102" },
		{"setPassword", "AnHTmt9O" }
		}), ElementsAre(1, 0, 1, 0, 0));
	
}
