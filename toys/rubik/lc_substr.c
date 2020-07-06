#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str1[] = "blue";
char str2[] = "clues";
int rows, cols, max;
int cell[5][5];

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
            if (str1[i] == str2[j]) {
                cell[i][j] = 1 + last_cell_value(i,j);
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
    memset(cell, 0, sizeof(cell));

    LCS();
    show();
}

