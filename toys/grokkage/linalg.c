#include <stdio.h>
#include "linalg.h"

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


