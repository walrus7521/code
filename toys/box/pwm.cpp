#include <cstdio>

int main()
{
    unsigned short val = -1;
    int i;
    printf("val: %x\n", val);
    for (i = 0; i < 64; ++i) {
        val-=4000;
        printf("val[%d]: %x\n", i, val);
    }
}

