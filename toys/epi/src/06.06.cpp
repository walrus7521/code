#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Delete duplicates for a sorted array
 *
 * This problem is concerned with deleting repeated elements from
 * a sorted array. For example, if A = <2,3,4,4,7,11,11,11,13>,
 * then after deletion, A = <2,3,5,7,11,13,0,0,0>.  After deletion,
 * there are 6 valid entries in A. There are no requirements as to
 * the values stored beyond the last valid element.
 *
 * Write a function which takes as input a sorted array A and
 * updates A so that all duplicates have been removed and the 
 * remaining elements have been shifted left to fill the emptied
 * indices.  Return the number of valid elements in A. Many
 * languages have library functions for performing this operation -
 * you cannot use these functions.
 *
 */


int RemoveDuplicates(vector<int>& A)
{
    int count = 0;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] == A[i+1]) {
            count++;
            for (int j = i+2; j < A.size(); ++j) {                
                if (j+1 < A.size()) {
                    A[j] = A[j+1];
                } else {
                    A[j] = 0;
                }
            }
        }
    }
    return count;
}

int RemoveDuplicates2(vector<int>& A)
{
    int count = 0;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] == A[i+1]) {
            count++;
            for (int j = i; j < A.size(); ++j) {                
                if (j+1 >= A.size()) {
                    A[j] = 0;
                } else {
                    A[j] = A[j+1];
                }
            }
        }
    }
    return count;
}

int main()
{
    vector<int> A = {2,3,4,4,7,11,11,11,13};

    cout << "before: " << endl;
    for (auto x: A) {
        cout << "A[] = " << x << endl;
    }
    cout << "remove: " << RemoveDuplicates(A) << endl;
    cout << "after: " << endl;
    for (auto x: A) {
        cout << "A[] = " << x << endl;
    }
}

