#include <stdio.h>

void Hanoi(int n, int from, int to, int use) {
    if (n > 0) {
        Hanoi(n - 1, from, use, to);
        printf("Move from peg %d to %d\n", from, to);
        Hanoi(n - 1, use, to, from);
    }
}

int main()
{
    Hanoi(4, 1, 3, 2);
    return 0;
}
