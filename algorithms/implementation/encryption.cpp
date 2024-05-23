// MEDIUM https://www.hackerrank.com/challenges/encryption/problem

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <string>

namespace {
    std::string encryption(std::string s) {

        s.erase(std::remove(begin(s), end(s), ' '), std::end(s));
        auto sqrtLength = sqrt(s.size());
        auto cols = static_cast<size_t>(ceil(sqrtLength));

        std::string cipherText;
        cipherText.reserve(s.size() + cols);
        for (size_t col = 0; col < cols; ++col) {
            for (auto idx = col; idx < s.size();idx += cols) {
                cipherText += s.at(idx);
            }
            cipherText += ' ';
        }
        return cipherText.erase(cipherText.size() - 1);
    }
}

TEST(Encryption, example) {
	EXPECT_EQ("imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau", encryption("if man was meant to stay on the ground god would have given us roots"));
}

TEST(Encryption, sample0) {
	EXPECT_EQ("hae and via ecy", encryption("haveaniceday"));
}


TEST(Encryption, sample1) {
	EXPECT_EQ("fto ehg ee dd", encryption("feedthedog"));
}

TEST(Encryption, sample2) {
	EXPECT_EQ("clu hlt io", encryption("chillout"));
}

TEST(Encryption, case0) {
    EXPECT_EQ("hae and via ecy", encryption("haveaniceday"));
}


TEST(Encryption, case1) {
    EXPECT_EQ("fto ehg ee dd", encryption("feedthedog"));
}

TEST(Encryption, case2) {
    EXPECT_EQ("clu hlt io", encryption("chillout"));
}