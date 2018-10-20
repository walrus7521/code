#include "poly.h"

status read_poly(polynomial *p_poly)
{
    int coef;
    int degree;

    if (ERROR == init_list(p_poly))
        return ERROR;

    do {
        printf("\t enter coeff, degree (0,0 when done): ");
        scanf("%d,%d", &coef, &degree);
        if (coef != 0)
            if (ERROR == term_insert(p_poly, coef, degree))
                return ERROR;
    } while (coef != 0|| degree != 0);
    return OK;
}

status write_term(term *p_term)
{
    printf(" + %dx^%d", p_term->coefficient, p_term->degree);
    return OK;
}

void write_poly(polynomial poly)
{
    traverse(poly, write_term);
}

status add_poly(polynomial *p_poly1, polynomial *p_poly2)
{
}

void destroy_poly(polynomial *p_poly)
{
}

int main()
{
}

