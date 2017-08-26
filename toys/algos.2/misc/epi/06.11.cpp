#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/* 
   Compute the longest contiguous increasing subarray

   An array is increasing if each element is less than it succeeding
   element, except for the last element.

   Implement an algorithm that takes as input an array A of n
   elements and returns the beginning and ending indices of a
   longest increasing subarray of A. E.g., A=<2,11,3,5,13,7,19,17,23>
   = <3,5,13> and you should return <2,4>
*/

pair<int, int> LongestSubarray(vector<int> A)
{
    pair<int, int> ret(0,0);
    int max_len = 0, cur_len, max_idx;
    int i, j;
    for (i = 0; i < A.size(); ++i) {
        cur_len = 1;
        for (j = i; j < A.size(); ++j) {
            if (A[j] < A[j+1]) {
                cur_len++;
             } else {
                 break;
             }
        }
        if (cur_len > max_len) {
            max_len = cur_len;
            max_idx = j;
        }
    }

    if (max_idx == A.size()) {
        --max_idx;
        --max_len;
    }
    
    cout << "len = " << max_len << " idx = " << max_idx << endl;
    return ret;
}

int main()
{
    //int array[] = {2,11,3,5,13,7,19,17,23};
    //int array[] = {2,3,5,7,19,17,23};
    int array[] = {12,11,5,4,19,17,23};
    vector<int> A (array, array + sizeof(array)/sizeof(array[0]));    
    pair<int, int> ret = LongestSubarray(A);
}
