/* C/C++ program to solve N Queen Problem using
   backtracking */
#define N 8
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;


// driver program to test above function
int main()
{
    test_backtrack();
    test_bits();
    test_dynamic();
    test_graph();
    // test_hash()
    test_list();

    
    return 0;
}
