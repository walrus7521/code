#include <stdio.h>

#define LT(x, y) ((x) <  (y))
#define GE(x, y) ((x) >= (y))

int a[13] = {0,1,5,3,4,8,2,7,6,9,11,10,33};
int n_elems = 12;

void insert(int current, int low, int high, int *entry)
{
    int large;
    large = 2*low+1;
    while (large <= high) {
        if (large < high && LT(entry[large], entry[large+1]))
            large++;
        if (GE(current, entry[large]))
            break;
        else {
            entry[low] = entry[large];
            low = large;
            large = 2*low+1;
        }
    }
    entry[low] = current;
}

void build(int *entry, int count)
{
    int low;
    for (low = count/2-1; low >= 0; --low) {
        insert(entry[low], low, count, entry);
    }
}

void sort(int *entry, int count)
{
    int current;
    int lu;
    if (count == 1) return;
    build(entry, count);
    for (lu = count; lu >= 1; --lu) {
        current = entry[lu];
        entry[lu] = entry[0];
        insert(current, 0, lu-1, entry);
    }
}

int delete(int *a, int count)
{
    int first = a[1];
    int last = a[n_elems];
    a[1] = last;
    n_elems--;
    sort(a, n_elems);
    return first;
}

void show(int *a, int count)
{
    int i;
    if (count == 0) return;
    for (i = 1; i <= count; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }
    printf("\n");
}

int main()
{
    int i, n;
    show(a, n_elems);
    sort(a, n_elems);
    show(a, n_elems);
    while (n_elems > 0) {
        n = delete(a, n_elems);
        printf("min = %d, n_elems %d\n", n, n_elems);
        //show(a, n_elems);
    }
    return 0;
}
