#include <iostream>
#include "types.hpp"

using namespace std;

template <typename T>
void show(const shared_ptr<list_t<T>> &l)
{
    std::cout << "using non-generic" << std::endl;
    auto p = l->first;
    for (auto entry = p; entry != nullptr; entry = entry->next) {
        std::cout << entry->data << std::endl;
    }
}

template <typename Iter, typename T>
void show(Iter it, Iter end, T init)
{
    std::cout << "using generic" << std::endl;
    for (; it != end; ++it) {
        std::cout << *it << std::endl;
    }
}

template <typename T>
shared_ptr<link_t<T>> merge(link_t<T> a, link_t<T> b)
{
    shared_ptr<link_t<T>> c;
    return c;
}

template <typename T>
void reverse(shared_ptr<list_t<T>> &list)
{
    auto p = list->first, q = list->first, r =list->first;
    r = nullptr;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    list->first = r;
}

int main()
{
    shared_ptr<list_t<int>> list = make_shared<list_t<int>>();
    list->append(1);
    list->append(2);
    list->append(3);
    list->append(4);
    show(list);
    reverse<int>(list);
    show(list->begin(), list->end(), 0);
}

