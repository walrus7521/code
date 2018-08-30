#include <stdio.h>
#include <math.h>
#include "coords.h"

int dense_layers(double w, double h, double r)
{
    double gap; /* distance between layers */
    if ((2*r) > h) return (0);
    gap = 2.0 * r * (sqrt(3)/2.0);
    return (1 + floor((h-2.0*r)/gap));
}

int plates_per_row(int row, double w, double r)
{
    int plates_per_full_row;
    plates_per_full_row = floor(w/(2*r));
    if ((row % 2) == 0) return (plates_per_full_row);
    if (((w/(2*r))-plates_per_full_row) >= 0.5) /* odd row full */
        return (plates_per_full_row);
    else
        return (plates_per_full_row - 1);
}

int plates_on_top(int xh, int yh, double w, double l, double r)
{
    int number_on_top = 0;  /* total plates on top */
    int layers;             /* number of rows in grid */
    int rowlength;          /* number of plates in row */
    int row;                /* counter */
    int xla, yla, xra, yra; /* array coordinates */

    layers = dense_layers(w, l, r);
    for (row = xh+1; row < layers; row++) {
        rowlength = plates_per_row(row, w, r) - 1;
        hex_to_array(row, yh-row, &xla, &yla);
        if (yla < 0) yla = 0;                 /* left boundary */
        hex_to_array(row, yh, &xra, &yra);
        if (yra > rowlength) yra = rowlength; /* right boundary */
        number_on_top += yra-yla+1;
    }

    return (number_on_top);
}

int dense_plates(double w, double l, double r)
/*
 * How many radius r plates fit in a hexagonal-lattice packed w*h box?
 */
{
    int layers;
    layers = dense_layers(w, l, r);
    return (ceil(layers/2.0) * plates_per_row(0, w, r) +
            floor(layers/2.0) * plates_per_row(1, w, r));
}

int grid_plates(double w, double h, double r)
/*
 * How many radius r plates fit in a grid-lattice packed w*h box?
 */
{
    int layers;
    layers = floor(h/(2*r));
    return (layers * plates_per_row(0, w, r));
}

int main()
{
    return 0;
}
