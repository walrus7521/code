#include <cstdio>
#include <cmath>

//                           a = in_row b = in_col
int x[9]={0,0,0,0,0,0,0,0,0}, a=4, b=3, line=0;

bool place(int queen, int row) {
    for (int prev_c = 1; prev_c <= queen-1; prev_c++) {
        if (x[prev_c] == row ||
            (abs(x[prev_c] - row) == abs(prev_c - queen))) {
                return false;
        }
    }
    return true;
}

void backtrack(int queen) { /* queen = col */
    for (int row = 1; row <= 8; row++) {
        if (place(queen, row)) {
            x[queen] = row;
            if (queen == 8 && x[b] == a) {
                printf("ROWS[%02d] =>    %d", ++line, x[1]);
                for (int j = 2; j <= 8; j++) printf(" %d", x[j]);
                printf("\n");
            } else {
                backtrack(queen+1);
            }
        }
    }
    
}

int main() {
    printf("\n           COLUMN\n");
    printf("SOLNS      1 2 3 4 5 6 7 8\n\n");
    backtrack(1);
}

