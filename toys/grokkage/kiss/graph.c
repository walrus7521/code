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

int main() {
    graph_t g = {.n_vert = 4, /* directed graph */
                  { { 0, 1, 1, 0 }, 
                    { 0, 0, 1, 0 }, 
                    { 1, 0, 0, 1 }, 
                    { 0, 0, 0, 1 } } };
     
    int start = 2;
    bfs(&g, start);

    printf("\n The vertices which are reachable from %d are:\n\n", start); 
    for (int i=0;i<g.n_vert;i++)
        if(g.visited[i]) printf("%d\t",i);
    printf("\n");
    find_path(0, 4, g.parent);
    show(&g);
}

