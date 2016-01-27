#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef int e_v;
#include "queue.h"
//#include "../toys/queue.h"

#define dprintf(...)

#define MAXV        200
#define MAXDEGREE   8

typedef char bool;
enum {FALSE=0, TRUE=1}; 

typedef struct {
    int v;
    int weight;
} edge;

typedef struct {
    edge edges[MAXV+1][MAXDEGREE];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
} graph;

int processed[MAXV+1];
int discovered[MAXV+1];
int parent[MAXV+1];
int nedges;
int finished;

void initialize_graph(graph *g)
{
    int i;
    memset(g, sizeof(graph), 0);
    g->nvertices = 0;
    g->nedges = 0;
    nedges = 0;
    for (i = 0; i <= MAXV; i++) {
        g->degree[i] = 0;
    }
}

void initialize_search(graph *g)
{
    int i;
    nedges = 0;
    finished = 0;
    for (i = 1; i <= g->nvertices; i++) {
        processed[i] = discovered[i] = 0;
        parent[i] = -1;
    }
}

void insert_edge(graph *g, int x, int y, int directed)
{
    if (g->degree[x] > MAXDEGREE)
        printf("warning: insertion(%d,%d) exceeds max degree\n", x, y);
    g->edges[x][g->degree[x]].v = y;
    g->degree[x]++;

    if (directed == 0)
        insert_edge(g, y, x, 1);
    else
        g->nedges++;
}

int is_connected(graph *g, int x, int y)
{
    int i;
    for (i = 0; i < g->degree[x]; i++) {
        if (g->edges[x][i].v == y) return 1;
    }
    return 0;
}

void print_graph(graph *g)
{
    int i, j;
    printf("printing graph...\n");
    for (i = 1; i <= g->nvertices; i++) {
        printf("%02d: ", i);
        for (j = 0; j < g->degree[i]; j++)
            printf(" (%02d %02d), ", i, g->edges[i][j].v);
        printf("\n");
    }
}

void read_graph(graph *g, int directed)
{
    int i, m, x, y;
    initialize_graph(g);
    scanf("%d %d", &(g->nvertices), &m);
    for (i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        insert_edge(g, x, y, directed);
    }
}

void find_path(int start, int end, int parents[])
{
    int i;
    for (i = 0; i < MAXV; i++)
        dprintf("parents[%d] = %d\n", i, parents[i]);

    printf("parent[%d] = %d\n", end, parents[end]);

    if ((start == end) || (end == -1))
        printf("\n%d,", start);
    else {
        find_path(start, parents[end], parents);
        printf(" %d,", end);
    }
}

int valid_edge(int v)
{
    return 1;
}

void process_vertex(int v)
{
    dprintf("processed vertex %d\n", v);
}

void process_edge_bfs(int v, int w)
{
    dprintf("processed edge (%d, %d)\n", v, w);
    nedges = nedges + 1;
}

void process_edge_cycle(int x, int y)
{
#if 1
    if (parent[x] != y) {
        printf("cycle from %d to %d: ", x, y);
        find_path(y, x, parent);
        //finished = 1;
    }
    printf(" }\n");
#endif
}

void bfs(graph *g, int start)
{
    queue q;
    link *t;
    int v, i, p;
    printf("bfs - enter\n");
    init_queue(&q);
    enqueue(&q, start);
    discovered[start] = 1;
    while (!empty(&q)) {
        t = dequeue(&q);
        v = t->value;
        process_vertex(v);
        processed[v] = 1;
        for (i = 0; i < g->degree[v]; i++) {
            if (valid_edge(g->edges[v][i].v) == 1) {
                if (discovered[g->edges[v][i].v] == 0) {
                    enqueue(&q, g->edges[v][i].v);
                    discovered[g->edges[v][i].v] = 1;
                    p = g->edges[v][i].v;
                    printf("bfs - found (v=%d, p=%d)\n", v, p);
                    parent[g->edges[v][i].v] = v;
                    //printf("p[%d] = %d\n", p, v);
                }
                if (processed[g->edges[v][i].v] == 0)
                    process_edge_bfs(v, g->edges[v][i].v);
            }
        }
    }
}

void dfs(graph *g, int v)
{
    int i, y;

    if (finished) return;

    discovered[v] = 1;
    process_vertex(v);

    for (i = 0; i < g->degree[v]; i++) {
        y = g->edges[v][i].v;
        if (valid_edge(g->edges[v][i].v) == 1) {
            if (discovered[y] == 0) {
                parent[y] = v;
                dfs(g, y);
            } else {
                if (processed[y] == 0) {
                    process_edge_cycle(v, y);
                }
            }
        }
        if (finished) return;
    }
    processed[v] = 1;
}

graph *graph_create()
{
    graph *g = (graph *) malloc(sizeof(graph));
    initialize_graph(g);
    return g;
}
