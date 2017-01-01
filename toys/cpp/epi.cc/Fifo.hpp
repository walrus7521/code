#ifndef _Fifo_h_
#define _Fifo_h_

#include "pch.hpp"

template <typename T>
struct Fifo {
    Fifo<T> *next;
    Fifo<T> *tail;
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

// put to tail
template <typename T>
void Fifo_put(Fifo<T> *head, T key)
{
    Fifo<T> *n = Fifo_create(key);
    if (head->tail == nullptr) {
        head->next = head->tail = n;
    } else {
        head->tail->next = n;
        head->tail = n;
    }
}

// get from head
template <typename T>
T Fifo_get(Fifo<T> *head)
{
    T key; // = INVALID;
    Fifo<T> *n = head->next;
    if (head->next != nullptr) {
        n = head->next;
        key = n->key;
        head->next = n->next;
        delete n;
        n = nullptr;
    }
    return key;
}

template <typename T>
bool Fifo_empty(Fifo<T> *head)
{
    if (head->next == nullptr) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
void Fifo_show(Fifo<T> *head)
{
    std::cout << "show list:" << std::endl;
    if (head->next == nullptr) return;
    Fifo<T> *p = head->next;
    while (p) {
        std::cout << p->key << std::endl;
        p = p->next;
    }
}

#endif // _Fifo_h_
