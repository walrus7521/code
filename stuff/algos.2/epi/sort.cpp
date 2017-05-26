#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void show(vector<int>& A) {
    for (int i = 0; i < A.size(); ++i) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }
}

void SortIt(vector<int>& A) {
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
}

int main()
{
    //vector<int> A = {3,5,4,-1,5,1,-1};
    vector<int> A = {22,3,5,4,-1,5,1,-1};
    show(A);
    SortIt(A);
    show(A);
}

