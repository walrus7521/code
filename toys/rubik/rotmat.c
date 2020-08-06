#include <stdio.h>

#define N 3

int mat[N][N] = { 
        { 1, 2, 3 }, 
        { 4, 5, 6 }, 
        { 7, 8, 9 }
    }; 

void show()
{
    int r, c;
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            printf("%d ", mat[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void rot() // clockwise
{
    int temp;
    int r, c;
    for (r = 0; r < N/2; r++) {
        for (c = 0; c < N; c++) {
            temp = mat[r][c];
            mat[r][c] = mat[r][N-c-1];
            mat[c][N-r-1] = mat[N-r-1][N-c-1];
            mat[N-r-1][N-c-1] = mat[N-c-1][r];
            mat[N-c-1][r] = temp;
        }
    }
}

int main()
{
    show();
    rot();
    show();
}


