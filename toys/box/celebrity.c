#include <stdio.h>
#include "graph2.h"

/* 
 * Decrease-and-Conquer
 * create a graph where a celebrity is known by all
 * but knows no-one.  Find the celebrity.
 */


/*  #2 is the celebrity
 * 
 *   1 2 3 4
 * 1 0 0 0 0
 * 2 1 0 1 1
 * 3 0 0 0 0
 * 4 0 0 0 0
 */

int done[5] = {0};

// needs is_connected(g, x, y); algorithm

int main()
{
    int x, y;
    graph *g = (graph *) malloc(sizeof(graph));
    initialize_graph(g);
    x = 0, y = 0;
    g->nvertices = 4;
    insert_edge(g, 1, 2, 1);
    insert_edge(g, 3, 2, 1);
    insert_edge(g, 4, 2, 1);
    print_graph(g);
    for (int i = 1; i <= g->nvertices; i++) {
        for (int j = 1; j <= g->nvertices; j++) {
            if (g->edges[i][j] && !g->edges[j][i]) {
                done[i] = 1;
            }
            else if (g->edges[j][i] && !g->edges[i][j]) {
                done[j] = 1;
            }
        }
    }
}
