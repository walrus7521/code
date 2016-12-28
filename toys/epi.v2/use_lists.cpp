#include <iostream>
#include <memory>
#include "List.hpp"
#include <list>
// node std:: has list (dbl linked list) and forward_list (single linked list)

using namespace std;

/*
 * Add merge of 2 lists
 */

void use_api()
{
    shared_ptr<ListNode<int>> head = make_shared<ListNode<int>>();
    head->data = 42;
    shared_ptr<ListNode<int>> node;
    for (int i = 0; i < 8; ++i) {
        node = make_shared<ListNode<int>>();
        node->data = i;
        InsertAfter(head, node);
    }
    ShowList(head);
    DeleteAfter(head);
    ShowList(head);
}

/*
 *  To know:
 *
 *  list & forward_list
 *  push_front/back
 *  emplace_front/back
 *  splice, reverse, sort
 *  splice_after, erase_after
 *
 */
void use_stdlib()
{
    list<int> head;
    for (int i = 0; i < 8; ++i) {
        head.push_back(i);
    }
    for (auto &li : head) {
        cout << li << endl;
    }
}

int main()
{
    use_api();
    //use_stdlib();
}
