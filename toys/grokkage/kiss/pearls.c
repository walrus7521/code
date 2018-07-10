#include <stdio.h>
#include <assert.h>
#include <time.h>

// side note: check out ptest

/*
 *
 * while read(algnum, n, numtests)
    for i = [0, n)
        x[i] = i
    starttime = clock()
    for testnum = [0, numtests)
        for i = [0, n)
            switch (algnum)
                case 1: assert(binarysearchl(i) == i)
                case 2: assert(binarysearch2(i) == i)
    clicks = clock() - starttime
    print algnum, n, numtests, clicks,
        clicks/(1e9 * CLOCKS_PER_SEC * n * numtests)

*/

// next: automated test

#define MAXN 1024
#define s binarysearch
typedef int DataType;
clock_t starttime, clicks, endtime;
static double delta_t;

int algnum;
int numtests;
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
    int i, testnum;
    printf("input algo# n num tests\n");
    while (scanf("%d %d %d", &algnum, &n, &numtests)) {
        for (i = 0; i < n; i++) {
            x[i] = 10*i;
        }
        starttime = clock();
        for (testnum = 0; testnum < numtests; testnum++) {
            for (i = 0; i < n; i++) {
                switch (algnum) {
                    case 1: assert(binarysearch(10*i) == i);
                }
            }
        }
        clicks = clock() - starttime;
        delta_t = (double)(clicks) / CLOCKS_PER_SEC / numtests / n;
        delta_t *= 1000000.0f; // to usec
        printf("algnum: %d, n: %d, numtests: %d, delta t %lf usec\n", algnum, n, numtests, delta_t);
#if 0
        // check distinct elements - plus one at end
        for (i = 0; i < n; i++) {
            assert(s(10*i) == i);
            assert(s((10*i)-5) == -1);
        }
        assert(s((10*n)) == -1);
        assert(s((10*n)-5) == -1);
        // now test equal elements
        if (n == 0) {
            assert(s(10) == -1);
        } else {
            assert(0 <= s(10) && s(10) < n);
        }
        assert(s(5) == -1);
        assert(s(15) == -1);
        for (i = 0; i < n; i++) {
            assert(s(10*i) == i);
            assert(s((10*i)-5) == -1);
        }
        printf(" %d\n", s(t));
#endif
    }
}

