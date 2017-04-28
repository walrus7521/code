#include <iostream>

using namespace std;

template <typename T>
struct ListNode {
    T data;
    ListNode<T> *next;
};

ListNode<int> merge(ListNode<int> a, ListNode<int> b)
{
    ListNode<int> c;
    return c;
}

ListNode<int> *insert(ListNode<int> *l, int x)
{
    ListNode<int> *t = new ListNode<int>();
    cout << "insert: " << x << endl;
    t->data = x;
    t->next = l->next;
    l->next = t;
    return t;
}

void show(ListNode<int> *l)
{
    while (l->next) {
        cout << l->next->data << endl;
        l = l->next;
    }
}

int main()
{
    ListNode<int> *a = new ListNode<int>();
    a->next = nullptr;
    insert(a, 1);
    insert(a, 2);
    insert(a, 3);
    insert(a, 4);
    show(a);
    ListNode<int> *b = new ListNode<int>();
    b->next = nullptr;
}
