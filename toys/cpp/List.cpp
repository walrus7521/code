#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct ListNode {
    T key;
    shared_ptr<ListNode<T>> next;
};

template <typename T>
shared_ptr<ListNode<T>> create(T key)
{
    shared_ptr<ListNode<int>> n(new ListNode<int>);
    n->next = nullptr;
    n->key = key;
    return n;
}

template <typename T>
shared_ptr<ListNode<T>> push_front(shared_ptr<ListNode<T>>& list, T key)
{
    shared_ptr<ListNode<int>> n = create(key);
    n->next = list->next;
    list->next = n;   
    return n;
}

template <typename T>
T pop(shared_ptr<ListNode<T>>& list)
{
    static T invalid;
    if (list->next == nullptr) {
        return invalid;
    } else {
        shared_ptr<ListNode<int>> n = list->next;
        list->next = n->next;
        T key = n->key;
        return key;
    }
}

template <typename T>
int empty(const shared_ptr<ListNode<T>>& list)
{
    if (list->next == nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
void show(const shared_ptr<ListNode<T>> list)
{
    shared_ptr<ListNode<T>> tmp = list;
    while (tmp->next != nullptr) {
        cout << tmp->next->key << endl;
        tmp = tmp->next;
    }
}

int main()
{
    shared_ptr<ListNode<int>> list(new ListNode<int>);
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
