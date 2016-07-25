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
 * Rotate an array, A of n elements to the right/left
 * by k positions.
 *
 */

/*
 * To rotate left by one, store arr[0] in a temporary variable temp, 
 * move arr[1] to arr[0], arr[2] to arr[1] …and finally temp to arr[n-1]
 */

void RotateArrayLeft(vector<int>& A, int k) {
    int i, j, n = A.size();
    for (j = 0; j < k; ++j) {
        int tmp = A[0];
        for (i = 0; i < n; ++i) {
            A[i] = A[i+1];
        }
        A[i-1] = tmp;
    }
}

/*
 * To rotate left by one, store arr[n-1] in a temporary variable temp, 
 * move arr[n-2] to arr[n-1], arr[n-3] to arr[n-2] …and finally temp to arr[0]
 */
void RotateArrayRight(vector<int>& A, int k) {
    int i, j, n = A.size();
    for (j = 0; j < k; ++j) {   
        int tmp = A[n-1];
        for (i = n-1; i > 0; --i) {
            A[i] = A[i-1];
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
