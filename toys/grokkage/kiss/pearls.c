#include <stdio.h>
#include <assert.h>
//#include <stdlib.h>

#define MAXN 256
typedef int DataType;

int n;
DataType x[MAXN];

int is_sorted();

int binarysearch(DataType t)
{
    int l, u, m;
    l = 0;
    u = n-1;
    assert(is_sorted());
    while (l <= u) {
        m = (l + u) / 2;
        if (x[m] > t) {
            u = m-1;
        } else if (x[m] == t) {
            assert(x[m] == t);
            return m;
        } else {
            l = m+1;
        }
    }
    assert((u < 0 || x[u] < t) && (u+1 >= n || x[u+1] > t));
    return -1;
}

int is_sorted()
{
    int i;
    for (i = 0; i < n-1; i++) {
        if (x[i] > x[i+1]) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    DataType t;
    int i;
    while (scanf("%d %d", &n, &t)) {
        for (i = 0; i < n; i++) {
            x[i] = 10*i;
        }
        printf(" %d\n", binarysearch(t));
    }
}
