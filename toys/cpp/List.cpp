#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct ListNode {
    T key;
    shared_ptr<ListNode<T>> next;
};

template <typename T>
using ListPtr = shared_ptr<ListNode<T>>;

template <typename T>
ListPtr<T> create(T key)
{
    ListPtr<T> n(new ListNode<T>);
    n->next = nullptr;
    n->key = key;
    return n;
}

template <typename T>
ListPtr<T> push_front(ListPtr<T>& list, T key)
{
    ListPtr<T> n = create(key);
    n->next = list->next;
    list->next = n;   
    return n;
}

template <typename T>
T pop(ListPtr<T>& list)
{
    static T invalid;
    if (list->next == nullptr) {
        return invalid;
    } else {
        ListPtr<T> n = list->next;
        list->next = n->next;
        T key = n->key;
        return key;
    }
}

template <typename T>
int empty(const ListPtr<T>& list)
{
    if (list->next == nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
void show(const ListPtr<T> list)
{
    ListPtr<T> tmp = list;
    while (tmp->next != nullptr) {
        cout << tmp->next->key << endl;
        tmp = tmp->next;
    }
}

int main()
{
    ListPtr<int> list(new ListNode<int>);
    list->next = nullptr;
    push_front(list, 42);
    push_front(list, 88);
    push_front(list, 92);
    show(list);
    while (!empty(list)) {
        int key = pop(list);
        cout << "popped: " << key << endl;
    }
}
