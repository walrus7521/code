#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define WEIGHT (0)
#define VALUE  (1)

int sack[3][3];
int items[3][3] = {{1,1500},{4,3000},{3,2000}};
int sizes[3] = {1,2,3};

void show()
{
    int r, c;
    for (r = 0; r < 3; r++) {
        printf("(%d,%d)\n", items[r][WEIGHT], items[r][VALUE]);
    }
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            printf("%d ", sack[r][c]);
        }
        printf("\n");
    }
}

// for a given row, find max for a given column
int get_max(int row, int col)
{
    static int max = 0;
    int r, c;
    printf("find max for row %d, col %d\n", row, col);
    for (r = 0; r <= row; r++) {
        int wt_of_row = items[r][WEIGHT];
        int val = items[r][VALUE];
        for (c = 0; c <= col; c++) {
            int wt_cap_of_col = sizes[c];
            if (wt_of_row <= wt_cap_of_col && val > max) {
                max = val;
                printf("setting max = %d\n", max);
            }
        }
    }
    printf("max[%d,%d] = %d\n", row, col, max);
    return max;
}

void knap()
{
    int mx = get_max(0,0);
        //mx = get_max(0,1);
        //mx = get_max(0,2);
}

int main()
{
    knap();
    //show();
}
