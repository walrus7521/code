#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void grid_show(int rows, int cols, int p[][cols], char *name) {
    int i, j;
    printf("graph: %s\n", name);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) 
            printf("%d\t", p[i][j]);
        printf("\n"); 
    }
    printf("\n");
}

void row_major(int rows, int cols, int a[][cols])
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d %d\n", i, j);
        }
        printf("\n");
    }
}

void col_major(int rows, int cols, int a[][cols])
{
    int i, j;
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            printf("%d %d\n", i, j);
        }
        printf("\n");
    }
}

void snake(int rows, int cols, int a[][cols])
{
    int r, c, k, dir = 1;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            k = c;
            if (dir < 0) {
                k = cols-c-1; //j + (cols+1+j) * ((i)%2);
            }
            printf("%d %d\n", r, k);
        }
        dir *= -1;
        printf("\n");
    }
}

void traversals()
{
    int s[][4] = { {  1,  2,  3,  4 }, 
                   {  5,  6,  7,  8 }, 
                   {  9, 10, 11, 12 }, 
                   { 13, 14, 15, 16 } };

    //col_major(4,4,s);
    //row_major(4,4,s);
    snake(4,4,s);
    grid_show(4,4,s,"snake");
 }

int main()
{
    traversals();
}
