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

void show(vector<int>& A, int len)
{
    cout << endl;

    for (int i = 0; i < len; ++i) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }
}

/* use 2 indices, one to skip repeats, and the other
   to record where to move elements to.  Note, all
   repeated elements are in a single subarray.
 */
int RemoveDuplicatesBook(vector<int>& A)
{
    if (A.empty()) {
        return 0;
    }

    int write_index = 0;
    for (int read = 1; read < A.size(); ++read) {
        if (A[write_index] != A[read]) {
            A[++write_index] = A[read];
        }
    }
    return write_index + 1;
}

int RemoveDuplicates(vector<int>& A)
{
    int count = 0, i = 0, k;
    while (i < A.size()) {
        // look for ascending order, 
        // which back filling zeros will prevent
        if (A[i+1] < A[i]) break; 
        k = i;
        while (A[k] == A[k+1]) {
            for (int j = k+1; j < A.size(); ++j) {                
                if (j+1 < A.size()) {
                    A[j] = A[j+1];
                } else {
                    A[j] = 0;
                }
            }            
        }
        //show(A);
        ++i;
    }
    return count;
}

int main()
{
    vector<int> A = {2,3,4,4,7,11,11,11,13};
    cout << "before: " << endl;
    show(A, A.size());
    //cout << "remove: " << RemoveDuplicates(A) << endl;
    int len = RemoveDuplicatesBook(A);
    cout << "after: " << endl;
    show(A, len);
}

