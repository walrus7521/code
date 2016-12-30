#ifndef _Fifo_h_
#define _Fifo_h_

#include "pch.hpp"

template <typename T>
struct Fifo {
    Fifo<T> *next;
    Fifo<T> *last;
    T key;
};

enum {
    INVALID = -1
};

template <typename T>
void Fifo_show(Fifo<T> *head);

template <typename T>
Fifo<T> *Fifo_create(T key)
{
    Fifo<T> *l = new Fifo<T>();
    l->next = nullptr;
    l->key = key;
    return l;
}

template <typename T>
void Fifo_put(Fifo<T> *head, T key)
{
    Fifo<T> *n = Fifo_create(key);
    if (head->last == nullptr) {
        head->next = head->last = n;
    } else {
        head->last->next = n;
        head->last = n;
    }
}

// get is toast
template <typename T>
T Fifo_get(Fifo<T> *head)
// fetches from end of list
{
    T key = INVALID;
    Fifo<T> *n = head->next;
    if (head->next == nullptr) {
        return key;
    } else
    if (head->next->next == nullptr) {
        key = n->key;
        free(n);
        head->next = head->last = nullptr;
        return key;
    } else { 
        // find 2nd to last node
        while (n->next->next != nullptr) {
            n = n->next;
        }
        Fifo<T> *r = head->last;
        head->last = n;
        n->next = nullptr;
        key = r->key;
        //free(r);
        return key;
    }
}

template <typename T>
int Fifo_empty(Fifo<T> *head)
{
    if (head->next == nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
void Fifo_show(Fifo<T> *head)
{
    printf("show list:\n");
    if (head->next == nullptr) return;
    Fifo<T> *p = head->next;
    while (p) {
        printf("node: %d\n", p->key);
        p = p->next;
    }
}

#endif // _Fifo_h_
