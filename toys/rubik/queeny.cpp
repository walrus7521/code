#include <cstdio>
#include <cstring>

int rows[8];
bool collision(int row, int col)
{
    //printf("check: %d, %d\n", row, col);
#if 0
    for (int r = 0; r < 8; r++) {
        if (rows[r] != 0 && r == row) {
            printf("row collision: %d %d\n", r, col);
            return false;
        }
    }
    //printf("no row collision: %d %d\n", row, col);
#endif
    for (int r = 0; r < 8; r++) {
        int hitcol = rows[r];
        if (hitcol == 0) continue;
        printf("check hitcol %d\n", hitcol);
        for (int c = 0; c < 8; c++) {
        //printf("now check col: %d\n", s_col);
        //if (rows[row] && col == rows[row]) {
            if (c == hitcol) {
                printf("col collision: %d %d\n", row, col);
                return false;
            }
        }
    }
    //printf("no col collision: %d %d\n", row, col);

    // now diagonals
    return true;
}

void show()
{
    for (int r = 0; r < 8; r++) {
        printf("%d ", rows[r]);
    }
    printf("\n");
}

int main()
{
    memset(rows, 0, sizeof(rows));
    rows[3] = 4; // starting position
    show();
    int r, c;
    r = 0, c = 3;
    collision(r, c);
#if 0
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (!collision(r, c)) {
                //printf("no collision at (%d, %d)\n", r, c);
                //rows[r] = c;
            } else {
                //printf("collision at (%d, %d)\n", r, c);
            }
        }
    }
#endif
}

