#include <stdio.h>

void hanoi(int n, int from, int to, int use) {
    if (n > 0) {
        hanoi(n - 1, from, use, to);
        printf("Move from peg %d to %d\n", from, to);
        hanoi(n - 1, use, to, from);
    }
}

int main()
{
    hanoi(4, 1, 3, 2);
    return 0;
}
