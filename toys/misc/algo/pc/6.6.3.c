#include <stdio.h>

/*

- From the problem, we know f(1) = 2, f(2) = 5
- From the sample Input/Output, we know f(3) = 13
- A number can only start from 1, 2, 3, or 4
- If it starts from 1, then the remaining n-1 digits should have a summation of n-1
- If it starts from 2, then the remaining n-1 digits should have a summation of n-2
- If it starts from 3, then the remaining n-1 digits should have a summation of n-3
- If it starts from 4, then the remaining n-1 digits should have a summation of n-1 (4 is also 1)
- So, f(n) = 2f(n-1) + f(n-2) + f(n-3)
- For this problem we can build a table for all f(n),1 <= n <= 1000
- Remember to use big number library!        

 */

#define MAXN 32
unsigned long long fn[MAXN];
void genfn()
{
    int n;
    fn[0] = 0;
    fn[1] = 2;
    fn[2] = 5;
    fn[3] = 13;
    for (n = 4; n < MAXN; n++) {
        fn[n] = 2*fn[n-1] + fn[n-2] + fn[n-3];
    }
}

void f_of(int n)
{
    printf("f(%d) = %lld\n", n, fn[n]);
}

int main()
{
    int n;
    genfn();
    for (n = 0; n < MAXN; n++)
        f_of(n);
    return 0;
}
