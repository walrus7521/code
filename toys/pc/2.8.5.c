/* stack 'em up
 *
 * note: arrays are counted from 1..52 inclusive
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define dprintf printf */
#define dprintf(...)

char *vdeck[] = { " ", 
            "2 of Clubs", "3 of Clubs", "4 of Clubs", "5 of Clubs", "6 of Clubs", "7 of Clubs", "8 of Clubs", 
            "9 of Clubs", "10 of Clubs", "Jack of Clubs", "Queen of Clubs", "King of Clubs", "Ace of Clubs",
            "2 of Diamonds", "3 of Diamonds", "4 of Diamonds", "5 of Diamonds", "6 of Diamonds", "7 of Diamonds", 
            "8 of Diamonds", "9 of Diamonds", "10 of Diamonds", "Jack of Diamonds", "Queen of Diamonds", 
            "King of Diamonds", "Ace of Diamonds", "2 of Hearts", "3 of Hearts", "4 of Hearts", "5 of Hearts", 
            "6 of Hearts", "7 of Hearts", "8 of Hearts", "9 of Hearts", "10 of Hearts", "Jack of Hearts", 
            "Queen of Hearts", "King of Hearts", "Ace of Hearts", "2 of Spades", "3 of Spades", "4 of Spades", 
            "5 of Spades", "6 of Spades", "7 of Spades", "8 of Spades", "9 of Spades", "10 of Spades", 
            "Jack of Spades", "Queen of Spades", "King of Spades", "Ace of Spades" };

char *deck[] = {" ", "2c","3c","4c","5c","6c","7c","8c","9c","tc","jc","qc","kc","ac",
                     "2d","3d","4c","5d","6d","7d","8d","9d","td","jd","qd","kd","ad",
                     "2h","3h","4h","5h","6h","7h","8h","9h","th","jh","qh","kh","ah",
                     "2s","3s","4s","5s","6s","7s","8s","9s","ts","js","qs","ks","as"};

void reorder(int *a, int *b, int *c)
{
    int i, j;
    for (i = 1; i <= 52; i++) {
        j = b[i];
        c[i] = a[j];
    }
}

void show(int *a)
{
    int i, j;
    for (i = 1; i <= 52; i++) {
        j = a[i];
        dprintf("%d => %s\n", j, vdeck[j]);
        printf("%s\n", vdeck[j]);
    }
}

int **alloc2d(int rows, int cols)
{
    int **arr2d;
    int i, j;
    /* printf("alloc2d: rows %d, cols %d\n", rows, cols); */
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
    /* printf("dealloc2d: rows %d\n", rows); */
    for (i = 0; i < rows; i++) free(arr2d[i]);
    free(arr2d);
}

void show_in(int *a)
{
    int i;
    for (i = 1; i <= 52; i++) printf("%d ", a[i]);
    printf("\n");
}

void zero_it(int *a, int len)
{
    int i;
    for (i = 0; i < len; i++) a[i] = 0;
}

void copy_to(int *a, int *b, int len)
{
    int i;
    for (i = 0; i <= len; i++) a[i] = b[i];
}

int main()
{
    int i, j, ncases = 0, nshuffles = 0, shuffle;
    int tmp[54], *in, *out, *to, nrows, ncols = 54;
    char line[256];
    int **arr2d;
    scanf("%d\n", &ncases);
    dprintf("num cases %d\n", ncases);
    if (ncases <= 0) return 0;
    for (i = 0; i < ncases; i++) {
        scanf("%d\n", &nshuffles);
        dprintf("num shuffles %d\n", nshuffles);
        nrows = ncases+2;
        arr2d = alloc2d(nrows, ncols);
        for (j = 1; j <= nshuffles; j++) {
            memset(line, '\0', 256);
            fgets(line, 256, stdin);
            dprintf("%s", line);
            sscanf(line, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
                   "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 
                &arr2d[j][ 1], &arr2d[j][ 2], &arr2d[j][ 3], &arr2d[j][ 4], &arr2d[j][ 5], &arr2d[j][ 6], 
                &arr2d[j][ 7], &arr2d[j][ 8], &arr2d[j][ 9], &arr2d[j][10], &arr2d[j][11], &arr2d[j][12], &arr2d[j][13],
                &arr2d[j][14], &arr2d[j][15], &arr2d[j][16], &arr2d[j][17], &arr2d[j][18], &arr2d[j][19], &arr2d[j][20], 
                &arr2d[j][21], &arr2d[j][22], &arr2d[j][23], &arr2d[j][24], &arr2d[j][25], &arr2d[j][26], &arr2d[j][27], 
                &arr2d[j][28], &arr2d[j][29], &arr2d[j][30], &arr2d[j][31], &arr2d[j][32], &arr2d[j][33], &arr2d[j][34], 
                &arr2d[j][35], &arr2d[j][36], &arr2d[j][37], &arr2d[j][38], &arr2d[j][39], &arr2d[j][40], &arr2d[j][41], 
                &arr2d[j][42], &arr2d[j][43], &arr2d[j][44], &arr2d[j][45], &arr2d[j][46], &arr2d[j][47], &arr2d[j][48], 
                &arr2d[j][49], &arr2d[j][50], &arr2d[j][51], &arr2d[j][52]);
            /* show_in(arr2d[j]); */
        }
        in = arr2d[0];
        out = tmp;
        for (j = 1; j <= nshuffles; j++) {
            zero_it(out, 52);
            scanf("%d\n", &shuffle);
            /* printf("shuffle[%d] => %d\n", j, shuffle); */
            to = arr2d[shuffle];
            reorder(in, to, out);
            copy_to(in, out, 52);
            out = tmp;
        }
        show(out);
        dealloc2d(arr2d, nrows);
    }
    return 0;
}

