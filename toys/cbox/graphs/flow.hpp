#ifndef _FLOW_H_
#define _FLOW_H_

#include <queue>

using namespace std;

#define MAXV        100 /* maximum number of vertices */
#define MAXDEGREE   50  /* maximum outdegree of a vertex */


typedef struct {
    int v;              /* neighboring vertex */
    int capacity;       /* capacity of edge */
    int flow;           /* flow through edge */
    int residual;       /* residual capacity of edge */
} edge;

typedef struct {
    edge edges[MAXV][MAXDEGREE];    /* adjacency info */
    int degree[MAXV];   /* outdegree of each vertex */
    int nvertices;      /* number of vertices in the graph */
    int nedges;         /* number of edges in the graph */
} flow_graph;

bool processed[MAXV];   /* which vertices have been processed */
bool discovered[MAXV];  /* which vertices have been found */
int parent[MAXV];       /* discovery relation */
bool finished = false;  /* if true, cut off search immediately */

void process_vertex(int v) {}
void process_edge(int x, int y) {}


bool valid_edge(edge e)
{
    if (e.residual > 0) return (true);
    else return(false);
}

void initialize_graph(flow_graph* g)
{
    g->nvertices = 0;
    g->nedges = 0;
    for (int i = 0; i < MAXV; i++) g->degree[i] = 0;
}

void initialize_search(flow_graph *g)
{
    for (int i=1; i<=g->nvertices; i++) {
        processed[i] = false;
        discovered[i] = false;
        parent[i] = -1;
    }
}

void bfs(flow_graph *g, int start)
{
    queue<int> q;  /* queue of vertices to visit */

    q.push(start);
    discovered[start] = true;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        process_vertex(v);
        processed[v] = true;
        for (int i=0; i<g->degree[v]; i++) 
            if (valid_edge(g->edges[v][i]) == true) {
            if (discovered[g->edges[v][i].v] == false) {
                q.push(g->edges[v][i].v);
                discovered[g->edges[v][i].v] = true;
                parent[g->edges[v][i].v] = v;
            }
            if (processed[g->edges[v][i].v] == false) 
                process_edge(v,g->edges[v][i].v);
            }
    }
}


#endif // _FLOW_H_

