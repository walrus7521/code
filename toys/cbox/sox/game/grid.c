#include <stdio.h>

#define ROWS    (30)
#define COLS    (40)
#define VSPACE   (3)
#define HSPACE   (2)

int draw_grid()
{
    int r, c;
    for (r = 0; r < ROWS; r++) {
        if (r % HSPACE == 0) {
            for (c = 0; c < COLS; c++) {
                //if (c % VSPACE == 1) {
                //    printf("|");
                //}
                printf("-");
            }
        } else {
            for (c = 0; c < COLS; c++) {
                if (c % VSPACE == 1) {
                    printf("|");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    draw_grid();
}
