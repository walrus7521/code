#include <stdio.h>

#define INVALID (-99)

void showBoard(int queenList[8])
{
    int row, col;
    printf("   0 1 2 3 4 5 6 7\n");
    for (row = 0; row < 8; row++) {
        printf("%d  ", row);
        for (col = 0; col < 8; col++) {
            if (queenList[col] == row) {
                printf("Q ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
}

int safeLocation(int row, int col, int queenList[8])
{
    int qRow, qCol;
    for (qCol = 0; qCol < col; ++qCol) {
        qRow = queenList[qCol];
        if (qRow == row) return 0;
        else if (qCol == col) return 0;
        else if ((qCol-qRow == col-row) || (qCol+qRow == col+row)) return 0;
    }
    return 1;
}

int placeQueens(int queenList[8], int col)
{
    int row;
    int foundLocation;

    if (col == 8) { // halting condition
        foundLocation = 1;
    } else {
        foundLocation = 0; // start at row 0
        row = 0;
        while (row < 8 && !foundLocation) {
            // check whether cell (row,col) is safe, if so,
            // assign row to queenList and call placeQueens()
            // for the next col; otherwise go to next row
            if (safeLocation(row, col, queenList) == 1) {
                queenList[col] = row;
                // recursive step, try to place queens in col+1 -> 7
                // !! **** calling for next column
                foundLocation = placeQueens(queenList, col+1);
            }
            // current row fails, try next row
            row++;
        } // end while
    }
    return foundLocation;
}

int queens(int queenList[8], int row)
{
    // place first queen at (row,0)
    queenList[0] = row;
    // locate remaining queens in cols 1 -> 7
    if (placeQueens(queenList, 1)) {
        return 1;
    }
    return 0;
}

void do_queens()
{
    int queenList[8];
    int row, col;
    for (col = 0; col < 8; col++) queenList[col] = INVALID;
    for (row = 0; row < 8; row++) queens(queenList, row);
    showBoard(queenList);
}

int main()
{
    do_queens();
}

