// EASY https://www.hackerrank.com/challenges/grading/problem

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <vector>

using ::testing::ElementsAre;

namespace {
    std::vector<int> gradingStudents(std::vector<int> grades) {
        for (auto& x : grades)
        {
            if (x < 38)
                continue;
            int nextMultiple = 5 - (x % 5) + x;
            if ((nextMultiple - x) < 3)
                x = nextMultiple;
        }
        return grades;
    }
}

TEST(GradingStudents, example)
{
    EXPECT_THAT(gradingStudents({ 84, 29, 57}), ElementsAre(85, 29, 57));
}

TEST(GradingStudents, sample0)
{
    EXPECT_THAT(gradingStudents({ 73, 67, 38, 33 }), ElementsAre(75, 67, 40, 33));
}

TEST(GradingStudents, case0)
{
    EXPECT_THAT(gradingStudents({ 73, 67, 38, 33 }), ElementsAre(75, 67, 40, 33));
}