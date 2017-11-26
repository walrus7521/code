#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_VERT (16)
typedef struct graph {
    int n_vert;
    int m[MAX_VERT][MAX_VERT];
    int que[MAX_VERT];
} graph_t;


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


