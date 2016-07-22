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

void show(vector<int>& A) {
    for (int i = 0; i < A.size(); ++i) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }
}

void PermuteIt(vector<int>& A, vector<int> P) {
    for (int i = 0; i < A.size(); ++i) {
        int tmp = P[i];
        P[i] = A[i];
        A[tmp] = P[i];
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

