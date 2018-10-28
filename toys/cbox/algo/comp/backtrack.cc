#include "utils.h"

int row[8], TC, a, b, lineCounter;

bool place(int r, int c)
{
    for (int prev = 0; prev < c; prev++) {
        if (row[prev] == r || (abs(row[prev] - r) == abs(prev - c)))
            return false;
    }
    return true;
}

//
int n = 14;
int ans = 0;
bitset<30> rw, ld, rd;
char board[14][14] = {0};
void backtrack_uva11195(int c)
{
    if (c == n) { ans++; return; }
    for (int r = 0; r < n; r++) {
        if (board[r][c] != '*' &&
            !rw[r] && !ld[r-c+n-1] &&
             !rd[r+c]) {
            rw[r] = ld[r-c+n-1] = rd[r+c] = true;
            backtrack_uva11195(c+1);
            rw[r] = ld[r-c+n-1] = rd[r+c] = false;
        }
    }
}


// use file in_queen_1
void backtrack_uva750(int c)
{
    if (c == 8 && row[b] == a) {
        printf("%2d    %d", ++lineCounter, row[0] + 1);
        for (int j = 1; j < 8; j++) printf(" %d", row[j] + 1);
        printf("\n");
    }
    for (int r = 0; r < 8; r++) {
        if (place(r, c)) {
            row[c] = r; backtrack_uva750(c + 1);
        }
    }
}

int main()
{
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d %d", &a, &b); a--; b--;
        memset(row, 0, sizeof(row)); lineCounter = 0;
        printf("SOLN       COLUMN\n");
        printf(" #    1 2 3 4 5 6 7 8\n\n");
        backtrack_uva750(0);
        //backtrack_uva11195(0);
        if (TC) printf("\n");
    }
}

