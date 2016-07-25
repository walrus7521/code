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

void RotateArray(vector<int> A, int i) {
    for (int i = 0; i < A.size(); ++i) {
    }
}

int main()
{
    int i = 4;
    vector<int> A = {22,3,5,4,8,1,34,76,23,98};
    show(A);
    RotateArray(A, i);
    cout << "after rotation " << i << " positions right" << endl;
    show(A);
}
