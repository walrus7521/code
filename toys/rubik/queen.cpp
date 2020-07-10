#include <cstdio>
#include <cmath>

int rows[9]={0,0,0,0,0,0,0,0,0}, in_row=4, in_col=3, lineCounter=0;

bool place(int row, int col) {
    for (int prev_col = 0; prev_col < col; prev_col++) {
        if (rows[prev_col] == row || (abs(rows[prev_col] - row) == abs(prev_col - col))) {
            return false;
        }
    }
    return true;
}

void backtrack(int col) {
    if (col == 8 && rows[in_col] == in_row) {
        printf("%2d         %d", ++lineCounter, rows[0] + 1);
        for (int j = 1; j < 8; j++) printf(" %d", rows[j] + 1);
        printf("\n");
    }
    for (int row = 0; row < 8; row++) {
        if (place(row, col)) {
            rows[col] = row; backtrack(col+1);
        }
    }
}

int main() {
    printf("SOLN        COLUMN\n");
    printf(" #         1 2 3 4 5 6 7 8\n\n");
    backtrack(0);
}

