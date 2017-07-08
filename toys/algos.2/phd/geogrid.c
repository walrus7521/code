#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

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
    int i, j, k;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            k = j + (cols-2*j-1) * (i%2);
            printf("%d %d\n", i, k);
        }
        printf("\n");
    }
}

// BUGBUG
void diagonal_orig(int rows, int cols, int a[][cols])
{
    int d, j, k, hgt, pcnt, l1, l2;
    for (d = 0; d < rows+cols; d++) {
        //printf("d1: %d\n", d);
        hgt = 1 + max(0,(d-cols));
        printf("hgt: %d\n", hgt);
        //printf("d2: %d\n", d);
        //hgt = max(0,(d-cols));
        pcnt = min(d, (rows-hgt+1));
        printf("pcnt: %d\n", pcnt);
        for (j = 0; j < pcnt; j++) {
            //printf("cols: %d, d: %d\n", cols, d);
            l1 = min(cols,d)-j;
            l2 = hgt+j;
            printf("%d %d\n", l1, l2);
        }
        printf("\n");
    }
}

void diagonal(int rows, int cols, int a[][cols])
{
    int d, j, k;
    int hgt; // row of lowest point
    int pcnt; // points on diagonal
    int l1, l2; // final coordinates

    for (d = 0; d < rows+cols; d++) {
        printf("d-cols: %d\n", (d-cols));
        hgt = max(0,(d-cols));
        printf("hgt: %d\n", hgt);
        //hgt = max(0,(d-cols));
        pcnt = 1 + min(d, (rows-hgt+1));
        printf("pcnt: %d\n", pcnt);
        for (j = 0; j < pcnt; j++) {
            //printf("cols: %d, d: %d\n", cols, d);
            l1 = min(cols,d)-j;
            l2 = hgt+j;
            printf("%d %d\n", l1, l2);
        }
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
    //snake(4,4,s);
    //diagonal_orig(4,4,s);
    diagonal(4,4,s);
    grid_show(4,4,s,"snake");
 }

int main()
{
    traversals();
}
