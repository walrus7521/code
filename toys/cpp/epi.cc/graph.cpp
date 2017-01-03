#include "pch.hpp"
#include "Graph.hpp"

using namespace std;

void test_graph()
{
    Graph graph = {.V = 12};
    graph.adj = new list<int>[graph.V];
}



int main()
{
    test_graph();
}
