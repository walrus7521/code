#include <stdio.h>


#define INF (99999999)
#define MAX_VERT (16)
typedef struct graph {
    int n_vert;
    int m[MAX_VERT][MAX_VERT];
    int parent[MAX_VERT];
    int visited[MAX_VERT];
} graph_t;


void init(graph_t *g)
{
    int i;
    for (i = 0; i < g->n_vert; i++) {
        g->parent[i] = -1, g->visited[i] = 0;
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

int queue[32];
int head=0,tail=0;
void bfs(graph_t *g, int v) 
{
    int i;
    queue[tail++] = v;
    g->visited[v] = 1;
    while (tail != head) {
        v = queue[head++]; printf("bfs: %d\n", v);
        for (i = 0; i < g->n_vert; i++) {
            if (g->m[v][i] && !g->visited[i]) {
                queue[tail++] = i;
                g->visited[i] = 1;
                g->parent[i] = v;
            }
        }
    }
#if 1
    printf("\n The vertices which are reachable from %d are:\n\n", v); 
    for (i=0;i<g->n_vert;i++)
        if(g->visited[i]) printf("%d\t",i);
    printf("\n");
    find_path(0, 3, g->parent);
#endif
}

int main()
{
    graph_t g = {.n_vert = 4, /* directed graph */
                 { { 0, 1, 1, 0 }, 
                   { 0, 0, 0, 1 }, 
                   { 0, 0, 0, 1 }, 
                   { 0, 0, 0, 0 } } };

    init(&g);
    bfs(&g, 2);
}

