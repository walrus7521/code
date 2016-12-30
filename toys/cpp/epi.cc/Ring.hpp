#ifndef _Ring_h_
#define _Ring_h_

#include "pch.hpp"

template <typename T>
struct Ring {
    T *A;
    int read;
    int write;
    int size;
};

enum {
    INVALID = -1
};

template <typename T>
void Ring_show(Ring<T> *ring);

template <typename T>
Ring<T> *Ring_create(int size)
{
    Ring<T> *r = new Ring<T>();
    r->A = (T *) calloc(size, sizeof(T));
    r->read = r->write = 0;
    r->size = size;
    return r;
}

template <typename T>
void Ring_put(Ring<T> *ring, T key)
{
}

// get is toast
template <typename T>
T Ring_get(Ring<T> *ring)
// fetches from end of list
{
    T key = INVALID;
    return key;
}

template <typename T>
bool Ring_empty(Ring<T> *ring)
{
    if (ring->read == ring->write) return true;
    return false;
}

template <typename T>
void Ring_show(Ring<T> *ring)
{
    printf("show ring:\n");
    for (int i = 0; i < ring->size; ++i) {
        printf("r[%d] => %d\n", i, ring->A[i]);
    }
}

#endif // _Ring_h_
