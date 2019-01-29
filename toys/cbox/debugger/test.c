#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int test1(int a)
{
    return (a+3);
}

int main()
{
    while (1) {
        int j = test1(42);
        printf("test: %d\n", j);
        sleep(2);
    }
    char *p = malloc(16);
}


