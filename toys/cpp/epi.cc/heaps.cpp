#include "pch.hpp"
#include "Heap.hpp"

int main()
{
    //int ii[] = {2,5,1,33,16,9,22,3,9};
    int ii[] = {67,42,43,68};

    int i;
    int sz = sizeof(ii) / sizeof(ii[0]);
    Heap<int> *h = Heap_create<int>(32);
    for (i = 0; i < sz; i++) {
        Heap_insert(h, ii[i]);
    }
    Heap_tree(h);
    i = Heap_top(h);
    Heap_tree(h);
    printf("mx: %d\n", i);

    Heap_extract(h, 42);
    Heap_tree(h);
    Heap_extract(h, 68);
    Heap_tree(h);
    Heap_extract(h, 67);
    Heap_tree(h);
    Heap_extract(h, 43);
    Heap_tree(h);
}

