#ifndef POLY_H
#define POLY_H

#include "types.h"
#include "list.h"

typedef list polynomial;

typedef struct term {
    int coefficient;
    int degree;
} term;

status read_poly(polynomial *p_poly);
void write_poly(polynomial poly);
status add_poly(polynomial *p_poly1, polynomial *p_poly2);
void destroy_poly(polynomial *p_poly);


status traverse(list L, status (*p_func_f)());

#endif // POLY_H
