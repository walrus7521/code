#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

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

float maxsum2(float x[], int n)
{
    float maxsofar = 0.0f;
    float sum = 0.0f;
    int i, j;
    for (i = 0; i < n; i++) {
        sum = 0.0f;
        for (j = i; j < n; j++) {
            sum += x[j];
            maxsofar = max(maxsofar, sum);
        }
    }
    return maxsofar;
}

float maxsum3(float x[], int n)
{
    float maxsofar = 0.0f;
    float sum = 0.0f;
    float *cumarr;
    float tmp[64];
    int i, j;
    memset(tmp, sizeof(tmp), 0);
    cumarr = &tmp[2]; // to allow [-1]
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
    float x[] = {31.0f, -41.0f, 59.0f, 26.0f, -53.0f, 58.0f, 97.0f, -93.0f, -23.0f, 84.0f};
    int n = sizeof(x) / sizeof(x[0]);
    printf("max: %f\n", maxsum3(x, n));


}


int main()
{
    test_maxsum();
}

