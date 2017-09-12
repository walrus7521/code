#pragma once

struct vector {
    float x, y, z;
};

struct matrix {
    struct vector row1;
    struct vector row2;
    struct vector row3;
};

void vector_show(struct vector *v);
void matrix_show(struct matrix *m);

