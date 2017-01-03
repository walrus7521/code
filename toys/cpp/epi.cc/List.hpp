#ifndef _List_h_
#define _List_h_

#include "pch.hpp"
#include "Heap.hpp"

using namespace std;

template <typename T>
struct List {
    List<T> *next;
    T key;
    Heap<T> *max;
};

enum {
    INVALID = -1
};

template <typename T>
void List_show(List<T> *head);

template <typename T>
List<T> *List_create(T key)
{
    List<T> *l = new List<T>();
    l->next = nullptr;
    l->key = key;
    l->max = Heap_create<T>(32);
    return l;
}

template <typename T>
void List_push(List<T> *head, T key)
{
    List<T> *n = List_create(key);
    if (head->next == nullptr) {
        head->next = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
    Heap_insert<T>(head->max, key);

}

template <typename T>
T List_pop(List<T> *head)
{
    static T invalid;
    if (head->next == nullptr) {
        return invalid;
    } else {
        List<T> *n = head->next;
        head->next = n->next;
        T key = n->key;
        free(n);
        Heap_extract<T>(head->max, key);
        return key;
    }
}

template <typename T>
List<T> *List_reverse(List<T> *head)
{
    List<T> *p = head->next;
    List<T> *q;
    List<T> *r = nullptr;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}

template <typename T>
T List_max(List<T> *head)
{
    int mx = head->max->A[1];
    return mx;
}

template <typename T>
int List_empty(List<T> *head)
{
    if (head->next == nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
List<T> *merge_2_sorted_lists(List<T> *l1, List<T> *l2)
{
    List<T> *m = nullptr;
    List<T> *n1 = l1->next;
    List<T> *n2 = l2->next;
    List<T> *q = nullptr;
    List<T> *ret = nullptr;
    while (n1 && n2) {
        if (n1->key <= n2->key) {
            cout << "n1: " << n1->key << endl;
            if (m == nullptr) {
                m = l1;
                ret = m;
            }
            q = n1;
            n1 = n1->next;
            q->next = m->next;
            m->next = q;
        } else {
            cout << "n2: " << n2->key << endl;
            if (m == nullptr) {
                m = l2;
                ret = m;
            }
            q = n2;
            n2 = n2->next;
            q->next = m->next;
            m->next = q;
        }
        m = m->next;
    }
    if (n1) {
        m->next = n1;
    } else if (n2) {
        m->next = n2;
    }
    return ret;
}

template <typename T>
void List_show(List<T> *head)
{
    cout << "show list:" << endl;
    if (head->next == nullptr) return;
    List<T> *p = head->next;
    while (p) {
        cout << "node: " << p->key << endl;
        p = p->next;
    }
}

#endif // _List_h_
