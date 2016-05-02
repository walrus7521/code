#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

/* Generate uniform random numbers
 *
 * This problem is motivated by the following.  Five friends have to select a
 * designated driver using a single unbiased coin.  The process should be fair
 * to everyone.
 *
 * How would you implement a random number generator that generates a random
 * integer i between a and b, inclusive, given a random number generator that
 * produces either zero or one with equal probability?  All generated values
 * should be equally likely.
 */

int ZeroOneRandom()
{
    double res = rand() / double(RAND_MAX);
    return (res < 0.50 ? 0 : 1); 
}

int UniformRandom(int a, int b)
{
    int t = b - a + 1, res;
    do {
        res = 0;
        for (int i = 0; (1 << i) < t; ++i) {
            res = res * 2 | ZeroOneRandom();
        }
    } while (res >= t);
    return (a + res);
}

int main()
{
    srand((unsigned)time(NULL));
    int a = 4, b = 10;
    printf("%d - %d => %d\n", a, b, UniformRandom(a, b));
#if 0
    for (int i = 0; i < 8; ++i) {
        printf("%d = %d\n", i, ZeroOneRandom());
    }
#endif
}
