#include <cstdio>
#include <cstdint>
#include <climits>
#include <cmath>

int maxArray(int A[], int left, int right, int& maxV);

#define max(a,b) ((a) > (b) ? (a) : (b))

int maxSubArray(int A[], int n)
{
    int maxV = INT_MIN;
    return maxArray(A,0,n-1,maxV);
}

int maxArray(int A[], int left, int right, int& maxV)
{
    if (left > right) return INT_MIN;
    int mid = (left + right) / 2;
    int lmax = maxArray(A, left, mid-1, maxV);
    int rmax = maxArray(A, mid+1, right, maxV);
    maxV = max(maxV, lmax);
    maxV = max(maxV, rmax);
    int sum, mlmax = 0;
    for (int i = mid-1; i >= left; i--) {
        sum += A[i];
        if (sum > mlmax) mlmax = sum;
    }
    sum = 0; int mrmax = 0;
    for (int i = mid+1; i <= right; i++) {
        sum += A[i];
        if (sum > mrmax) mrmax = sum;
    }
    maxV = max(maxV, mlmax + mrmax + A[mid]);
    return maxV;
}

int main()
{
    int a[] = {2,5,4,8,9,32,5,6,2};
    int len = sizeof(a)/sizeof(a[0]);

    printf("max: %d\n", maxSubArray(a, len));
}

