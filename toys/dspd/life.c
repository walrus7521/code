#include "common.h"
#include "life.h"

void usage()
{
    printf("a.out <file name>\n");
}

void Initialize(Grid map, FILE *in)
{
    int row, col;
    printf("game of life: rows %d, cols %d\n", MAXROW, MAXCOL);
    for (row = 0; row <= MAXROW; ++row)
        for (col = 0; col <= MAXCOL; ++col)
            map[row][col] = DEAD;
    printf("each line is a coordinate pair for a living cell, terminate with (0,0)\n");
    fscanf(in, "%d %d", &row, &col);
    while (row != 0 || col != 0) {
        if (row >= 1 && row <= MAXROW && col >= 1 && col <=MAXCOL)
            map[row][col] = ALIVE;
        else
            printf("values out of range\n");
        fscanf(in, "%d %d", &row, &col);
    }
    while (getchar() != '\n') ; // discard remaining chars
}

void CopyMap(Grid map, Grid newmap)
{
    int row, col;
    for (row = 0; row <= MAXROW; ++row)
        for (col = 0; col <= MAXCOL; ++col)
            map[row][col] = newmap[row][col];
}

void WriteMap(Grid map)
{
    int row, col;
    putchar('\n');
    putchar('\n');
    for (row = 1; row <= MAXROW; ++row) {
        for (col = 1; col <= MAXCOL; ++col)
            if (map[row][col] == ALIVE)
                putchar('*');
            else
                putchar('-');
        putchar('\n');
    }
}

Boolean UserSaysYes()
{
    int c;
    //printf(" more gens (y,n)? ");
    do {
        while ((c = getchar()) == '\n') return 1;
        //if (c == 'y' || c == 'Y' || c == 'n' || c == 'N') {
        //    printf("returning from user says y/n\n");
        //    return (c == 'y' || c == 'Y');
        //}
        //printf("please enter either y or n\n");
    } while (1);
}

int NeighborCount(Grid map, int row, int col)
{
    int i, j, count=0;
    for (i = row-1; i <= row+1; ++i) {
        for (j = col-1; j <= col+1; ++j) {
            if (map[i][j] == ALIVE) count++;
        }
    }
    if (map[row][col] == ALIVE) count--;
    return count;
}

int main(int argc, char *argv[])
{
    int row, col;
    Grid map;
    Grid newmap;
    FILE *in;
    int i;

    //for (i = 0; i < argc; ++i) {
    //    printf("arg[%d] = %s\n", i, argv[i]);
    //}
    if (argc != 2) {
        usage();
        return -1;
    }

    in = fopen(argv[1], "rb");
    if (in == NULL) {
        printf("file not found\n");
        return -1;
    }
    Initialize(map, in);
    WriteMap(map);
    printf("press enter to continue...");
    while (getchar() != '\n') ;

    do {
        for (row = 1; row <= MAXROW; ++row) {
            for (col = 1; col <= MAXCOL; ++col) {
                switch (NeighborCount(map,row,col)) {
                    case 0:
                    case 1:
                        newmap[row][col] = DEAD;
                        break;
                    case 2:
                        newmap[row][col] = map[row][col];
                        break;
                    case 3:
                        newmap[row][col] = ALIVE;
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        newmap[row][col] = DEAD;
                        break;
                }

            }
        }
        CopyMap(map, newmap);
        WriteMap(map);
    } while (UserSaysYes());

    return 0;
}
