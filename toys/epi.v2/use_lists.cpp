#include <iostream>
#include <memory>
#include "List.hpp"
#include <list>
// node std:: has list (dbl linked list) and forward_list (single linked list)

using namespace std;

/*
 * Add merge of 2 sorted lists
 */

void merge_lists()
{
    int ii1[] = {9,7,5,3,1};
    int ii2[] = {16,14,10,6,2};
    shared_ptr<ListNode<int>> head1 = make_shared<ListNode<int>>();
    shared_ptr<ListNode<int>> head2 = make_shared<ListNode<int>>();
    shared_ptr<ListNode<int>> node;
    for (int i = 0; i < 5; ++i) {
        node = make_shared<ListNode<int>>();
        node->data = ii1[i];
        InsertAfter(head1, node);
        node = make_shared<ListNode<int>>();
        node->data = ii2[i];
        InsertAfter(head2, node);
    }
    ShowList(head1);
    ShowList(head2);
    shared_ptr<ListNode<int>> head3 = MergeSortedLists(head1, head2);
    ShowList(head3);
}

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
    //use_api();
    merge_lists();
    //use_stdlib();
}
