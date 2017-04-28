#include <stdio.h>
#include <math.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) > (b)) ? (b) : (a))

void process(int i, int j)
{
    printf("i = %d, j = %d\n", i, j);
}

void row_major(int n, int m)
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            process(i, j);
}

void column_major(int n, int m)
{
    int i, j;
    for (j = 1; j <= m; j++)
        for (i = 1; i <= n; i++)
            process(i, j);
}

void snake_order(int n, int m)
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            process(i, j + (m+1-2*j) * ((i+1) % 2));

}

void diagonal_order(int n, int m)
{
    int d, j;
    int pcount;
    int height;

    for (d = 1; d <= (m+n-1); d++) {
        height = 1 + max(0, d-m);
        pcount = min(d, (n-height+1));
        for (j = 0; j < pcount; j++)
                process(min(m,d)-j, height+j);
    }
}

void hex_to_geo(int xh, int yh, double r, double *xg, double *yg)
{
    *yg = (2.0 * r) * xh * (sqrt(3)/2.0);
    *xg = (2.0 * r) * xh * (1.0/2.0) + (2.0 * r) * yh;
}

void geo_to_hex(double xg, double yg, double r, double *xh, double *yh)
{
    *xh = (2.0/sqrt(3)) * yg / (2.0 * r);
    *yh = (xg - (2.0 * r) * (*xh) * (1.0/2.0)) / (2.0 * r);
}

void array_to_hex(int xa, int ya, int *xh, int *yh)
{
    *xh = xa;
    *yh = ya - xa + ceil(xa/2.0);
}

void hex_to_array(int xh, int yh, int *xa, int *ya)
{
    *xa = xh;
    *ya = yh + xh - ceil(xh/2.0);
}

int test_coords()
{
    //row_major(3, 3);
    //column_major(3, 3);
    //snake_order(3, 3);
    diagonal_order(3, 3);
    return 0;
}

