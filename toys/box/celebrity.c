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

int done[256] = {0};

int main()
{
    int celebrity;
    graph *g = (graph *) malloc(sizeof(graph));
    initialize_graph(g);
    g->nvertices = 96;
    celebrity = 52;
    for (int i = 1; i <=g->nvertices; i++) {
        if (i == celebrity) continue;
        insert_edge(g, i, celebrity, 1);
    }
    //print_graph(g);
    for (int i = 1; i <= g->nvertices; i++) {
        for (int j = 1; j <= g->nvertices; j++) {
            if (is_connected(g,i,j) && !is_connected(g,j,i)) {
                done[i] = 1;
            }
            else if (is_connected(g,j,i) && !is_connected(g,i,j)) {
                done[j] = 1;
            }
        }
    }
    for (int i = 1; i <= g->nvertices; i++) {
        if (done[i] == 0) {
            printf("the celebrity is %d\n", i);
        }
    }
}
