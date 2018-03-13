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

<<<<<<< HEAD
void dfs(graph_t *g, int start)
{
    int v;
    int i;
    init(g);
    ring[head++] = start;
    g->visited[start] = 1;
    while (head != 0)
    {
        v = ring[--head];
        if (!g->visited[v]) {
            printf("v: %d\n", v);
            g->visited[v] = 1;
        }
        for (i = 0; i < g->n_vert; i++) {
            if (g->m[v][i] == 1 && !g->visited[i]) {
                ring[head++] = i;
                g->visited[i] = 1;
                g->parent[i] = v;
=======
// unconfirmed
void dfs(graph_t *g, int start)
{
    int i, v;
    init(g);
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
>>>>>>> 128e7655929dfc25db38deb44481c513b1328a0d
            }
        }
    }
}

<<<<<<< HEAD
=======

>>>>>>> 128e7655929dfc25db38deb44481c513b1328a0d
int main() {
    graph_t g = {.n_vert = 4, /* directed graph */
                  { { 0, 1, 1, 0 }, 
                    { 0, 0, 1, 0 }, 
                    { 1, 0, 0, 1 }, 
                    { 0, 0, 0, 1 } } };
     
    int start = 2;
    //bfs(&g, start);
<<<<<<< HEAD
    dfs(&g, start);
    return 0;
=======
    dfs(&g, 0);
>>>>>>> 128e7655929dfc25db38deb44481c513b1328a0d

    printf("\n The vertices which are reachable from %d are:\n\n", start); 
    for (int i=0;i<g.n_vert;i++)
        if(g.visited[i]) printf("%d\t",i);
    printf("\n");
    find_path(0, 4, g.parent);
    show(&g);
}

