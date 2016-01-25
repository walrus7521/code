#include <stdio.h>

int envelope[10] = {0};

int Pow(int x, int y)
{
    int rc = 1, i;
    if (y == 0) return 1;
    if (y < 0) {
        x = 1/x;
        y *= -1;
    }
    for (i = 0; i < y; ++i) {
        rc *= x;
    }
    return rc;
}

int main()
{
    int i, sum;
    printf("exp(%d, %d) = %d\n", 2, 3, Pow(2, 3));
    envelope[0] = Pow(2,0);
    envelope[1] = Pow(2,1);
    envelope[2] = Pow(2,2);
    envelope[3] = Pow(2,3);
    envelope[4] = Pow(2,4);
    envelope[5] = Pow(2,5);
    envelope[6] = Pow(2,6);
    envelope[7] = Pow(2,7);
    envelope[8] = Pow(2,8);
    sum = envelope[0]+envelope[1]+envelope[2]+envelope[3]+envelope[4]+
          envelope[5]+envelope[6]+envelope[7]+envelope[8];
    envelope[9] = 1000-sum;
    printf("sum=%d\n", sum);
    /* note:
     * sum = 2^8 + 2^7 + 2^6 + 2^5 + 2^4 +2^3 + 2^2 + 2^1 + 2^0
     *  which is binary 111111111
     *  = 511
     *  = 2^9 - 1
     */
    printf("2^9 = %d\n", Pow(2,9));
    for (i = 0; i < 10; i++) {
        printf("env[%d] = %d\n", i, envelope[i]);
    }
}

