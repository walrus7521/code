#include <stdio.h>
#include <string.h>

char str1[] = "FOSH";
char str2[] = "FISH";
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

int last_cell_value(int row, int col)
{
    if (row <= 0) return 0;
    if (col <= 0) return 0;
    return cell[row-1][col-1];
}

void LCS()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //printf("s1[%d]: %c, s2[%d]: %c\n", i, str1[i], j, str2[j]);
            if (str1[i] == str2[j]) {
                printf("HIT %d %d\n", i, j);
                cell[i][j] = 1 + last_cell_value(i,j);
                //printf("HIT s1[%d]: %c, s2[%d]: %c\n", i, str1[i], j, str2[j]);
                if (cell[i][j] > max) max = cell[i][j];
            } else {
                cell[i][j] = 0;
            }
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

