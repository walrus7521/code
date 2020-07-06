#include <stdio.h>
#include <string.h>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

char str1[] = "FOSH";
char str2[] = "FORT";
int rows, cols, max;

int cell[4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
};

void show()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", cell[i][j]);
        }
        printf("\n");
    }
    printf("max: %d\n", max);
}


int get_top_left(int row, int col)
{
    if (row <= 0) return 0;
    if (col <= 0) return 0;
    return cell[row-1][col-1];
}

int get_top(int row, int col)
{
    if (row <= 0) return 0;
    return cell[row-1][col];
}

int get_left(int row, int col)
{
    if (col <= 0) return 0;
    return cell[row][col-1];
}

void LCS()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (str1[r] == str2[c]) {
                cell[r][c] = 1 + get_top_left(r, c);
            } else {
                int top  = get_top(r, c);
                int left = get_left(r, c);
                cell[r][c] = max(top, left);
            }
            if (cell[r][c] > max) max = cell[r][c];
        }
    }
}


int main()
{
    rows = strlen(str1);
    cols = strlen(str2);
    max  = 0;
    LCS();
    show();
}

