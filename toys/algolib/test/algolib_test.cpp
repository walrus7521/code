#include <gtest/gtest.h>
#include <iostream>
#include <slist.h>

using namespace std;


TEST(MyTestSuitName, MyTestCaseName) {
    //QueueTest qt;
    //int n = q1_.Dequeue();
    int actual = 1;
    EXPECT_GT(actual, 0);
    EXPECT_EQ(1, actual) << "Should be equal to one";

    int i;
    list *l = list_new();
    list *r = list_new();
    for (i = 0; i < 8; i++) {
        list_push_back(l, i);
        list_push_front(l, i+16);
    }
    list_show(l);
    r->next = reverse(l);
    list_show(r);
    while (!LIST_EMPTY(r)) {
        _link *n = list_pop_front(r);
        printf("pop: %d\n", n->value);
    }

}

#if 0
int main()
{
    cout << "sup homi" << endl;
}
#endif
