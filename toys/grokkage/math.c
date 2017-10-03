#include <stdio.h>
#include <math.h>
#include "math.h"

double log_base_n(double x, double n)
{
    //logN (x) = logy (x) / logy (N)
    double lognX = log(x) / log(n);
    return lognX;
}

int dotProduct(int x[], int y[], int n) {
    int i, sum;
    sum = 0;
    for (i = 0; i < n; i++) sum += x[i]*y[i];
    return sum;
}

void vector_show(struct vector *v)
{
    printf("%f, %f, %f\n", v->x, v->y, v->z);
}

void matrix_show(struct matrix *m)
{
    vector_show(&m->row1);
    vector_show(&m->row2);
    vector_show(&m->row3);
}

#if 0
int main()
{
    int a[] = {1,2,3,4};
    int b[] = {5,6,7,8};
    int sum = dotProduct(a, b, 4);
    printf("sum: %d\n", sum);

    double n, x, h;
    n = 4;
    x = 64;
    h = log_base_n(x,n) + 1;
    printf("height of %.0f-way tree with %.0f nodes is %.0f\n", n, x, h);
}
#endif

