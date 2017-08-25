/* C/C++ program to solve N Queen Problem using
   backtracking */
#define N 8
#include <cstdio>
#include <iostream>
#include <string>

#include "Backtrack.hpp"
void test_backtrack()
{
    solveNQ();
}

#include "Bits.hpp"
void test_bits()
{
    int arr[] = {8, 1, 2, 12};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Max subarray XOR is " << maxSubarrayXOR(arr, n);
}

#include "Dynamic.hpp"
void test_dynamic()
{
    // your code goes here
    string str1 = "sunday";
    string str2 = "saturday";
 
    cout << endl;
    cout << "NP: " << editDist(str1, str2, str1.length(), str2.length()) << endl;
    cout << "DP: " << editDistDP(str1, str2, str1.length(), str2.length()) << endl;
 
}

// driver program to test above function
int main()
{
    test_backtrack();
    test_bits();
    test_dynamic();
    return 0;
}
