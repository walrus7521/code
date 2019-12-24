#include "utils2.h"


int x[9], TC, a, b, lineCounter;

bool place(int queen, int row) {
    for (int prev = 1; prev <= queen-1; prev++) {
        if (x[prev] == row || (abs(x[prev] - row) == abs(prev-queen))) {
            return false;
        }
    }
    return true;
}

void dumpBoard() {
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            if (x[col] == row) printf("%d ", 1);
            else printf("%d ", 0);
        }
        printf("\n");
    }
}

void NQueens(int queen) {
    for (int row = 1; row <= 8; row++) {
        if (place(queen, row)) {
            x[queen] = row;
            if (queen == 8 && x[b] == a) {
                printf("%2d     %d", ++lineCounter, x[1]);
                for (int j = 2; j <= 8; j++) printf(" %d", x[j]);
                printf("\n");
                dumpBoard();
            } else {
                NQueens(queen+1);
            }
        }
    }
}

int main()
{
    int row = 3, column = 5;
    TC = 1; a = row; b = column;
    memset(x, 0, sizeof(x)); lineCounter=0;
    printf("SOLN      COLUMN\n");
    printf(" #     1 2 3 4 5 6 7 8\n\n");
    NQueens(1);
    printf("\n");
}

