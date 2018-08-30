#include <stdio.h>
#include <stdlib.h>

#define PAD 2
unsigned int **grid;

void init_grid(unsigned long nrows, unsigned long ncols)
{
    int row, col;
    grid = (unsigned int **) malloc((nrows+PAD) * sizeof(unsigned int *));
    for (row = 0; row < nrows+PAD; row++) {
        grid[row] = (unsigned int *) malloc((ncols+PAD) * sizeof(unsigned int));
    }
    for (row = 0; row < nrows+PAD; row++) {
        for (col = 0; col < ncols+PAD; col++) {
            grid[row][col] = '.';
        }
    }
}

void free_grid(unsigned long nrows, unsigned long ncols)
{
    int row, col;
    for (row = 0; row < nrows+PAD; row++) {
        free(grid[row]);
    }
    free(grid);
}

void show_grid(unsigned long nrows, unsigned long ncols)
{
    int row, col;
    for (row = 1; row <= nrows; row++) {
        printf("[%d]: ", row);
        for (col = 1; col <= ncols; col++) {
            printf("%c", grid[row][col]);
        }
        printf("\n");
    }
}

void process_grid(unsigned long fieldno, unsigned long nrows, unsigned long ncols)
{
    unsigned long row, col, count;
    if (fieldno > 1) printf("\n");
    printf("Field #%ld:\n", fieldno);
    for (row = 1; row <= nrows; row++) {
        for (col = 1; col <= ncols; col++) {
            count = 0;
            /* printf("grid[1][%ld] = %c\n", col, grid[1][col]); */
            if (grid[row-1][col-1] == '*') count++;
            if (grid[row-1][col]   == '*') count++;
            if (grid[row-1][col+1] == '*') count++;
            if (grid[row][col-1] == '*') count++;
            if (grid[row][col+1] == '*') count++;
            if (grid[row+1][col-1] == '*') count++;
            if (grid[row+1][col]   == '*') count++;
            if (grid[row+1][col+1] == '*') count++;
            if (grid[row][col]   == '*') {
                printf("%c", '*');
            } else {
                printf("%ld", count);
            }
        }
        printf("\n");
    }
}

int get_grid(unsigned long nrows, unsigned long ncols)
{
    int row, col, toggle_row;
    char c;
    for (row = 1; row <= nrows; row++) {
        for (col = 1; col <= ncols+1; col++) {
            c = getchar();
            if (c != '.' && c != '*') {
                /* printf("what is it c = %c, x = %x\n", c, c); */
                continue;
            }
            /* putchar(c); */
            grid[row][col] = c;
        }
    }
    return 0;
}

void suck_nlines(unsigned long nrows)
{
    unsigned long row;
    char buffer[102];
    printf("sucking lines\n");
    for (row = 0; row < nrows; row++) {
        fgets(buffer, sizeof(buffer), stdin);
    }
}

int main()
{
    long nrows, ncols, fieldno = 0;
    /* 0. init mines grid to all dots */
    nrows = ncols = 0;
    while (EOF != scanf("%ld %ld\n", &nrows, &ncols)) {
        /* printf("got %ld rows and %ld cols\n", nrows, ncols); */
        /* 1. read rows, cols <= 100 */
        if (ncols < 0 || ncols > 100) {
            suck_nlines(nrows);
            continue;
        }
        if (nrows == 0 || ncols == 0)
            break;
        init_grid(nrows, ncols);
        /* 2. increment the Field # */
        fieldno++;
        get_grid(nrows, ncols);
        process_grid(fieldno, nrows, ncols);
        /* printf("\n"); */
        /* show_grid(nrows, ncols); */
        free_grid(nrows, ncols);
        nrows = ncols = 0;
        /* printf("\n"); */
    }
    return 0;
}
