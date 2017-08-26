#ifndef _Ring_h_
#define _Ring_h_

#include "pch.hpp"

using namespace std;

template <typename T>
struct Ring {
    T *A;
    int read;
    int write;
    int size;
};

enum {
    INVALID = -1,
    FULL = 1,
    EMPTY = 2,
    NOT_EMPTY = 3
};

template <typename T>
void Ring_show(Ring<T> *ring);

template <typename T>
void Ring_config(Ring<T> *ring, T *A, int size)
{
    ring->A = A;
    ring->read = ring->write = 0;
    ring->size = size;
}

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
    //if (ring->read != ring->write) {
        ring->A[ring->write++] = key;
    //}
}

// get is toast
template <typename T>
T Ring_get(Ring<T> *ring)
// fetches from end of list
{
    T key = INVALID;
    //if (ring->read != ring->write) {
        key = ring->A[ring->read++];
    //}
    return key;
}

template <typename T>
bool Ring_empty(Ring<T> *ring)
{
    if (ring->read == ring->write) return true;
    return false;
}

template <typename T>
int Ring_status(Ring<T> *ring)
{
    cout << "rd: " << ring->read << ", wr: " << ring->write << endl;
    if (ring->read == ring->write) {
        return EMPTY;
    }
    return NOT_EMPTY;
}

template <typename T>
void Ring_show(Ring<T> *ring)
{
    cout << "show ring:" << endl;
    for (int i = 0; i < ring->size; ++i) {
        cout << "r[" << i << "] => " << ring->A[i] << endl;
    }
}

#endif // _Ring_h_

#include "pch.hpp"

using namespace std;

int main()
{
    int A[32] = {0};
    Ring<int> ring = { .read = 0, .write = 0, .size = 32, .A = A };

    for (int i = 0; i < 16; ++i) {
        //if (!Ring_empty(&ring)) {
        Ring_put(&ring, i);
        Ring_status(&ring);
        //}
    }
    Ring_status(&ring);
    Ring_show(&ring);
    while (!Ring_empty(&ring)) {
        int key = Ring_get(&ring);
        cout << "get: " << key << endl;
        Ring_status(&ring);
    }
}

