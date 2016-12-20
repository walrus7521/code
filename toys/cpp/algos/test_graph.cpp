#include <iostream>
#include "Graph.hpp"

using namespace std;
 
// Driver program to test methods of graph class
int main()
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
 
    return 0;
}

