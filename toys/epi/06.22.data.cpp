#include <cstdio>
#include <cstdlib>

using namespace std;

int **malloc2d(int r, int c)
{ 
    int i;
    int **t = (int **) malloc(r * sizeof(int *));
    for (i = 0; i < r; i++) {
        t[i] = (int *) malloc(c * sizeof(int));
    }
    return t;
}

enum {NORTH, SOUTH, EAST, WEST};
void print_spiral(int **a, int n) {
    int dir = EAST, spaces = n;
    int row=0, col=0, r, c;
    for (int i = 0; i < n*n; i+=spaces) {
        switch (dir) {
        case NORTH:
            //printf("NORTH: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            for (r = row; r > row-spaces; --r) {
                printf("%02d ", a[r][col]);
            }
            row -= spaces;
            row++;
            col++;
            dir = EAST;
            break;
        case SOUTH:
            //printf("SOUTH: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            for (r = row; r < row+spaces; ++r) {
                printf("%02d ", a[r][col]);
            }
            row += spaces;
            row--;
            col--;
            dir = WEST;
            break;
        case EAST:
            //printf(" EAST: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            for (c = col; c < col+spaces; ++c) {
                printf("%02d ", a[row][c]);
            }
            col += spaces;
            row++;
            col--;
            spaces--;
            dir = SOUTH;
            break;
        case WEST:
            //printf(" WEST: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            for (c = col; c > col-spaces; --c) {
                printf("%02d ", a[row][c]);
            }
            col -= spaces;
            row--;
            col++;
            spaces--;
            dir = NORTH;
            break;
        }
        if (spaces == 0) {
            break;
        }
    }
    printf("\n");
}

void print_square(int **a, int n) {
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%02d ", a[i][j]);
        }
        //printf("\n");
    }
    printf("\n");
}

void fill2x2(int **a) {
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
}

void fill3x3(int **a) {
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[1][0] = 4;
    a[1][1] = 5;
    a[1][2] = 6;
    a[2][0] = 7;
    a[2][1] = 8;
    a[2][2] = 9;
}

void fill4x4(int **a) {
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[0][3] = 4;
    a[1][0] = 5;
    a[1][1] = 6;
    a[1][2] = 7;
    a[1][3] = 8;
    a[2][0] = 9;
    a[2][1] = 10;
    a[2][2] = 11;
    a[2][3] = 12;
    a[3][0] = 13;
    a[3][1] = 14;
    a[3][2] = 15;
    a[3][3] = 16;
}

void fill5x5(int **a) {
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[0][3] = 4;
    a[0][4] = 5;
    a[1][0] = 6;
    a[1][1] = 7;
    a[1][2] = 8;
    a[1][3] = 9;
    a[1][4] = 10;
    a[2][0] = 11;
    a[2][1] = 12;
    a[2][2] = 13;
    a[2][3] = 14;
    a[2][4] = 15;
    a[3][0] = 16;
    a[3][1] = 17;
    a[3][2] = 18;
    a[3][3] = 19;
    a[3][4] = 20;
    a[4][0] = 21;
    a[4][1] = 22;
    a[4][2] = 23;
    a[4][3] = 24;
    a[4][4] = 25;
}

void fill6x6(int **a) {
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[0][3] = 4;
    a[0][4] = 5;
    a[0][5] = 6;
    a[1][0] = 7;
    a[1][1] = 8;
    a[1][2] = 9;
    a[1][3] = 10;
    a[1][4] = 11;
    a[1][5] = 12;
    a[2][0] = 13;
    a[2][1] = 14;
    a[2][2] = 15;
    a[2][3] = 16;
    a[2][4] = 17;
    a[2][5] = 18;
    a[3][0] = 19;
    a[3][1] = 20;
    a[3][2] = 21;
    a[3][3] = 22;
    a[3][4] = 23;
    a[3][5] = 24;
    a[4][0] = 25;
    a[4][1] = 26;
    a[4][2] = 27;
    a[4][3] = 28;
    a[4][4] = 29;
    a[4][5] = 30;
    a[5][0] = 31;
    a[5][1] = 32;
    a[5][2] = 33;
    a[5][3] = 34;
    a[5][4] = 35;
    a[5][5] = 36;
}

void fill7x7(int **a) {
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[0][3] = 4;
    a[0][4] = 5;
    a[0][5] = 6;
    a[0][6] = 7;
    a[1][0] = 8;
    a[1][1] = 9;
    a[1][2] = 10;
    a[1][3] = 11;
    a[1][4] = 12;
    a[1][5] = 13;
    a[1][6] = 14;
    a[2][0] = 15;
    a[2][1] = 16;
    a[2][2] = 17;
    a[2][3] = 18;
    a[2][4] = 19;
    a[2][5] = 20;
    a[2][6] = 21;
    a[3][0] = 22;
    a[3][1] = 23;
    a[3][2] = 24;
    a[3][3] = 25;
    a[3][4] = 26;
    a[3][5] = 27;
    a[3][6] = 28;
    a[4][0] = 29;
    a[4][1] = 30;
    a[4][2] = 31;
    a[4][3] = 32;
    a[4][4] = 33;
    a[4][5] = 34;
    a[4][6] = 35;
    a[5][0] = 36;
    a[5][1] = 37;
    a[5][2] = 38;
    a[5][3] = 39;
    a[5][4] = 40;
    a[5][5] = 41;
    a[5][6] = 42;
    a[6][0] = 43;
    a[6][1] = 44;
    a[6][2] = 45;
    a[6][3] = 46;
    a[6][4] = 47;
    a[6][5] = 48;
    a[6][6] = 49;
}

int main()
{
    int n = 2;
    int **a = malloc2d(n,n);
    switch (n) {
        case 2: fill2x2(a); break;
        case 3: fill3x3(a); break;
        case 4: fill4x4(a); break;
        case 5: fill5x5(a); break;
        case 6: fill6x6(a); break;
        case 7: fill7x7(a); break;
    }
    //print_square(a, n);
    //printf("\n");
    print_spiral(a, n);
    return 0;
}

