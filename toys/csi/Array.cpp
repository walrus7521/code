// sorting/strings
//
#include <iostream>
#include <vector>
#include <cstdio>

#define exchg(A, B) { int t = A; A = B; B = t; } 

#define exchg2(X, Y) { \
    (X) = (X) ^ (Y);   \
    (Y) = (Y) ^ (X);   \
    (X) = (X) ^ (Y); }

using namespace std;

template <typename T>
void show(vector<T>& v)
{
    for (auto e : v) cout << e << ",";
    cout << endl;
}

void sort_show(int a[], int n)
{
    int i;
    for (i = 0 ; i < n; i++) {
        printf("%3d", a[i]);
    }
    printf("\n\n\n ");
}

template <typename T>
void merge(vector<T>& v, int first, int mid, int last)
{
    vector<T> tmp;
    int idxA = first;
    int idxB = mid;

    while (idxA < mid && idxB < last) {
        if (v[idxA] < v[idxB]) tmp.push_back(v[idxA++]);
        else                   tmp.push_back(v[idxB++]);
    }
    while (idxA < mid) tmp.push_back(v[idxA++]);
    while (idxB < last) tmp.push_back(v[idxB++]);
    // copy tmp back to v
    idxA = first; // starting at first
    int idxV = 0;
    while (idxV < tmp.size()) v[idxA++] = tmp[idxV++];
}

// merge sort
template <typename T>
void split(vector<T>& v, int first, int last)
{
    if (first + 1 < last) {
        int mid = (last + first) / 2;
        split(v, first, mid);
        split(v, mid, last);
        merge(v, first, mid, last);
    }
}


int partition(int *A, int lo, int hi) {
    int i, p, firsthigh;
    p = hi; /* pick a partition (=hi) */
    firsthigh = lo; /* firsthigh is the partition boundary */
    for (i = lo; i < hi; ++i) {
        if (A[i] < A[p]) {
            exchg(A[i], A[firsthigh]);
            firsthigh++;
        }
    }
    exchg(A[p], A[firsthigh]);
    return firsthigh;
}

void quicksort(int *A, int lo, int hi) {
    int p;
    if (lo < hi) {
        p = partition(A, lo, hi);
        quicksort(A, lo, p-1);
        quicksort(A, p+1, hi);
    }
}

void do_quicksort()
{
    int a[] = {26,33,35,29,19,12,22,15,42,69,1};
    int sz = sizeof(a)/sizeof(a[0]);
    printf("quicksort: "); quicksort(a, 0, sz-1);
    sort_show(a, sz);
}

void do_mergesort()
{
    vector<int> v = {25,10,7,19,3,48,12,17,56,30,21};
    vector<string> s = {"Dallas","Akron","Wausau","Phoenix",
                        "Fairbanks","Miami"};
    split(v,0,v.size());
    show(v);
    split(s,0,s.size());
    show(s);
}

int main()
{
    do_mergesort();
    do_quicksort();
}

