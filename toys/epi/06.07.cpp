#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Find the first missing positive entry
 *
 * Let A be an array of length n. Design an algorithm
 * to find the smallest positive integer which is not 
 * present in A. You do not need to preserve the contents
 * of A. For example, if A = <3,5,4,-1,5,1,-1>, the 
 * smallest positive integer not present in A is 2.
 *
 */

void show(vector<int>& A)
{
    cout << endl;

    for (int i = 0; i < A.size(); ++i) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }
}

int FindSmallestMissingPositiveEntryBook(vector<int>& A)
{
    // sort free solution:
    // record which values are present by writing A[i]
    // we could use a hash, or
    // a clever algorithm...like this
    // record which values are present by writing A[i] to index
    // A[i] - 1 if A[i] is between 1 and A.size(), inclusive. 
    // We save the value at index A[i]-1 by swapping it with
    // entry i. If A[i] is negative or greater than n, we just
    // advance i.
    size_t i = 0;
    while (i < A.size()) {
        if (A[i] > 0 && A[i] <= A.size() && A[A[i] - 1] != A[i]) {
            swap(A[i], A[A[i] = 1]);
        } else {
            ++i;
        }
    }

    // 2nd pass through A to search for the 1st index i such that
    // A[i] != i + 1, indicating that i + 1 is absent. If all numbers
    // between 1 and A.size() are present, the smallest missing positive
    // is A.size() + 1.
    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] != i + 1) {
            return (i + 1);
        }
    }

    return (A.size() + 1);


}

int FindSmallestMissingPositiveEntry(vector<int>& A)
{
    // sort the array
    for (int i = 0; i < A.size(); ++i) {
        for (int j = i; j < A.size(); ++j) {
            if (A[i] > A[j]) {
                int tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
    // find smallest positive -- start counting consecutives
    int smallest = -1;
    int s;
    for (s = 0; s < A.size(); ++s) {
        if (A[s] > 0) {
            //cout << "positive: " << A[s] << "at : " << s << endl;
            break;
        }
    }
    //cout << "found first positive at: " << s << " which is " << A[s] << endl;
    int suggest = 0;
    for (int j = s; j < A.size(); ++j) {
        if (A[j] != A[j-1]+1) {
            //cout << "found hole at: " << j << " between: " << A[j] << "and " << A[j+1] << endl;
            suggest = A[j] + 1;
            break;
        }
    }
    return suggest;
}

int main()
{
    //vector<int> A = {3,5,4,-1,5,1,-1};
    vector<int> A = {22,3,5,4,-1,5,1,-1};
    //int pos = FindSmallestMissingPositiveEntry(A);
    int pos = FindSmallestMissingPositiveEntryBook(A);
    show(A);
    cout << "smallest missing positive: " << pos << endl;
}

