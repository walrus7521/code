#if 0
m:\code>c:\LLVM\bin\clang.exe clang_array_init.c

m:\code>a.exe
 1 1 1 1 1 1 1 1 1 1
 1 1 1 1 1 1 1 1 1 1
 1 1 1 1 1 1 1 1 1 1
 1 1 1 1 1 1 1 1 1 1
 1 1 1 1 1 1 1 1 1 1
#endif

#include <stdio.h>

enum { ROW = 5, COLUMN = 10 };

int array[ROW][COLUMN] = { [0 ... ROW-1] = { [0 ... COLUMN-1] = 1 } };

int main(void)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
            printf("%2d", array[i][j]);
        putchar('\n');
    }
    return 0;
}
