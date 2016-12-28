#include <iostream>
#include <memory>
#include "List.hpp"
#include <list>
// node std:: has list (dbl linked list) and forward_list (single linked list)

using namespace std;

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
