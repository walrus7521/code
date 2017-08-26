#ifndef _heap_h_
#define _heap_h_

#include "pch.hpp"

#define PARENT(x)       (x/2)
#define LEFT_CHILD(x)   ((2*(x))+1)
#define RIGHT_CHILD(x)  ((2*(x)))


struct Heap {
    int *A; // index 0 is not used
    //std::shared_ptr<int> A;
    int length;
    int size;
};


std::shared_ptr<Heap> CreateHeap(int size) {
    std::shared_ptr<Heap> heap = std::make_shared<Heap>();
    //heap->A = std::make_shared<int>(size);
    heap->A = new int(size);
    heap->length = 1;
    heap->size = size;
    return heap;
}

void InsertHeap(const std::shared_ptr<Heap>& h, int key)
{
    int i, tmp;
    h->A[h->length] = key;
    for (i = h->length; i > 1; --i) {
        if (h->A[i] > h->A[PARENT(i)]) {
            tmp = h->A[i];
            h->A[i] = h->A[PARENT(i)];
            h->A[PARENT(i)] = tmp;
        }
    }
    h->length++;
}

void TreeHeap(const std::shared_ptr<Heap> h)
{
    int i, level, j, k;
    int lvl[] = {0, 1,  2,  2,  4,  4,  4,  4, \
                    8,  8,  8,  8,  8,  8,  8,  8, \
                   16, 16, 16, 16, 16, 16, 16, 16, \
                   16, 16, 16, 16, 16, 16, 16, 16, 16};
    for (i = 1; i <= h->length-1; ) {
        level = lvl[i];
        switch (level) {
            case 1: printf("        "); break;
            case 2: printf("      "); break;
            case 4: printf("  "); break;
        }
        //printf("lvl %d i=%d\n", level, i);
        for (j = i, k = 1; (k <= level) && (i <= h->length-1); ++k, ++j) {
            printf("[%d] ", h->A[j]);
            ++i;
        }
        printf("\n");
    }
}

void DumpHeap(const std::shared_ptr<Heap>& h)
{
    int i;
    for (i = 1; i <= h->length-1; ++i) {
        printf("A[%d] = %d\n", i, h->A[i]);
    }
}

int TopHeap(const std::shared_ptr<Heap>& h)
{
    int key = h->A[1], i, tmp;
    h->A[1] = h->A[h->length-1];
    h->length--;
    for (i = 1; i < h->length; ++i) {
        if (h->A[i] < h->A[LEFT_CHILD(i)]) {
            tmp = h->A[i];
            h->A[i] = h->A[LEFT_CHILD(i)];
            h->A[LEFT_CHILD(i)] = tmp;
        } 
        if (h->A[i] < h->A[RIGHT_CHILD(i)]) {
            tmp = h->A[i];
            h->A[i] = h->A[RIGHT_CHILD(i)];
            h->A[RIGHT_CHILD(i)] = tmp;
        }
    }
    return key;
}

void ExtractHeap(const std::shared_ptr<Heap>& h, int key)
{
    int i, j, tmp;
    printf("extracting: %d\n", key);
    for (i = 1; i < h->length; ++i) {
        if (key == h->A[i]) {
            h->length--;
            if (i == h->length) {
                h->A[i] = 0;
                return;
            }
            printf("found match %d, swap %d with %d\n", key, h->A[i], h->A[h->length-1]);
            h->A[i] = h->A[h->length];
            for (j = i; j < h->length; ++j) {
                if (h->A[j] < h->A[LEFT_CHILD(j)]) {
                    tmp = h->A[j];
                    h->A[j] = h->A[LEFT_CHILD(j)];
                    h->A[LEFT_CHILD(j)] = tmp;
                } 
                if (h->A[j] < h->A[RIGHT_CHILD(j)]) {
                    tmp = h->A[j];
                    h->A[j] = h->A[RIGHT_CHILD(j)];
                    h->A[RIGHT_CHILD(j)] = tmp;
                }
            }
            return;
        }
    }
}

#endif // _heap_h_

#include "pch.hpp"

using namespace std;

void use_api()
{
    //int ii[] = {2,5,1,33,16,9,22,3,9};
    int ii[] = {67,42,43,68};
    int i;
    int sz = sizeof(ii) / sizeof(ii[0]);
    //shared_ptr<ListNode<int>> head = make_shared<ListNode<int>>();
    shared_ptr<Heap> heap = CreateHeap(32);

    for (int i = 0; i < sz; i++) {
        cout << "insert: " << ii[i] << endl;
        InsertHeap(heap, ii[i]);
    }
    DumpHeap(heap);
    TreeHeap(heap);
    i = TopHeap(heap);
    TreeHeap(heap);
    printf("mx: %d\n", i);

    ExtractHeap(heap, 42);
    TreeHeap(heap);
    ExtractHeap(heap, 68);
    TreeHeap(heap);
    ExtractHeap(heap, 67);
    TreeHeap(heap);
    ExtractHeap(heap, 43);
    TreeHeap(heap);

}

void use_stdlib()
{
}

int main()
{
    use_api();
    //use_stdlib();
}

