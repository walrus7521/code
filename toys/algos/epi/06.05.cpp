#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Delete a key from an array
 *
 * This problem is concerned with writing a remove function for
 * arrays.  Often, languages have library functions for performing
 * this operation. You cannot use these functions. (Imagine you
 * are implementing the corresponding library.)
 *
 * Implement a function which takes as input an array A of integers
 * and an integer k, and updates A so that all occurences of k have 
 * been removed and the remaining elements have been shifted left to
 * fill the emptied idices. Return the number of remaining elements.
 * There are no requirements as to the values stored beyond the last
 * valid element. For example, if A=<5,3,7,11,2,3,13,5,7> and k=3,
 * then <5,7,11,2,13,5,7,0,0> is an acceptable update to A, and the
 * return value is 7.
 *
 */


int RemoveElements(vector<int>& A, int k)
{
    int count = 0;
    for (int i = 0; i < A.size(); ++i) {
        int x = A[i];
        if (x == k) {
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
    vector<int> A = {5,3,7,11,2,3,13,5,7};
    int k = 3;

    cout << "before: " << endl;
    for (auto x: A) {
        cout << "A[] = " << x << endl;
    }
    cout << "remove: " << k << " " << RemoveElements(A, k) << endl;
    cout << "after: " << endl;
    for (auto x: A) {
        cout << "A[] = " << x << endl;
    }
}

