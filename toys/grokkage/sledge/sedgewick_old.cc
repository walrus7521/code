#include <stdio.h>
#include <string.h>
#include <math.h>

// sedgewick

#define MAXN 100

void arr_show(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) printf("%c ", a[i]);
    printf("\n");
}

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void bubsort(int a[], int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            if (a[i] > a[j]) {
                swap(a, i, j);
            }
        }
    }
}

void selsort(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (a[j] < a[min]) min = j;
        }
        swap(a, i, min);
    }
}

void inssort(int a[], int n)
{
    int i, j, v;
    for (i = 0; i < n; i++) {
        v = a[i]; j = i;
        while (a[j-1] > v) {
            a[j] = a[j-1]; j--;
        }
        a[j] = v;
    }
}

void indirect_sort(int a[], int p[], int n)
{
    int i, j, v;
    for (i = 0; i < n; i++) p[i] = i;
    for (i = 1; i < n; i++) {
        v = p[i]; j = i;
        while (a[p[j-1]] > a[v]) {
            p[j] = p[j-1];
            j--;
        }
        p[j] = v;
    }
}

unsigned int bits(unsigned int x, int k, int j)
{
    return ((x >> k) & ~(~0 << j));
}

void radix_exchange_sort(int a[], int l, int r, int b)
{
    int t, i, j;
    printf("radix: l:%d r:%d b:%d\n", l, r, b);
    if (r > l && b >= 0) {
    //if (r > l && b > 0) {
        i = l; j = r;
        while (j != i) {
            while (bits(a[i], b, l) == 0 && i < j) i++;
            while (bits(a[j], b, l) != 0 && j > i) j--;
            //printf("exchg: %d %d\n", i, j);
            t = a[i]; a[i] = a[j]; a[j] = t;
        }
        if (bits(a[r], b, l) == 0) j++;
        radix_exchange_sort(a, l, j-1, b-1);
        radix_exchange_sort(a, j, r, b-1);
    }
}

int partition(int a[], int l, int r)
{
    int i, j, v, t;
    v = a[r];
    i = l-1;
    j = r;
    for (;;) {
        while (a[++i] < v) ;
        while (a[--j] > v) ;
        if (i >= j) break;
        t = a[i]; a[i] = a[j]; a[j] = t;
    }
    t = a[i]; a[i] = a[r]; a[r] = t;
    return i;
}

void select_kth_largest(int a[], int l, int r, int k)
{
    int i;
    if (r > l) {
        i = partition(a, l, r);
        if (i > l+k-i) select_kth_largest(a, l, i-1, k);
        if (i < l+k-i) select_kth_largest(a, i+1, r, k-i);
    }
}

int smallest(int a[], int n)
{
    int i, min = 9999999, min_idx = -1;
    for (i = 0; i < n; i++) {
        if (a[i] < min) {
            min_idx = i;
            min = a[i];
        }
    }
    return min_idx;
}

#define MIN(a, b) (((a)>(b)) ? (b) : (a))

int tape_in[] = {'A','S','O','R','T','I','N','G','A','N','D','M','E','R','G','I','N','G','E','X','A','M','P','L','E'};
int tape_out[32] = {0};
void three_way_merge_sort()
{
    int n, t1, t2, t3, j;
    int len = sizeof(tape_in) / sizeof(tape_in[0]);
    int tape1[32] = {0};
    int tape2[32] = {0};
    int tape3[32] = {0};
    int tape4[32] = {0};
    int tape5[32] = {0};
    int tape6[32] = {0};
    printf("len: %d\n", len);
    for (n = 0; n < len; n++) printf("%c ", tape_in[n]);
    printf("\n");
    // fix this loop to manage the non-multiple of 3 size of input
    // this should be reflected on the outputs: tape1, tape2, tape3
    for (j = n = 0; n < len; n+=9) {
        printf("n: %d n/3: %d j: %d min: %d\n", n, n/3, j, MIN(n,n/3+3));
        for (t1 = n/3; t1 < n/3+3; t1++, j++) {
            tape1[t1] = tape_in[j];
        }
        //arr_show(&tape1[n/3], 3);
        selsort(&tape1[n/3], 3);
        arr_show(&tape1[n/3], 3);
        for (t2 = n/3; t2 < n/3+3; t2++, j++) {
            tape2[t2] = tape_in[j];
        }
        //arr_show(&tape2[n/3], 3);
        selsort(&tape2[n/3], 3);
        arr_show(&tape2[n/3], 3);
        for (t3 = n/3; t3 < n/3+3; t3++, j++) {
            tape3[t3] = tape_in[j];
        }
        //arr_show(&tape3[n/3], 3);
        selsort(&tape3[n/3], 3);
        arr_show(&tape3[n/3], 3);
    }
    arr_show(tape1, n);
    arr_show(tape2, n);
    arr_show(tape3, n);
    printf("start merge\n");
    int first = 1;
    int small = -1; // index of tape with smallest value
    // now ready to merge the sorted sub-blocks
    // process the 1st 3x3 block into tape4
    // process the 2nd 3x3 block into tape5
    // process the 3rd 3x3 block into tape6
    for (n = 0; n < 9; n++) {
        int s1, s2, s3;
        int tmp[3];
        if (first == 1) {
            tmp[0] = tape1[n];
            tmp[1] = tape2[n];
            tmp[2] = tape3[n];
            first = 0;
        } else {
            switch (small) {
                case 0: tmp[small] = tape1[n]; break;
                case 1: tmp[small] = tape2[n]; break;
                case 2: tmp[small] = tape3[n]; break;
            }
        }
        small = smallest(tmp, 3);
        tape4[n] = tmp[small];
        printf("%c %c %c => %c\n", tmp[0], tmp[1], tmp[2], tmp[small]);
    }
    arr_show(tape4, n);

}
#if 1
int main()
{
    int n=0, i; //, a[MAXN+1];
    //while (scanf("%d", &a[n]) != EOF) n++;
    int a[] = {'a','s','o','r','t','i','n','g','e','x','a','m','p','l','e'};
    int p[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    int k[] = {1,73,25,87,42,54,66,28};

    n = 15;
    //selsort(a, n);
    //inssort(a, n);
    //bubsort(a, n);
    //bubsort(a, n);
    //radix_exchange_sort(a, 1, 14, 30);
    //for (i = 0; i < n; i++) printf("%c ", a[i]);
    //indirect_sort(a, p, n); for (i = 0; i < n; i++) printf("%c ", a[p[i]]);
    //printf("\n");

    //int select = 1;
    //select_kth_largest(k, 0, 7, select);
    //printf("k[select] = %d\n", k[select]);

    three_way_merge_sort();

}
#endif
