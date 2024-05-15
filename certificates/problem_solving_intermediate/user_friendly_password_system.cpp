#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>


#include <cmath>
#include <array>
#include <numeric>
#include <string>
#include <vector>

using ::testing::ElementsAre;

namespace {
	unsigned long long pow131(auto  n) {
		constexpr std::array<unsigned long long, 8> pow131 = { 1, 131, 17161, 2248091, 294499921, 38579489651, 5053913144281, 662062621900811};
		if (n < 8)
			return pow131[n];

		return static_cast<unsigned long long>(std::pow(131, n));
		};

	int hasherFunc(auto const& value) {
		auto ret = std::transform_reduce(std::begin(value), std::end(value),
			0LL,
			std::plus<>(),
			[&, len = value.size()](char c) mutable {
				return (pow131(--len)*c) % 1000000007; 
			});

		return static_cast<int>(ret % 1000000007);
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
	EXPECT_EQ(pow131(8), 86730203469006240);
}

TEST(UserFriendlyPasswordSystem, DISABLED_hash) {
	//auto  c = hashSecret("cAr1");
	EXPECT_EQ(hashPair("c").first, 99);
	EXPECT_EQ(hashPair("cA").first, 13034); // 131*99 + 65 = 12969 + 65 = 13034
	EXPECT_EQ(hashPair("cAr").first, 1707568); // 17161*99 + 131*65 + 114 = 1699399 + 8515 + 114 = 1707568
	EXPECT_EQ(hashPair("cAr1").first, 223691457); // 2248091*99 + 17161*65 + 131*114 + 49 = 223691457
	EXPECT_EQ(hashPair("cAr1a").first, 303580761); // 294499921*99 + 2248091*65 + 17161*114 + 131*49 + 97 = 303580761
	EXPECT_EQ(hashPair("cAr1"), std::pair(223691457, 303580664));
	EXPECT_EQ(hashPair("000A").first, 108738449);
}
TEST(UserFriendlyPasswordSystem, DISABLED_example) {
	EXPECT_THAT(authEvents({
		{"setPassword", "cAr1"},
		{"authorize", "223691457"},
		{"authorize", "303580761"},
		{"authorize", "100"},
		{"setPassword", "d"},
		{ "authorize", "100" } }
	), ElementsAre(1, 1, 0, 1));
}

TEST(UserFriendlyPasswordSystem, DISABLED_sample0) {
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

TEST(UserFriendlyPasswordSystem, DISABLED_case0) {
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

TEST(UserFriendlyPasswordSystem, DISABLED_case3) {
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
