#include <gtest/gtest.h>
#include <iostream>

using namespace std;


TEST(MyTestSuitName, MyTestCaseName) {
    int actual = 1;
    EXPECT_GT(actual, 0);
    EXPECT_EQ(1, actual) << "Should be equal to one";
}

