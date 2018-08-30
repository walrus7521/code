#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::sort;

/**

Let A be an array of n numbers.  Let t be a number, and k be an integer in [1,n].
Define A to k-create t if and onl if there exists k indices i0, i1, i2, ... , ik-1 
(not necessarily distinct) such that SUM[j-0, k-1]A[ij] = t;

Design an algorithm that takes as input an array A and a number t, 
and determines if A 3-creates t.

1. Sort A
2. For each A[i], search for indices j and k, such that A[j] + A[k] = t - A[i];

 */

bool HasTwoSum(const vector<int>& A, int t) {
    int j = 0, k = A.size() - 1;
    
    //cout << "has 2 sum? [" << t << "]";
    while (j <= k) {
        if (A[j] + A[k] == t) {
            //cout << " yes" << endl;
            return true;
        } else
        if (A[j] + A[k] < t) {
            ++j;
        } else { // A[j] + A[k] > t
            --k;
        }
    }
    //cout << " no" << endl;
    return false;
}

bool HasThreeSum(vector<int> A, int t) {
    sort(A.begin(), A.end());

    for (int a : A) {
        // finds if the sum of 2 numbers in A equals to t - a.
        if (HasTwoSum(A, t-a)) {
            return true;
        }
    }
    return false;
}

int main()
{
    vector<int> vi = {1, 2, 3, 4, 5, 7};
    bool has3;
    int sum;
    for (sum = 0; sum < 12; ++sum) {
        has3 = HasThreeSum(vi, sum);
        cout << sum << (has3 ? " has 3 sum" : " has no 3 sum") << endl;
    }
    return 0;
}
