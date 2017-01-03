#include "pch.hpp"
#include "Graph.hpp"

using namespace std;

void test_graph()
{
    Graph graph = {.V = 12};
    graph.adj = new list<int>[graph.V];

    Graph_addEdge(&graph, 0, 1);
    Graph_addEdge(&graph, 0, 2);
    Graph_addEdge(&graph, 1, 2);
    Graph_addEdge(&graph, 2, 0);
    Graph_addEdge(&graph, 2, 3);
    Graph_addEdge(&graph, 3, 3);
 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    Graph_BFS(&graph, 2);
 
}



int main()
{
    test_graph();
}
