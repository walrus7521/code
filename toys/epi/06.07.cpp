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
    int pos = FindSmallestMissingPositiveEntry(A);
    show(A);
    cout << "smallest missing positive: " << pos << endl;
}

