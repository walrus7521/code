#include <stdio.h>

#define NROWS 3
#define NCOLS 102
unsigned int grid[NROWS][NCOLS];

void init_grid()
{
    int row, col;
    for (row = 0; row < NROWS; row++) {
        for (col = 0; col < NCOLS; col++) {
            grid[row][col] = '.';
        }
    }
}

void show_grid(unsigned long ncols)
{
    int row, col;
    for (row = 0; row < NROWS; row++) {
        printf("[%d]: ", row);
        for (col = 1; col <= ncols; col++) {
            printf("%c", grid[row][col]);
        }
        printf("\n");
    }
}

void show_row(unsigned long ncols)
{
   unsigned long col;
   int count = 0;
   /* printf("process the row\n"); */
   for (col = 1; col <= ncols; col++) {
       count = 0;
       /* printf("grid[1][%ld] = %c\n", col, grid[1][col]); */
       if (grid[0][col-1] == '*') count++;
       if (grid[0][col]   == '*') count++;
       if (grid[0][col+1] == '*') count++;
       if (grid[1][col-1] == '*') count++;
       if (grid[1][col+1] == '*') count++;
       if (grid[2][col-1] == '*') count++;
       if (grid[2][col]   == '*') count++;
       if (grid[2][col+1] == '*') count++;
       if (grid[1][col]   == '*') {
           printf("%c", '*');
       } else {
           printf("%d", count);
       }
   }
   printf("\n");
}

void shift_rows(unsigned long ncols)
{
    unsigned long col;
    for (col = 0; col < NCOLS; col++) {
        grid[0][col] = grid[1][col];
        grid[1][col] = grid[2][col];
    }
}

void clear_last_row(unsigned long ncols)
{
    unsigned long col;
    for (col = 0; col < NCOLS; col++) {
        grid[NROWS-1][col] = '.';
    }
}

int getlines(unsigned long fieldno, unsigned long nrows, unsigned long ncols)
{
    int row, col, toggle_row;
    char c;
    if (fieldno > 1) printf("\n");
    printf("Field #%ld:\n", fieldno);
    for (row = 1; row <= nrows; row++) {
        toggle_row = ((row-1) % 2) + 1;
        /* printf("trow %d\n", toggle_row); */
        /* add 1 to loop to grab the carriage return */
        for (col = 1; col <= ncols+1; col++) {
            c = getchar();
            if (c != '.' && c != '*') {
                /* printf("what is it c = %c, x = %x\n", c, c); */
                continue;
            }
            /* putchar(c); */
            if (row == 1) grid[1][col] = c;
            else grid[2][col] = c;
        }
        /* show_grid(ncols); */
        /* printf("\n"); */
        if (row > 1) {
            show_row(ncols);
            shift_rows(ncols);
            clear_last_row(ncols);
        }
        /* printf("\n"); */
    }
    /* show_grid(ncols); */
    show_row(ncols);
    return 0;
}

void suck_nlines(unsigned long nrows)
{
    unsigned long row;
    char buffer[102];
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
        init_grid();
        /* 2. increment the Field # */
        fieldno++;
        getlines(fieldno, nrows, ncols);
        nrows = ncols = 0;
    }

    return 0;
}
