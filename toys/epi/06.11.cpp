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
    return ret;
}

int main()
{
    int array[] = {2,11,3,5,13,7,19,17,23};
    vector<int> A (array, array + sizeof(array)/sizeof(array[0]));    
    pair<int, int> ret = LongestSubarray(A);
}
