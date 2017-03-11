#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int nelems = 0;
int A[32];
int max = 32;

#define exchg(A, B) { int t = A; A = B; B = t; }

void perc_up(int k, int x)
{
    while (k > 1 && x > A[k/2]) {
        A[k] = A[k/2];
        k /= 2;
    }
    A[k] = x;
}

void perc_down(int k)
{
    int c;
    c = 2 * k;
    while (c < nelems) {
        if (c < nelems-1 && A[c] < A[c+1])
            c++; 
        if (A[k] < A[c]) {
          exchg(A[k], A[c])
          k = c;
          c = 2 * c;
        } else {
            break;
        }
        c++;
    }
}

void insert(int x)
{
    int k = ++nelems;
    perc_up(k, x);
}

int deletemax()
{
    int x = A[1];
    nelems--;
    exchg(A[1], A[nelems])
    perc_down(1);
    return x;
}

int level[]  = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
int space[] = {0, 46, 25, 12, 6, 1};
void show()
{
    int i, lvl, j;
    int height = 5;
    for (lvl = 0; lvl < 10; lvl++) {
        for (i = 1; i <= level[lvl-1]; i++) {
            if (i + lvl > nelems) goto end;
            printf("<[%d]>  ", A[lvl+i]);
        }
        printf("\n");
    }
end:
    return;
}

void show2()
{
    int i, lvl;
     for (i = 1; i <= nelems; i++) {
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
    show2();
    show();
    while (nelems) {
        i = deletemax();
        printf("max = %d\n", i);
    }
    return 0;
}
