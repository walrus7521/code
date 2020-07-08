#include <cstdio>
#include <cstring>
#include <cmath>

int out_row[8];
int in_row, in_col;

bool place(int row, int col)
{
    for (int prev_col = 0; prev_col < col; prev_col++) {
        if (out_row[prev_col] == row || (abs(out_row[prev_col] - row) == abs(prev_col - col))) {
            return false;
        }
    }
    return true;
}

void backtrack(int col)
{
    if (col == 8 && out_row[in_col] == in_row) {
        printf("row: %d :", out_row[0] + 1);
        for (int j = 1; j < 8; j++) {
            printf(" %d", out_row[j] + 1);
        }
        printf("\n");
    }
    for (int row = 0; row < 8; row++) {
        if (place(row, col)) {
            out_row[col] = row;
            backtrack(col+1);
        }
    }
}

int main()
{
    memset(out_row, 0, sizeof(out_row));
    in_col = 3; in_row = 4;
    backtrack(0);
}

