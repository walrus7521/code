#ifndef _Fifo_h_
#define _Fifo_h_

#include "pch.hpp"

using namespace std;

template <typename T>
struct Fifo {
    Fifo<T> *next;
    Fifo<T> *tail;
    T key;
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
    T key; //= INVALID;
    if (head->next != nullptr) {
        Fifo<T> *n = head->next;
        if (n->next == nullptr) {
            head->next = head->tail = nullptr;
        } else {
            head->next = n->next;
        }
        key = n->key;
        delete n;
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
    cout << "show list:" << endl;
    if (head->next == nullptr) return;
    Fifo<T> *p = head->next;
    while (p) {
        cout << p->key << endl;
        p = p->next;
    }
}

#endif // _Fifo_h_
