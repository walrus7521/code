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

void Graph_BFS(Graph *g, int s)
{
    bool *visited = new bool[g->V];
    for (int i = 0; i < g->V; ++i) {
        visited[i] = false;
    }

    std::list<int> queue;
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent vertices of a vertex
    std::list<int>::iterator i;
 
    while (!queue.empty()) {
        s = queue.front();
        std::cout << s << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = g->adj[s].begin(); i != g->adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    std::cout << std::endl;
}

#endif // _Graph_h_
