#include <stdio.h>

/*
 *
 * a(1) = 1;
 * a(n+1) = 1 + a(n+1 - a(a(n)))
 *
 *
 */

int golomb(int n)
{
    int k, l, j, m, t;

    for (k = 2, m = 1, l = 2; m < 3; m++) {
        for (t = 0; t < k; t++) {
        //    printf("%d => %d\n", n, l);
        }
        l++;
    }
    return l;
}

int main()
{
    int n;
    n = 100;
    printf("golomb(%d) = %d\n", n, golomb(n));
#if 0
    int k=2,l=2,c=2,j=1,m,t;
    for (c = 2; c < 100; ) {
        for(m=1;m<3;m++) {
            for(t=0;t<k;t++) {
                printf("%d => %d\n", c, l);
                c++;
            }
            l++;
        }
        k++;
    }
#endif
    return 0;
}

