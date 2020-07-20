#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b)            (((a) > (b)) ? (a) : (b))

int A[] = {-2, -3, 4, -1, -2, 1, 5, -3};
int N = 8;

int max1dsum()
{
    int sum = 0, ans = INT_MIN;
    for (int i = 0; i < N; i++) {
        sum += A[i];
        if (ans < sum)
            ans = sum;
        if (sum < 0)
            sum = 0;
    }
    return ans;
}

int max1dsum_v2()
{
    int sum = 0, ans = INT_MIN;
    for (int i = 0; i < N; i++) {
        sum += A[i];
        ans = max(ans, sum);
        if (sum < 0) sum = 0;
    }
    return ans;
}

int main()
{
    printf("max1: %d\n", max1dsum());
    printf("max2: %d\n", max1dsum_v2());
}
