#include <iostream>
#include <memory>

// http://codereview.stackexchange.com/questions/33136/singly-linked-list-with-smart-pointers


class List {
public:
    List() {}
    List(int k) : data(k) {}
    ~List(){}
    void push(const std::shared_ptr<List>& new_node) {
        new_node->next = this->next;
        this->next = new_node;
    }
    bool empty() {
        if (this->next == nullptr) return true;
        return false;
    }
    int pop(){
        if (this->next == nullptr) return -1;
        std::shared_ptr<List> p = this->next;
        this->next = p->next;
        int v = p->data;
        return v;
    }
    void show(){
        std::shared_ptr<List> p = this->next;
        while (p) {
            std::cout << p->data << std::endl;
            p = p->next;
        }
    }
private:
    int data;
    std::shared_ptr<List> next;
};


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
