#include <stdio.h>

typedef struct graph {
    int n_vert; // verts
    int m[32][32];
} graph_t;

void topsort(graph_t *g)
{
    int i, j, k, indeg[32], flag[32], count=0;

    for (i = 0; i < g->n_vert; i++) {
        indeg[i]=0;
        flag[i]=0;
    }

    for(i = 0; i < g->n_vert; i++)
        for(j = 0; j < g->n_vert; j++)
            indeg[i] += g->m[j][i];

    printf("\ntopsort: ");
    while (count < g->n_vert) {
        for (k = 0; k < g->n_vert; k++) {
            if ((indeg[k] == 0) && (flag[k] == 0)){
                printf("%d ", (k+1));
                flag[k] = 1;
            }
 
            for(i = 0; i < g->n_vert; i++) {
                if (g->m[i][k] == 1)
                    indeg[k]--;
            }
        }
        count++;
    }
   
}

int main()
{
    graph_t g = {.n_vert = 4, /* directed graph */
                  { { 0,  1,  1,  0 }, 
                    { 0,  0,  0,  1 }, 
                    { 0,  0,  0,  1 }, 
                    { 0,  0,  0,  0 } } };
    topsort(&g);
    return 0;
}
