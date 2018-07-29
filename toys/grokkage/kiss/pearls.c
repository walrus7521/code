#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

// sorting algorithms
// base these on a global x[] and N
const int N = 8;
int s[N] = {1,5,2,4,6,3,7,8};

void show()
{
    int i;
    for (i = 0; i < N; i++) {
        printf("%d, ", s[i]);
    }
    printf("\n");
}

void swap(int i, int j)
{
    printf("swap(%d, %d)\n", i, j);
    if (i == j) return;
    int t = s[i];
    s[i] = s[j];
    s[j] = t;
}

void isort()
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = i; j > 0; j--) {
            if (s[j-1] > s[j]) swap(j, j-1);
        }
    }
}

int partition(int l, int u)
{
    int m = l;
    int i;
    for (i = l+1; i <= u; i++) {
        if (s[i] < s[l]) {
            swap(++m, i);
        }
    }
    swap(l, m);
    return m;
}

void my_qsort(int l, int u)
{
    if (l >= u) return;
    int m = partition(l, u);
    my_qsort(l, m-1);
    my_qsort(m+1, u);
}

// column 8
// max subset sum
float maxsum1(float x[], int n)
{
    float maxsofar = 0.0f;
    float sum = 0.0f;
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            sum = 0.0f;
            for (k = i; k <= j; k++) {
                sum += x[k];
            }
            maxsofar = max(maxsofar, sum);
        }
    }
    return maxsofar;
}

float maxsum2(int x[], int n)
{
    int maxsofar = 0.0f;
    int sum = 0.0f;
    int i, j;
    for (i = 0; i < n; i++) {
        sum = 0.0f;
        for (j = i; j < n; j++) {
            sum += x[j];
            maxsofar = max(maxsofar, sum);
            //printf("maxsofar: %f @ i:%d j:%d\n", maxsofar, i, j);
        }
    }
    return maxsofar;
}

float maxsum3(float x[], int n)
{
    float maxsofar = 0.0f;
    float sum = 0.0f;
    float tmp[64];
    float *cumarr = &tmp[2];
    int i, j;
    memset(tmp, sizeof(tmp), 0);
    cumarr[-1] = 0.0f;
    for (i = 0; i <= n; i++) {
        cumarr[i] = cumarr[i-1] + x[i];
    }
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            sum = cumarr[j] - cumarr[i-1];
            maxsofar = max(maxsofar, sum);
        }
    }
    return maxsofar;
}

int binarysum(int x[], int n) // unsorted input
{
    int l, u, m, i;
    int sum;
    l = 0;
    u = n-1;
    while (l <= u) {
        m = (l + u) / 2;
        sum = 0;
        for (i=l;i<=m;i++) {
            sum += x[i];
        }
        for (i=m;i<=u;i++) {
            sum += x[i];
        }
        //if (x[m] > t) {
        //    u = m-1;
        //} else if (x[m] == t) {
        //    //assert(x[m] == t);
        //    return m;
        //} else {
        //    l = m+1;
        //}
    }
    return -1;
}




#define MY_ASSERT(expr) printf("%s file: %s func: %s line: %d\n", #expr, __FILE__, __FUNCTION__, __LINE__)

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

void test_bsearch()
{
    DataType t;
    int i, testnum;
    unsigned long udelta;
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
        delta_t *= 1000000000.0f; // to nsec
        udelta = (unsigned long) delta_t;
        printf("algnum: %d, n: %d, numtests: %d, delta t %ld nsec\n", algnum, n, numtests, udelta);

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

void test_maxsum()
{
    int x[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
    int n = sizeof(x) / sizeof(x[0]);
    printf("max: %.2f\n", maxsum2(x, n));
    binarysum(x, n); // unsorted input

}

void test_sort()
{
    //isort();
    my_qsort(0, N-1);
    show();
}

int main()
{
    //test_maxsum();
    test_sort();
}

