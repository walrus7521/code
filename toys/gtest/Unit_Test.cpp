#include <gtest/gtest.h>
#include "Queue.hpp"

class QueueTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q3_.Enqueue(3);
    }

    // virtual void TearDown() {}

    Queue<int> q1_;
    Queue<int> q2_;
    Queue<int> q3_;
};

TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_EQ(0, q1_.size());
}

TEST_F(QueueTest, DequeueWorks) {
    int n = q1_.Dequeue();
    EXPECT(-1, n);

    //n = q2_.Dequeue();
    //ASSERT_TRUE();
}


TEST(MyTestSuitName, MyTestCaseName) {
    int actual = 1;
    EXPECT_GT(actual, 0);
    EXPECT_EQ(1, actual) << "Should be equal to one";
}

TEST_F(MyTestFixtureName, MyTestName) {
}
