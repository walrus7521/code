#include <gtest/gtest.h>
#include <iostream>
//#include <slist.h>

using namespace std;


TEST(MyTestSuitName, MyTestCaseName) {
    //QueueTest qt;
    //int n = q1_.Dequeue();
    int actual = 1;
    EXPECT_GT(actual, 0);
    EXPECT_EQ(1, actual) << "Should be equal to one";
}

#if 0
int main()
{
    cout << "sup homi" << endl;
}
#endif
