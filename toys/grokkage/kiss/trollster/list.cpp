#include <iostream>
#include "types.hpp"

using namespace std;

template <typename T>
void show(const shared_ptr<link_t<T>> &list)
{
    cout << "show list: \n";
    auto p = list;
    while (p->next) {
        cout << p->next->data << endl;
        p = p->next;
    }
}

template <typename T>
shared_ptr<link_t<T>> merge(link_t<T> a, link_t<T> b)
{
    shared_ptr<link_t<T>> c;
    return c;
}

template <typename T>
void insert(shared_ptr<link_t<T>> &list, T x)
{
    auto t = make_shared<link_t<T>>();
    cout << "insert: " << x << endl;
    t->data = x;
    t->next = nullptr;
    if (list->next == nullptr) {
        list->next = t;
    } else {
        t->next = list->next;
        list->next = t;
    }
}

template <typename T>
void reverse(shared_ptr<link_t<T>> &list)
{
    auto p = list->next, q = list, r =list;
    r = nullptr;
    p = list->next;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    list->next = r;
}

int main()
{
    shared_ptr<link_t<int>> list = make_shared<link_t<int>>();
    list->next = nullptr;
    insert(list, 1);
    insert(list, 2);
    insert(list, 3);
    insert(list, 4);
    show(list);
    reverse<int>(list);
    show(list);
}
