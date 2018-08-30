#include <stdio.h>
#include <unistd.h>

// http://pcbheaven.com/wikipages/How_Key_Matrices_Works/


enum state_codes { on, off };
enum ret_codes { ok, fail, repeat };

//                    A    B    C    D
int input[4]   =   { off, off, off, off };
int output[4]  =   { off, off, off, off };
int keys[4][4] = { { off, off, off, off },   // 1
                   { off, off, off, off },   // 2
                   { off, off, off, off },   // 3
                   { off, off, off, off } }; // 4

int get_output(int col, int *row_out)
{
    int row;
    for (row = 0; row < 4; row++) {
        if (keys[row][col] == on) {
            *row_out = row;
            return on;
        }
    }
    return off;
}

void set_key(int row, int col)
{
    keys[row][col] = on;
}

void clr_key(int row, int col)
{
    keys[row][col] = off;
}

void show_key()
{
}

void debounce()
{
}

int main(int argc, char *argv[])
{

    int col;
    int row;
    set_key(1,3);
    for (col = 0; col < 4; ++col) {
        if (on == get_output(col, &row)) {
            printf("key press: (%d,%d)\n", row, col);
        }
    }
}

