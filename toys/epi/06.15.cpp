#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

void show(vector<int>& A) {
    cout << "<" ;
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << ", ";
    }
    cout << ">" << endl;
}

/*
 * Rotate an array, A of n elements to the right
 * by i positions.
 *
 */

/*
 * To rotate by one, store arr[0] in a temporary variable temp, 
 * move arr[1] to arr[0], arr[2] to arr[1] …and finally temp to arr[n-1]
 *
 */

void RotateArrayLeft(vector<int>& A, int k) {
    int i, j;
    for (j = 0; j < k; ++j) {
        int tmp = A[0];
        for (i = 0; i < A.size(); ++i) {
            A[i] = A[i+1];
        }
        A[i-1] = tmp;
    }
}

void RotateArrayRight(vector<int>& A, int k) {
    int i, j;
    for (j = 0; j < k; ++j) {
        int tmp = A[A.size()-1];
        for (i = A.size(); i > 0; --i) {
            A[i] = A[i+1];
        }
        A[0] = tmp;
    }
}

int main()
{
    int i = 3;
    vector<int> A = {2,0,1,3};
    show(A);
    //RotateArrayLeft(A, i);
    RotateArrayRight(A, i);
    cout << "after rotation " << i << " positions right" << endl;
    show(A);
}
