#include <stdio.h>
#include "linalg.h"

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

int main()
{
    int a[] = {1,2,3,4};
    int b[] = {5,6,7,8};
    int sum = dotProduct(a, b, 4);
    printf("sum: %d\n", sum);
}
