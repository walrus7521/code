#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

int x[9], TC, a, b, lineCounter;

bool place(int queen, int row) {
    for (int prev = 1; prev <= queen - 1; prev++) {
        if (x[prev] == row || (abs(x[prev] - row) == abs(prev - queen)))
            printf("place returns false\n");
            return false;
    }
    printf("place returns true\n");
    return true;
}

void NQueens(int queen) {
    printf("queen: %d\n", queen);
    for (int row = 1; row <= 8; row++) {
        if (place(queen, row)) {
            x[queen] = row;
            printf("ok: %d %d\n", queen, row);
            if (queen == 8 && x[b] == a) {
                printf("%2d     %d", ++lineCounter, x[1]);
                for (int j = 2; j <= 8; j++) printf(" %d", x[j]);
                printf("\n");
            }
        } else {
            NQueens(queen + 1);
        }
    }
}

int main() {
    scanf("%d %d", &a, &b);
    memset(x, 0, sizeof(x));
    lineCounter = 0;
    printf("SOLN        COLUMN\n");
    printf(" #         1 2 3 4 5 6 7 8\n\n");
    NQueens(1);
    printf("\n");
}
