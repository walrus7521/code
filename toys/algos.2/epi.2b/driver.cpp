/* C/C++ program to solve N Queen Problem using
   backtracking */
#define N 8
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

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

#include "Graph.hpp"
void test_graph()
{
    // Create a graph given in the above diagram
    Graph g(4);
    //       v1 v2  data   wt
    g.addEdge(0, 1, "abe", 1);
    g.addEdge(0, 2, "boe", 1);
    g.addEdge(1, 2, "cal", 1);
    g.addEdge(2, 0, "doe", 1);
    g.addEdge(2, 3, "egg", 1);
    g.addEdge(3, 3, "fog", 1);
 
    g.show();

    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.Bfs(2);
    cout << endl;
}

#if 0
#include "hash.h"
void test_hash()
{
    hash *h = createHash(13);

    insertHash(h, "abe", 0);
    insertHash(h, "boa", 1);
    insertHash(h, "cod", 2);
    insertHash(h, "dia", 3);
    insertHash(h, "eat", 4);
    insertHash(h, "fat", 5);

    showHash(h);
#if 0

    cout << "h(7)?: " << h.lookup("goa", 7) << endl;
    cout << "h(4)?: " << h.lookup("eat", 4) << endl;

    pair<string, int> p = h.fetch("eat", 4);
    cout << "f(4): " << p.first << ": " << p.second << endl;
    pair<string, int> p2 = h.fetch("goe", 7);
    cout << "f(7): " << p2.first << ": " << p2.second << endl;
#endif

}
#endif

// driver program to test above function
int main()
{
    test_backtrack();
    test_bits();
    test_dynamic();
    test_graph();

    
    return 0;
}
