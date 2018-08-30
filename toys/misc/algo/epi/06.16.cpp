#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

/*
 *  Sample offline data
 *
 *  Let A be an array whose entries are all distinct. Implement an
 *  algorithm that takes A and an integer k and returns a subset of
 *  k elements of A. All subsets should be equally likely. Use as few
 *  calls to the random number generator (which returns random integers)
 *  as possible and use O(1) additional storage. You can return the
 *  result in the same array as input.
 */


void show(vector<int>& A) {
    cout << "<" ;
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << ", ";
    }
    cout << ">" << endl;
}

void showR(vector<int>& A) {
    std::vector<int>::reverse_iterator rit = A.rbegin();
    cout << "<" ;
    for (; rit!= A.rend(); ++rit)
        cout << *rit << ", ";
    cout << ">" << endl;

}

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

void OfflineSample(vector<int>& A, int k)
{
    for (int i = A.size()-1; i >= A.size()-1-k; --i) {
        int r = UniformRandom(0, i);
        int tmp = A[r];
        A[r] = A[i];
        A[i] = tmp;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    vector<int> A = {1,2,3,4,5};
    int k = 2;
    show(A);
    OfflineSample(A, k);
    show(A);
}

