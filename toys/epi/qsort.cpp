#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

void swap(vector<int> &a, int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void three_way_partition(vector<int> &a, int mid)
{
    int n = a.size()-1;
    int i = 0, j = 0;
    while (j <= n) {
        if (a[j] < mid) {
            swap(a, i, j);
            i++;
            j++;
        } else if (a[j] > mid) {
            swap(a, j, n);
            n--;
        } else {
            j++;
        }
    }
}

int two_way_partition( vector<int> &a, int low, int high )
{
  int left, right;
  int pivot_item, pivot;
  pivot_item = a[low];
  pivot = left = low;
  right = high;
  while ( left < right ) {
    /* Move left while item < pivot */
    while( a[left] <= pivot_item ) left++;
    /* Move right while item > pivot */
    while( a[right] > pivot_item ) right--;
    if ( left < right ) swap(a,left,right);
    }
  /* right is final position for the pivot */
  a[low] = a[right];
  a[right] = pivot_item;
  return right;
}

void qsort(vector<int> &v, int left, int right)
{
    int i, last;
    if (left >= right) return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; ++i) {
        if (v[i] < v[left])
            swap(v, ++last, i);
        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
    }
}

void show(vector<int> a)
{
    for (auto i: a) {
        cout << i << endl;
    }
}

int main()
{
    vector<int> a = {5,4,5,21,6,4,2,5,9};
    //two_way_partition(a, 0, len-1);
    three_way_partition(a, 5);
    //qsort(a, 0, len-1);
    show(a);
}
