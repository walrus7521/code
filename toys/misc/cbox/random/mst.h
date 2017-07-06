#include <stdio.h>
#include <stdlib.h>

typedef struct _graph {
    int v;
    int e;
    int **adj;
    int *visited;
    int *indegree;
    int *toporder;
} graph;

graph *create(int vertices)
{
    int u, v;
    graph *g = (graph *) malloc(sizeof(graph));
    g->adj = (int **) malloc(sizeof(int *) * vertices);
    g->v = vertices;
    for (v = 0; v < vertices; v++) {
        g->adj[v] = (int *) malloc(sizeof(int) * vertices);
    }
    g->visited  = (int *) malloc(sizeof(int) * vertices);
    g->indegree = (int *) malloc(sizeof(int) * vertices);
    g->toporder = (int *) malloc(sizeof(int) * vertices);
    for (u = 0; u < g->v; u++) {
        g->visited[u] = 0;
        g->indegree[u] = 0;
        g->toporder[u] = -1;
    }
    for (u = 0; u < g->v; u++)
        for (v = 0; v < g->v; v++)
            g->adj[u][v] = 0;
    return g;
}

void add_edge_wt(graph *g, int u, int v, int wt)
{
    g->adj[u][v] = wt;
    g->indegree[v]++;
    g->toporder[u] = 0;
    g->toporder[v] = 0;
    g->e++;
}

void init_mst(graph *g)
{
    add_edge_wt(g, 0, 1, 1);
    add_edge_wt(g, 0, 3, 1);
    add_edge_wt(g, 1, 3, 1);
    add_edge_wt(g, 1, 4, 1);
    add_edge_wt(g, 2, 0, 1);
    add_edge_wt(g, 2, 5, 1);
    add_edge_wt(g, 3, 5, 1);
    add_edge_wt(g, 3, 6, 1);
    add_edge_wt(g, 4, 6, 1);
    add_edge_wt(g, 6, 5, 1);
}

void mst(graph *g, int s)
{
    /*
     * struct PriorityQueue *PQ = CreatePriorityQueue();
     * int v, w;
     * EnQueue(PQ, s);
     * Distances[s] = 0;
     * while (!IsEmptyQueue(PQ)) {
     *     v = DeleteMin(PQ);
     *     for all adjacent vertices w of v {
     *         Compute new distance d = Distance[v] + weight[v][w];
     *         if (Distance[w] == -1) {
     *             Distance[w] = weight[v][w];
     *             Insert w in the priority queue with priority d
     *             Path[w] = v;
     *         }
     *         if (Distance[w] > new distance d) {
     *             Distance[w] = weight[v][w];
     *             Update priority of vertex w to be d;
     *             Path[w] = v;
     *         }
     *     }
     * }
     *
     */
}

void mst_test()
{
    graph *g = create(7);
}

