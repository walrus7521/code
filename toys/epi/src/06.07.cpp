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

int FindFirstMissingPositiveEntry(vector<int>& A)
{
    return 0;
}

int main()
{
    vector<int> A = {3,5,4,-1,5,1,-1};
    show(A);
}

