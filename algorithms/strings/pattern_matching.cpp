#include <gtest/gtest.h>

#include <string>
#include <utility>

int match(std::string A, std::string B) {

    using const_iterator = std::string::const_iterator;

    auto iterA = std::make_pair(A.begin(), A.end()); // pair for traverse and end of A
	auto iterB = std::make_pair(B.begin(), B.end()); // pair for traverse and end of B
	auto wildcardIter = std::make_pair(B.end(), B.end()); // pair for the start of the wildcard and the end of the wildcard


	iterB.first = std::find(iterB.first, iterB.second, '*');
    std::advance(iterA.first, std::distance(B.begin(), iterB.first)); // Let's just move to the first wildcard.

    while (iterA.first != iterA.second) { // While I am not done with A
        // First let's loop while I am not done with B
        if (iterB.first != iterB.second && *iterB.first == *iterA.first) { //If the chars match
            ++iterA.first;
            ++iterB.first;
        }
        else if (iterB.first != iterB.second && *iterB.first == '*') { // Ok, wildcard coming
            // I will move the iterator, and mark the start for the next processing...
            wildcardIter = make_pair(iterA.first, iterB.first);
            ++iterB.first;
        }
        else if (wildcardIter.second != iterB.second) { 
            iterB.first = wildcardIter.second + 1;
            iterA.first = ++wildcardIter.first;
        }
        else {
            return false; // Ok, something is going on. Out.
        }
    }

    iterB.first = std::find_if(iterB.first, iterB.second, [](char ch) { return ch != '*'; });

    return iterB.first == std::end(B);
}


TEST(patternMatching, example)
{
	EXPECT_EQ(match("abracadabra", "ab*c*d*abra"), 1);
    EXPECT_EQ(match("abradacabra", "ab*c*d*abra"), 0);
}

TEST(patternMatching, case0)
{
    EXPECT_EQ(match("abracadabra", "ab*c*d*abra"), 1);
    
}

TEST(patternMatching, case1)
{
    EXPECT_EQ(match("abradacabra", "ab*c*d*abra"), 0);
}