#include <stdio.h>
#include <limits.h>

#define MAXV        32
#define MAXDEGREE   32

typedef char bool;
enum {FALSE=0, TRUE=1}; 

typedef struct {
    int weight[MAXV+1][MAXV+1];
    int nvertices;
} adjacency_matrix;

void initialize_adjacency_matrix(adjacency_matrix *g)
{
    int i, j;
    g->nvertices = 0;
    for (i = 1; i <= MAXV; i++)
        for (j = 1; j <= MAXV; j++)
            g->weight[i][j] = INT_MAX;
}

void read_adjacency_matrix(adjacency_matrix *g, int directed)
{
    int i, m, x, y, w;
    initialize_adjacency_matrix(g);
    scanf("%d %d\n", &(g->nvertices), &m);
    for (i = 1; i <= m; i++) {
        scanf("%d %d %d\n", &x, &y, &w);
        g->weight[x][y] = w;
        if (directed == 0) g->weight[y][x] = w;
    }
}

void floyd(adjacency_matrix *g)
{
    int i, j, k, through_k;
    for (k = 1; k <= g->nvertices; k++)
        for (i = 1; i <= g->nvertices; i++)
            for (j = 1; j <= g->nvertices; j++) {
                through_k = g->weight[i][k]+g->weight[k][j];
                if (through_k < g->weight[i][j])
                    g->weight[i][j] = through_k;
            }
}


int main()
{
    return 0;
}
