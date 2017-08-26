#include "pch.hpp"

template <typename T>
class ListNode {
public:
    T data;
    std::shared_ptr<ListNode<T>> next;
};

std::shared_ptr<ListNode<int>> SearchList(std::shared_ptr<ListNode<int>> L, int key) {
    while (L && L->data != key) {
        L = L->next;
    }
    return L;
}

void InsertAfter(const std::shared_ptr<ListNode<int>>& node,
                 const std::shared_ptr<ListNode<int>>& new_node) {
    new_node->next = node->next;
    node->next = new_node;
}

void AppendNode(std::shared_ptr<ListNode<int>> *node,
                std::shared_ptr<ListNode<int>> *tail) {
    (*tail)->next = *node;
    *tail = *node;
    *node = (*node)->next;
}

void DeleteAfter(const std::shared_ptr<ListNode<int>>& node) {
    node->next = node->next->next;
}

std::shared_ptr<ListNode<int>> MergeSortedLists(const std::shared_ptr<ListNode<int>>& list1,
                                                const std::shared_ptr<ListNode<int>>& list2) {
    std::shared_ptr<ListNode<int>> merge = std::make_shared<ListNode<int>>();
    auto tail = merge;
    std::shared_ptr<ListNode<int>> p1 = list1->next; // skip head
    std::shared_ptr<ListNode<int>> p2 = list2->next;
    while (p1 && p2) {
        if (p1->data <= p2->data) {
            AppendNode(&p1, &tail);
        } else {
            AppendNode(&p2, &tail);
        }
    }
    if (p1) {
        tail->next = p1;
    } else if (p2) {
        tail->next = p2;
    }
    return merge;
}

std::shared_ptr<ListNode<int>> ReverseList(const std::shared_ptr<ListNode<int>>& list) {
    std::shared_ptr<ListNode<int>> p;
    std::shared_ptr<ListNode<int>> q;
    std::shared_ptr<ListNode<int>> r;

    p = list->next;
    while (p) {
        p = p->next;
    }
    return r;
}

void ShowList(const std::shared_ptr<ListNode<int>>& L) {
    std::shared_ptr<ListNode<int>> p = L->next;
    while (p) {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

#include "pch.hpp"
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

