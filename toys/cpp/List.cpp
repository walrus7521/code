#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next;
};


template <typename T>
shared_ptr<ListNode<T>> insert(shared_ptr<ListNode<T>>& list, T data)
{
    shared_ptr<ListNode<int>> n(new ListNode<int>);
    n->data = data;
    n->next = list->next;
    list->next = n;   
    return n;
}

template <typename T>
void show(shared_ptr<ListNode<T>>& list)
{
    while (list->next != nullptr) {
        cout << list->next->data << endl;
        list = list->next;
    }
}

int main()
{
    shared_ptr<ListNode<int>> list(new ListNode<int>);
    list->next = nullptr;
    insert(list, 42);
    insert(list, 88);
    insert(list, 92);
    show(list);
}
