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

void bfs()
{
    graph_t g = {.n_vert = 4, 
                  { { 0, 1, 0, 0 }, 
                    { 0, 0, 0, 1 }, 
                    { 0, 0, 0, 0 }, 
                    { 1, 0, 1, 0 } } 
                };
    show(&g);
}

int main()
{
    bfs();
}


