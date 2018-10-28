#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE    256
#define MAXWORDS    24
#define MAXLETTERS 128
#define dprintf printf
//#define dprintf(...)

char names[MAXWORDS][MAXLETTERS];
int found[MAXWORDS] = {0};

void init_names()
{
    int i, j;
    for (i = 0; i < MAXWORDS; i++)
        for (j = 0; j < MAXLETTERS; j++) names[i][j] = '\0';
}

int **alloc2d(int rows, int cols)
{
    int **arr2d;
    int i, j;
    arr2d = (int**) malloc(rows*sizeof(int*));
    for (i = 0; i < rows; i++) arr2d[i] = (int *) malloc(cols*sizeof(int));
    for (j = 0; j < cols; j++) /* initialize [0] to fresh deck.. */
        arr2d[0][j] = j;
    for (i = 1; i < rows; i++) for (j = 0; j < cols; j++) arr2d[i][j] = 0;
    return arr2d;
}

void dealloc2d(int **arr2d, int rows)
{
    int i;
    for (i = 0; i < rows; i++) free(arr2d[i]);
    free(arr2d);
}

void show_arr2d(int **arr, int rows, int cols)
{
    int i, j;
    dprintf("   ");
    for (i = 1; i <= cols; i++) dprintf("%2d ", i);
    dprintf("\n");
    for (i = 1; i <= rows; i++) {
        dprintf("%2d: ", i);
        for (j = 1; j <= cols; j++) {
            dprintf("%c  ", arr[i][j]);
        }
        dprintf("\n");
    }

}

int go_northwest(int **arr, int row, int col, char *word, int len)
{
    int i, k, found = 1;
    char c;
    for (k = 1, i = -1; k < len; k++, i--) {
        c = word[k];
        if (arr[row+i][col+i] != c) return 0;
    }
    return 1;
}
int go_north(int **arr, int row, int col, char *word, int len)
{
    int i, k, found = 1;
    char c;
    for (k = 1, i = -1; k < len; k++, i--) {
        c = word[k];
        if (arr[row+i][col] != c) return 0;
    }
    return 1;
}
int go_northeast(int **arr, int row, int col, char *word, int len)
{
    int i, j, k, found = 1;
    char c;
    for (k = 1, i = -1, j = 1; k < len; k++, i--, j++) {
        c = word[k];
        if (arr[row+i][col+j] != c) return 0;
    }
    return 1;
}
int go_east(int **arr, int row, int col, char *word, int len)
{
    int i, k, found = 1;
    char c;
    for (k = 1, i = 1; k < len; k++, i++) {
        c = word[k];
        if (arr[row][col+i] != c) return 0;
    }
    return 1;
}
int go_southeast(int **arr, int row, int col, char *word, int len)
{
    int i, k, found = 1;
    char c;
    for (k = 1, i = 1; k < len; k++, i++) {
        c = word[k];
        if (arr[row+i][col+i] != c) return 0;
    }
    return 1;
}
int go_south(int **arr, int row, int col, char *word, int len)
{
    int i, k, found = 1;
    char c;
    for (k = 1, i = 1; k < len; k++, i++) {
        c = word[k];
        if (arr[row+i][col] != c) return 0;
    }
    return 1;
}
int go_southwest(int **arr, int row, int col, char *word, int len)
{
    int i, j, k, found = 1;
    char c;
    for (k = 1, i = 1, j = -1; k < len; k++, i++, j--) {
        c = word[k];
        if (arr[row+i][col+j] != c) return 0;
    }
    return 1;
}
int go_west(int **arr, int row, int col, char *word, int len)
{
    int i, k, found = 1;
    char c;
    for (k = 1, i = -1; k < len; k++, i--) {
        c = word[k];
        if (arr[row][col+i] != c) return 0;
    }
    return 1;
}

int search(int **arr, int row, int col, char *word, int len)
{
    dprintf("search for %s from row %d col %d\n", word, row, col);
    if (arr[row-1][col-1] == word[1]) {
        if (go_northwest(arr, row, col, word, len)) return 1;
    }
    if (arr[row-1][col] == word[1]) {
        if (go_north(arr, row, col, word, len)) return 1;
    }
    if (arr[row-1][col+1] == word[1]) {
        if (go_northeast(arr, row, col, word, len)) return 1;
    }
    if (arr[row][col+1] == word[1]) {
        if (go_east(arr, row, col, word, len)) return 1;
    }
    if (arr[row+1][col+1] == word[1]) {
        if (go_southeast(arr, row, col, word, len)) return 1;
    }
    if (arr[row+1][col] == word[1]) {
        if (go_south(arr, row, col, word, len)) return 1;
    }
    if (arr[row+1][col-1] == word[1]) {
        if (go_southwest(arr, row, col, word, len)) return 1;
    }
    if (arr[row][col-1] == word[1]) {
        if (go_west(arr, row, col, word, len)) return 1;
    }
    return 0;
}


int main()
{
    int i, j, k, ncases = 0, len;
    int tmp[54], *in, *out, *to, nrows, ncols = 54, nr_names;
    char line[256], first_char;
    int **arr2d;
    scanf("%d\n", &ncases);
    dprintf("num cases %d\n", ncases);
    if (ncases <= 0) return 0;
    for (i = 0; i < ncases; i++) {
        scanf("%d\n", &nrows);
        scanf("%d\n", &ncols);
        dprintf("rows %d, cols %d\n", nrows, ncols);
        arr2d = alloc2d(nrows+2, ncols+2);
        for (i = 1; i <= nrows; i++) {
            fgets(line, MAXLINE, stdin);
            len = strlen(line);
            for (j = 1; j <= len; j++)
                arr2d[i][j] = toupper(line[j-1]);
        }
        scanf("%d\n", &nr_names);
        dprintf("nr names: %d\n", nr_names);
        init_names();
        for (i = 0; i < nr_names; i++) {
            fgets(names[i], MAXLETTERS, stdin);
            len = strlen(names[i]);
            names[i][len-1] = '\0'; /* chop of carriage return */
            for (j = 0; j < len-1; j++) names[i][j] = toupper(names[i][j]);
            dprintf("name[%d] = %s\n", i, names[i]);
        }
        show_arr2d(arr2d, nrows, ncols);
        for (i = 0; i < nr_names; i++) {
            first_char = names[i][0];
            for (j = 1; j <= nrows; j++) {
                for (k = 1; k <= ncols; k++) {
                    if (first_char == arr2d[j][k] && !found[i]) {
                        if (search(arr2d, j, k, names[i], strlen(names[i]))) {
                            found[i] = 1;
                            printf("%d %d\n", j, k);
                        }
                    }
                }
            }
        }
        for (i = 0; i < nr_names; i++) 
            dprintf("found[%d] = %d\n", i, found[i]);
        dealloc2d(arr2d, nrows+2);

    }
    return 0;
}

