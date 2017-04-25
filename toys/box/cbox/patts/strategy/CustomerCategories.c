
#include <stdio.h>
#include "CustomerCategories.h"

/* In production code, all input should be validated and
2 the calculations secured upon entry of each function. */
double bronzePriceStrategy(double amount, double shipping)
{
    printf("bronze\n");
    return amount * 0.98 + shipping;
}

double silverPriceStrategy(double amount, double shipping)
{
    printf("silver\n");
    return amount * 0.95 + shipping;
}

double goldPriceStrategy(double amount, double shipping)
{
    /* Free shipping for gold customers. */
    printf("gold\n");
    return amount * 0.90;
}

