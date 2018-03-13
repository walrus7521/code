#include "types.h"

void show(graph_t *g) {
    for (int i = 0; i < g->n_vert; i++) {
        for (int j = 0; j < g->n_vert; j++) { printf("%d, ", g->m[i][j]); }
        printf("\n");
    }
}

void find_path(int start, int end, int parents[]) {
    printf("start %d, end %d\n", start, end);
    if ((start == end) || (end == -1))
        printf("{start => %02d\n", start);
    else {
        find_path(start, parents[end], parents);
        printf("          %02d <=\n", end);
    }
}

void init(graph_t *g) {
    for (int i = 0; i < g->n_vert; i++) {
        g->parent[i] = -1, g->visited[i] = 0;
    }
}

int ring[32];
int head=0,tail=0;
void bfs(graph_t *g, int start) {
    int v;
    init(g);
    ring[tail++] = start;
    g->visited[start] = 1;
    while (tail != head) {
        v = ring[head++]; printf("v: %d\n", v);
        for (int i = 0; i < g->n_vert; i++) {
            if (g->m[v][i] == 1 && !g->visited[i]) {
                ring[tail++] = i;
                g->visited[i] = 1;
                g->parent[i] = v;
            }
        }
    }
}

// unconfirmed
int D[32];
int final[32];
void dijkstra(graph_t *g, int start)
{
    int i, v, w, min, n;
    init(g);

    n = g->n_vert;
    D[0] = 0;
    final[0] = 1;
    for (v = 1; v < n; v++) {
        final[v] = 0;
        D[v] = g->m[0][v];
    }

    for (i = 1; i < n; i++) {
        min = 9999999; // infinity
        for (w = 1; w < n; w++) {
            if (!final[w]) {
                if (D[w] < min) {
                    v = w;
                    min = D[w];
                }
            }
        }
        final[v] = 1;

        for (w = 1; w < n; w++) {
            if (!final[w]) {
                if (min + g->m[v][w] < D[w]) {
                    D[w] = min + g->m[v][w];
                }
            }
        }
    }

    // now look at distance and final
    for (i = 0; i < n; i++) {
        printf("final[%d] = %d\n", i, final[i]);
        printf("D[%d] = %d\n", i, D[i]);
    }
    return;
}

void dfs(graph_t *g, int start)
{
    int i, v;
    ring[head++] = start;
    //g->visited[start] = 1;
    while (head != 0) {
        v = ring[--head];
        for (i = 0; i < g->n_vert; i++) {
            if (g->m[v][i] == 1) {
                if (g->visited[i] == 0) {
                    g->visited[i] = 1;
                    g->parent[i] = v;
                    ring[head++] = i;
                    printf("u: %d\n", i);
                } else {
                    printf("u,v: %d,%d\n", v, i);
                }
            }
        }
    }
}

int main() {
    graph_t g = {.n_vert = 4, /* directed graph */
                  { { 0, 1, 1, 0 }, 
                    { 0, 0, 1, 0 }, 
                    { 1, 0, 0, 1 }, 
                    { 0, 0, 0, 1 } } };

    graph_t g2 = {.n_vert = 5, /* directed graph */
                  { { 0, 5, 3, 0, 2 }, 
                    { 0, 0, 2, 6, 0 }, 
                    { 0, 1, 0, 2, 0 }, 
                    { 0, 0, 0, 0, 0 }, 
                    { 0, 6, 10, 4, 0 } } };
     
    int start = 2;
    //bfs(&g, start);
    //dfs(&g2, 0);
    dijkstra(&g2, 0);
    return 0;

    printf("\n The vertices which are reachable from %d are:\n\n", start); 
    for (int i=0;i<g.n_vert;i++)
        if(g.visited[i]) printf("%d\t",i);
    printf("\n");
    find_path(0, 4, g.parent);
    show(&g);
}

