#include <gtest/gtest.h>
#include <iostream>
#include <slist.h>

using namespace std;

TEST(ListTest, ListAllocation) {
    list *l = NULL;
    list *r = NULL;
    ASSERT_TRUE((l = list_new()) != NULL) << "List should be non-NULL";
    ASSERT_TRUE((r = list_new()) != NULL) << "List should be non-NULL";
    for (int i = 0; i < 8; i++) {
        list_push_back(l, i);
        list_push_front(l, i+16);
    }
    ASSERT_TRUE((r->next = reverse(l)) != NULL) << "reverse should return non-NULL";
    while (!LIST_EMPTY(r)) {
        _link *n = list_pop_front(r);
        printf("pop: %d\n", n->value);
    }
    ASSERT_TRUE(l != NULL);

}

TEST(ListTest, ListAdd) {
    int actual = 1;
    EXPECT_GT(actual, 0);
    EXPECT_EQ(1, actual) << "Should be equal to one";
}

TEST(HashTest, HashAllocation) {
    int actual = 1;
    EXPECT_GT(actual, 0);
    EXPECT_EQ(1, actual) << "Should be equal to one";
}

TEST(TreeTest, TreeAllocation) {
    int actual = 1;
    EXPECT_GT(actual, 0);
    EXPECT_EQ(3, actual) << "Should be equal to one";
}

#if 0
int main()
{
    cout << "sup homi" << endl;
}
#endif
