#include "pch.h"

#include "heap.h"

int main()
{
    //int ii[] = {2,5,1,33,16,9,22,3,9};
    int ii[] = {67,42,43,68};

    int i;
    int sz = sizeof(ii) / sizeof(ii[0]);
    struct heap *h = heap_create(32);
    for (i = 0; i < sz; i++) {
        heap_insert(h, ii[i]);
    }
    heap_tree(h);
    i = heap_top(h);
    heap_tree(h);
    printf("mx: %d\n", i);

    heap_extract(h, 42);
    heap_tree(h);
    heap_extract(h, 68);
    heap_tree(h);
    heap_extract(h, 67);
    heap_tree(h);
    heap_extract(h, 43);
    heap_tree(h);
}

