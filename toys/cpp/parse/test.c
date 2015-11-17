#include <stdio.h>

int func(int a) {
    printf("a = %d\n", a);
}

int main() 
{
    int i;

    for (i = 0; i < 4; i++) {
        if (i % 2) {
            func(i);
        }
    }
    return 0;
}
