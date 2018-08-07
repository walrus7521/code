#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
//#include <cstdint>
//#include <cinttypes>
#include <set>
#include <algorithm>

using std::set;
using std::sort;

#define max(a,b) ((a) > (b) ? (a) : (b))



void show_heap(int x[], int n)
/* note: heaps start at x[1]
 */
{
    int level;
    int l, u;
    int nlevels = log2((double) n) + 1;
    printf("levels(%d) = %d\n", n, nlevels);
    for (level = 0; level < nlevels; level++) {
        l = exp2(level);
        u = 2*l;
        //printf("level: %d, start: %d, end: %d\n", level, l, u-1);
        for (; l < u; l++) {
            if (l == n+1) break; // may not be a complete tree
            printf("%d ", x[l]);
        }
        printf("\n");
    }
    int i;
    for (i = 1; i <= n; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}

void siftup(int x[], int n)
/*
 * pre:  n > 0 && heap(1, n-1)
 * post: heap(1, n)
 */
{
    int i; // current value
    int p; // parent
    int tmp; // swap temp
    i = n; // element to be added
    printf("adding: %d\n", x[n]);
    while (1) {
        if (i == 1) break;
        p = i/2;
        if (x[p] <= x[i]) break;
        //printf("parent: %d\n", x[p]);
        //swap(p, i);
        tmp = x[p]; x[p] = x[i]; x[i] = tmp;
        i = p; // set current to parent
    }
}

void siftdown(int x[], int n)
/*
 * pre:  n > 0 && heap(2, n)
 * post: heap(1, n)
 */
{
    int i; 
    int c;
    int tmp;
    i = 1;
    while (1) {
        if (n == 0) break;
        c = 2*i; // left child
        if (c > n) break;
        if (c+1 <= n) {
            if (x[c+1] < x[c]) c++;
        }
        if (x[c] < x[i]) {
            //swap(c, i);
            tmp = x[c]; x[c] = x[i]; x[i] = tmp;
        }
        i = c;
    }
}

unsigned long long bigrand();

//// c++ class
class IntSetImp {
public:
    IntSetImp(int maxelements, int maxval) {}
    void insert(int t) {}
    int size() { return 0; }
    void report(int *v) {}
};

class IntSetSTL {
private:
    set<int> S;
public:
    IntSetSTL(int maxelements, int maxval) {}
    int size() { return S.size(); }
    void insert(int t) { S.insert(t); }
    void report(int *v) {
        int j = 0;
        set<int>::iterator i;
        for (i = S.begin(); i != S.end(); ++i) {
            v[j++] = *i;
        }
    }
};

void gensets2(int m, int maxval)
{
    int *v = new int[m];
    IntSetSTL S(m, maxval);
    while (S.size() < m) {
        S.insert(bigrand() % maxval);
    }
    S.report(v);
    for (int i = 0; i < m; ++i) {
        printf("gs2::v[%d] = %d\n", i, v[i]);
    }
}




// sorting algorithms 
// base these on a global x[] and N
#define SIZE (8)
const int N = SIZE;
int s[SIZE] = {5,7,6,2,8,4,1,3};

void show()
{
    for (int i = 0; i < N; i++) {
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
    for (int i = 0; i < N; i++) {
        for (int j = i; j > 0; j--) {
            if (s[j-1] > s[j]) swap(j, j-1);
        }
    }
}

unsigned long long bigrand()
{
    unsigned long long r = rand();
    return r<<32 | r;
}

int randint(int l, int u)
{
    float r = (float) rand();
    r /= RAND_MAX;
    int idx = l + r * (u-l-1);
    //printf("r: %f -> %d -> %d -> %d\n", r, l, idx, u);
    return idx;
}

void genshuf(int m, int n)
{
    int i, j;
    int *x = new int[n];
    for (i = 0; i < n; i++) {
        x[i] = i;
    }
    for (i = 0; i < m; i++) {
        j = randint(i, n-1);
        int t = x[i]; x[i] = x[j]; x[j] = t;
    }
    sort(x, x+m);
    for (i = 0; i < m; i++) {
        printf("%d => %d\n", i, x[i]);
    }
}

void gensets(int m, int n)
{
    set<int> S;
    while (S.size() < m) {
        S.insert(rand()%n);
    }
    for (set<int>::iterator i = S.begin(); i != S.end(); ++i) {
        printf("=> %d\n", *i);
    }
}

int my_part(int l, int u)
{
    int pivot = l;
    int t = s[pivot];
    for (int i = l+1; i <= u; i++) {
        if (s[i] < t) {
            pivot++;
            swap(pivot, i);
        }
    }
    swap(pivot, l);
    return pivot;
}

int my_part2(int l, int u)
{
    if (l >= u) return -1;
    int t = s[l], i = l, j = u+1;
    while (1) {
        do {
            i++;
        } while (i <= u && s[i] < t);
        do {
            j--;
        } while (s[j] > t);
        if (i > j) break;
        swap(i, j);
    }
    swap(l, j);
    return j;
}

int my_part3(int l, int u)
{
    int pivot = randint(l, u);
    swap(pivot, l);
    pivot = l;
    int t = s[pivot];
    for (int i = l+1; i <= u; i++) {
        if (s[i] < t) {
            pivot++;
            swap(pivot, i);
        }
    }
    swap(pivot, l);
    return pivot;
}

void my_qsort(int l, int u)
{
    if (l >= u) return;
    //int m = my_part(l, u);
    //int m = my_part2(l, u);
    int m = my_part3(l, u);
    my_qsort(l, m-1);
    my_qsort(m+1, u);
}

// column 8
// max subset sum
float maxsum1(float x[], int n)
{
    float maxsofar = 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            sum = 0.0f;
            for (int k = i; k <= j; k++) {
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
    for (int i = 0; i < n; i++) {
        sum = 0.0f;
        for (int j = i; j < n; j++) {
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
    memset(tmp, sizeof(tmp), 0);
    cumarr[-1] = 0.0f;
    for (int i = 0; i <= n; i++) {
        cumarr[i] = cumarr[i-1] + x[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
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
    int testnum;
    unsigned long udelta;
    printf("input algo# n num tests\n");
    while (scanf("%d %d %d", &algnum, &n, &numtests)) {
        for (int i = 0; i < n; i++) {
            x[i] = 10*i;
        }
        starttime = clock();
        for (testnum = 0; testnum < numtests; testnum++) {
            for (int i = 0; i < n; i++) {
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
    srand(time(NULL));    
    //test_maxsum();
    //test_sort();
    //gensets(4,22);
    //gensets2(4,22);
    //genshuf(4,22);
    //printf("RAND_MAX: %d\n", RAND_MAX);
    //printf("big rand: %"PRId64"\n", bigrand());
    //int x[16] = {0,12,20,15,29,23,17,22,35,40,26,51,19};
    //show_heap(x, 12);
    //x[13] = 13;
    //siftup(x, 13);
    //show_heap(x, 13);
    int x[16] = {0,12,20,15,29,23,17,22,35,40,26,51,19};
    show_heap(x, 12);
    x[1] = 18; 
    siftdown(x, 12);
    show_heap(x, 12);
}


