#include <iostream>
#include <vector>


using namespace std;


/*
    Permute the elements of an array

    Given an array of n elements and a permutation P, apply P to A
    using only constant additional storage. Use A itself to store
    the result.

    Example: P = <2,0,1,3> // permutation mapping
             A = <a,b,c,d> // A to be permuted
             result = <b,c,a,d> // result

 */

using namespace std;

#define INVALID -6

void show(vector<int>& A) {
    for (int i = 0; i < A.size(); ++i) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }
}

int FindIdx(vector<int> A, int idx)
{
    int idx_find;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] == idx) {
            A[i] = INVALID;
            return idx;
        }
    }
    return INVALID;
}

void PermuteIt(vector<int>& A, vector<int> P) {
    for (int i = 0; i < A.size(); ++i) {
        if (P[i] != INVALID) {
            int idxp = P[i];
            int idxc = FindIdx(P, i);
            if (idxc != INVALID) {
                // swap em
                int tmp = A[idxp];
                A[idxp] = A[idxc];
                A[idxc] = tmp;
                P[idxp] = INVALID;
                P[idxc] = INVALID;
            }
        }
        //A[P[i]] = A[i];
    }
}

int main()
{
    vector<int> A = {22,3,5,4};
    vector<int> P = {2,0,1,3};
    show(A);
    show(P);
    PermuteIt(A, P);
    show(A);
}

