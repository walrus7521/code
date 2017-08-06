#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define GE(x, y) ((x) >= (y))
#define LE(x, y) ((x) <= (y))
#define LT(x, y) ((x) < (y))


void heap_show();
void down_max(int k);
int delete_max();
void up_max(int k);
void insert_max(int v);
void heapify_max(int *a, int size);
void down_min(int k);
int delete_min();
void up_min(int k);
void insert_min(int v);
void heapify_min(int *a, int size);
void test_min_heap();
void test_max_heap();
int heap_test();

#endif // _HEAP_H_

