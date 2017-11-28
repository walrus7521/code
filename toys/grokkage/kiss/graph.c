#include "types.h"

/*
    Breadth First Search
    Depth First Search
    Shortest Path from source to all vertices - Dijkstra
    Shortest Path from every vertex to every other vertex - Floyd Warshall
    Minimum Spanning tree - Prim
    Minimum Spanning tree - Kruskal
    Topological Sort
 */

void show(graph_t *g)
{
    printf("graph: %d\n", g->n_vert);
    for (int i = 0; i < g->n_vert; i++) {
        for (int j = 0; j < g->n_vert; j++) {
            printf("%d, ", g->m[i][j]);
        }
        printf("\n");
    }
}

void find_path(int start, int end, int parents[])
{
    printf("start %d, end %d\n", start, end);
    if ((start == end) || (end == -1))
        printf("{start => %02d\n", start);
    else {
        find_path(start, parents[end], parents);
        printf("          %02d <=\n", end);
    }
}

void init(graph_t *g)
{
    for (int i = 0; i < g->n_vert; i++) {
        g->parent[i] = -1;
        g->visited[i] = 0;
    }
}

void bfs()
{
    int start = 2;
    int v;
    graph_t g = {.n_vert = 4, /* directed graph */
                  { { 0, 1, 1, 0 }, 
                    { 0, 0, 1, 0 }, 
                    { 1, 0, 0, 1 }, 
                    { 0, 0, 0, 1 } } };
    init(&g);
    ring[tail++] = start;
    while (tail != head) {
        v = ring[head++];
        printf("v: %d\n", v);
        for (int i = 0; i < g.n_vert; i++) {
            if (g.m[v][i] == 1 && !g.visited[i]) {
                ring[tail++] = i;
                g.visited[i] = 1;
                g.parent[i] = v;
            }
        }
    }
    printf("\n The vertices which are reachable from %d are:\n\n", start); 
    for (int i=0;i<g.n_vert;i++)
        if(g.visited[i]) 
            printf("%d\t",i);
    printf("\n");
    find_path(0, 4, g.parent);
    show(&g);
}

int main()
{
    bfs();
}

