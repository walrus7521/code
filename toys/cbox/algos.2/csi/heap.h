#ifndef _heap_h_
#define _heap_h_

#include "pch.h"

#define PARENT(x)       (x/2)
#define LEFT_CHILD(x)   ((2*(x))+1)
#define RIGHT_CHILD(x)  ((2*(x)))

struct heap {
    int *A; // index 0 is not used
    int length;
    int size;
};

void heap_tree(struct heap *h);

struct heap* heap_create(int max)
{
    struct heap *h = (struct heap *) malloc(sizeof(struct heap));
    h->A = (int *) calloc(max, sizeof(int));
    h->size = max;
    h->length = 1;
    return h;
}

void heap_insert(struct heap *h, int key)
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

int heap_top(struct heap *h)
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

void heap_extract(struct heap *h, int key)
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

void heap_dump(struct heap *h)
{
    int i;
    for (i = 1; i <= h->length-1; ++i) {
        printf("A[%d] = %d\n", i, h->A[i]);
    }
}

void heap_tree(struct heap *h)
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


#endif // _heap_h_
