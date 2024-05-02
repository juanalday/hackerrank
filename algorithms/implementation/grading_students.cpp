#include <gtest/gtest.h>

#include <vector>
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

TEST(gradingStudents, sample0)
{
    std::vector input{73, 67, 38, 33};
    std::vector output{ 75, 67, 40, 33 };
    
    EXPECT_EQ(gradingStudents(input), output);
}