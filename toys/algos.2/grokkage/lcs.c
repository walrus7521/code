#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

char word_a[] = " fish";
char word_b[] = " fosh";
int cell[5][5];

void clear()
{
    int i, j;
    for (i = 0; i <= 4; i++) 
        for (j = 0; j <= 4; j++) cell[i][j] = 0;
}

void show()
{
    int i, j;
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 4; j++) printf("%d ", cell[i][j]);
        printf("\n");
    }
}

void lc_substring()
{
    int i, j;
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 4; j++) {
            if (word_a[i] == word_b[j]) {
                cell[i][j] = cell[i-1][j-1] + 1;
            } else {
                cell[i][j] = 0;
            }
        }
    }
}

void lc_subsequence()
{
    int i, j;
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 4; j++) {
            if (word_a[i] == word_b[j]) {
                cell[i][j] = cell[i-1][j-1] + 1;
            } else {
                cell[i][j] = MAX(cell[i-1][j], cell[i][j-1]);
            }
        }
    }
}

int main()
{
    clear();
    lc_subsequence();
    show();

    printf("\n");

    clear();
    lc_substring();
    show();



}
