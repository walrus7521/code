#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

/*
 *  Compute a random permutation
 *
 *  Design an algorithm that creates uniformly random permutations of
 *  [0,1,...,n-1]. You are given a random number generator that returns
 *  integers in the set [0,1,...,n-1] with equal probability; use as
 *  few calls to it as possible.
 *
 *  Basically, for each element from left to right, you generate all the 
 *  permutations of the remaining elements. You can do this recursively, 
 *  (or iteratively if you like pain) until you get to the last element 
 *  at which point there is only one possible order.
 *
 *  So, given a list: [1,2,3,4]
 *  You just generate all permutations that start with 1, then all the 
 *  permutations that start with 2, then with 3 and 4.
 * 
 *  This effectively reduces the problem from one of finding permutations 
 *  of a list of four elements to a list of three elements. Once you continue 
 *  reducing to 2 and then 1 element, you have all of them.
 *
 */

void show(vector<int>& A) {
    cout << "<" ;
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << ", ";
    }
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

void RandomPermutation(vector<int>& A, int k)
{
    for (int i = A.size()-1; i >= A.size()-1-k; --i) {
        int r = UniformRandom(0, i);
        int tmp = A[r];
        A[r] = A[i];
        A[i] = tmp;
    }
}

/* create a P vector of 0..k permutations,
 * and randomly select the element
 */
void CreatePermutationVector(vector<int>& P, int k)
{
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

