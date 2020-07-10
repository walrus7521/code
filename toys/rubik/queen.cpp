#include <cstdio>
#include <cmath>

int row[8]={0,0,0,0,0,0,0,0}, in_row=4, in_col=3, line=0;

bool place(int r, int c) {
    for (int prev_c = 0; prev_c < c; prev_c++) {
        if (row[prev_c] == r ||
            (abs(row[prev_c] - r) == abs(prev_c - c))) {
                return false;
        }
    }
    return true;
}

void backtrack(int c) {
    if (c == 8 && row[in_col] == in_row) {
        printf("ROWS[%02d] =>    %d", ++line, row[0] + 1);
        for (int j = 1; j < 8; j++) printf(" %d", row[j] + 1);
        printf("\n");
    }
    for (int r = 0; r < 8; r++) {
        if (place(r, c)) {
            row[c] = r; backtrack(c+1);
        }
    }
}

int main() {
    printf("\n           COLUMN\n");
    printf("SOLNS      1 2 3 4 5 6 7 8\n\n");
    backtrack(0);
}

