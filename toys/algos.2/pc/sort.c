#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}

void sel_sort(int s[], int n)
{
    int i, j;
    int min;

    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (s[j] < s[min]) min = j;
        }
        swap(&s[i], &s[min]);
    }
}

void ins_sort(int s[], int n)
{
    int i, j;

    for (i = 1; i < n; i++) {
        j = i;
        while ((j > 0) && (s[j] < s[j-1])) {
            swap(&s[j], &s[j-1]);
            j = j - 1;
        }
    }
}

int partition(int s[], int l, int h)
{
    int i, p, firsthigh;

    p = h;
    firsthigh = l;
    for (i = l; i < h; i++)
        if (s[i] < s[p]) {
            swap(&s[i], &s[firsthigh]);
            firsthigh++;
        }
    swap(&s[p], &s[firsthigh]);
    return (firsthigh);
}

void quicksort(int s[], int l, int h)
{
    int p;

    if ((h - 1) > 0) {
        p = partition(s, l, h);
        quicksort(s, l, p-1);
        quicksort(s, p+1, h);
    }
}

int main()
{
    return 0;
}

