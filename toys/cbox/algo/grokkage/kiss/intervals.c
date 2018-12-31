#include <stdio.h>

typedef struct interval {
    int left, right;
} interval;

void interval_sort(interval *arr)
{
    interval tmp;
}

void show_intervals(interval *arr) //, int n)
{
    while (arr && arr->left != -1) {
        printf("{%d,%d}\n", arr->left, arr->right);
        arr++;
    }
}

int main()
{
    interval arr[] = {
        {1,2},
        {2,3},
        {4,5},
        {6,9},
        {-1,-1}
    };
    show_intervals(arr);
    interval_sort(arr);
}


