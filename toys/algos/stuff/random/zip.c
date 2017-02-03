#include <stdio.h>
#include <stdlib.h>

void show(int zz[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("zz[%d] = %d\n", i, zz[i]);
    }
}

// iterative
int *zipi(int a[], int b[], int len)
{
    int i;
    int *c = calloc(2*len, sizeof(int));
    for (i = 0; i < len; i++) {
        c[2*i]   = a[i];
        c[2*i+1] = b[i];
    }
    return c;
}

// recursive
int z[256] = {0};
void zipr(int a[], int b[], int i, int len)
{
    if (len == 0) return;
    z[2*i] = a[i];
    z[2*i+1] = b[i];
    zipr(a, b, i+1, len-1);
}


int main()
{
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8};
    int *c;
    int len = 4;
    c = zipi(a, b, len);
    show(c, 2*len);

    printf("------------- now recursive\n");
    zipr(a, b, 0, len);
    show(z, 2*len);
    
}

