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
    int dir = EAST, spaces = n, k;
    int sign = 1;
    int row=0, col=0;
    for (int i = 0; i < n*n; i+=spaces) {
        switch (dir) {
        case NORTH:
            printf("NORTH: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            row -= spaces;
            dir = EAST;
            break;
        case SOUTH:
            printf("SOUTH: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            row += spaces;
            dir = WEST;
            break;
        case EAST:
            printf(" EAST: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            col += spaces;
            spaces--;
            if (i == 0) col--;
            dir = SOUTH;
            break;
        case WEST:
            printf(" WEST: %02d, spaces %d, row %d, col %d\n", i, spaces, row, col);
            col -= spaces;
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
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
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

int main()
{
    int n = 3;
    int **a = malloc2d(n,n);
    fill3x3(a);
    print_spiral(a, n);
    //print_square(a, n);
    return 0;
}

