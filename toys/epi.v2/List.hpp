#include <iostream>
#include <memory>

// http://codereview.stackexchange.com/questions/33136/singly-linked-list-with-smart-pointers

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

void DeleteAfter(const std::shared_ptr<ListNode<int>>& node) {
    node->next = node->next->next;
}

void ShowList(const std::shared_ptr<ListNode<int>>& L) {
    std::shared_ptr<ListNode<int>> p = L;
    while (p) {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}
