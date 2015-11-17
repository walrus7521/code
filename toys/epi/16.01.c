#include <stdio.h>

void Move(int n, int from, int to, int use) {
    if (n > 0) {
        Move(n - 1, from, use, to);
        printf("Move from peg %d to %d\n", from, to);
        Move(n - 1, use, to, from);
    }
}

int main()
{
    Move(4, 1, 3, 2);
    return 0;
}
