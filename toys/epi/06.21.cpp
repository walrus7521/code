#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>

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

bool hasDuplicate(vector<int> A) {
    return true;
}

void show_sudoku(vector<vector<int> > A) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void init_sudoku(vector<vector<int> >& A) {
    A.push_back({ 1,1,1, 2,2,2, 3,3,3 });
    A.push_back({ 1,1,1, 2,2,2, 3,3,3 });
    A.push_back({ 1,1,1, 2,2,2, 3,3,3 });

    A.push_back({ 4,4,4, 5,5,5, 6,6,6 });
    A.push_back({ 4,4,4, 5,5,5, 6,6,6 });
    A.push_back({ 4,4,4, 5,5,5, 6,6,6 });
    
    A.push_back({ 7,7,7, 8,8,8, 9,9,9 });
    A.push_back({ 7,7,7, 8,8,8, 9,9,9 });
    A.push_back({ 7,7,7, 8,8,8, 9,9,9 });
}

void print_spiral_outer_ring(int **a, int size, int n)
{
    int r, c, start=size-n, end=n-1;
    //printf("outer: size=%d, n=%d, start=%d, end=%d\n", size, n, start, end);
    if (start == end) {
        printf("%d ", a[start][end]);
        return;
    }
    for (c = start; c < end; ++c) { // east
        printf("%02d ", a[start][c]);
    }
    for (r = start; r < end; ++r) { // south
        printf("%02d ", a[r][end]);
    }
    for (c = end; c > start; --c) { // west
        printf("%02d ", a[end][c]);
    }
    for (r = end; r > start; --r) { // north
        printf("%02d ", a[r][start]);
    }
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
    int n = 9;
    int **a = malloc2d(n,n);
    vector<vector<int> > A;
    init_sudoku(A);
    show_sudoku(A);
    //for (int i = n; i > n/2; --i) {
    //    print_spiral_outer_ring(a, n, i);
    //}
    printf("\n");
    return 0;
}

