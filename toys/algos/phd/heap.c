#include <stdio.h>

int N = 0;
int A[32];

void perc_up(int k)
{
    int v;
    v = A[k]; A[0] = 99999;
    while (A[k/2] <= v) {
        A[k] = A[k/2];
        k /= 2;
    }
    A[k] = v;
}

void perc_down(int k)
{
    int j, v;
    v = A[k];
    while (k <= N/2) {
        j = 2*k;
        if (j < N & A[j] < A[j+1]) j++;
        if (v >= A[j]) break;
        A[k] = A[j]; k = j;
    }
    A[k] = v;
}

void insert(int x)
{
    A[++N] = x;
    perc_up(N);
}

int deletemax()
{
    int x = A[1];
    N--;
    A[1] = A[N];
    perc_down(1);
    return x;
}

void show()
{
    int i, lvl;
     for (i = 1; i <= N; i++) {
        printf("[%d]  ", A[i]);
    }
    printf("\n");
}

int a[15] = {22,5,3,4,8,2,7,6,9,11,10,33,20,12,55};
int main()
{
    int i;
    for (i = 0; i < 15; i++) {
        insert(a[i]);
    }
    show();
    while (N) {
        i = deletemax();
        printf("max = %d\n", i);
    }
    return 0;
}
