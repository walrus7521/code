#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef SEDGEWICK
#define SEDGEWICK
// sedgewick

#define MAXN 100

void arr_show(int a[], int n);
void swap(int a[], int i, int j);
void bubsort(int a[], int n);
void selsort(int a[], int n);
void inssort(int a[], int n);
void indirect_sort(int a[], int p[], int n);
unsigned int bits(unsigned int x, int k, int j);
void radix_exchange_sort(int a[], int l, int r, int b);
int partition(int a[], int l, int r);
void select_kth_largest(int a[], int l, int r, int k);
int smallest(int a[], int n);
void append(int tape[], int i, int buf[], int j, int n);
void three_way_merge_sort();


#endif // SEDGEWICK


