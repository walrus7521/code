#ifndef _Graph_h_
#define _Graph_h_

#include "pch.hpp"

struct Graph
{
    int V;    // No. of vertices
    std::list<int> *adj; 
};

void Graph_addEdge(Graph *g, int v, int w)
{
    g->adj[v].push_back(w);
}


#endif // _Graph_h_
