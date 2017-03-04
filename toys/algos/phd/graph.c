#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE_RING 32
#define SIZE_STAK 32
typedef int e_v;
#include "ring.inc"
#include "stak.inc"


#define dprintf(...)

#define MAXV        100
#define MAXDEGREE   50

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

void initialize_graph(graph *g);
void insert_edge(graph *g, int x, int y, int directed);

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

void initialize_graph(graph *g)
{
    int i, j;
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

void print_graph(graph *g)
{
    int i, j;
    for (i = 1; i < g->nvertices; i++) {
        printf("%d: ", i);
        for (j = 0; j < g->degree[i]; j++)
            printf(" %d", g->edges[i][j].v);
        printf("\n");
    }
}

void find_path(int start, int end, int parents[])
{
    int i;
    for (i = 0; i < MAXV; i++)
        dprintf("parent[%d] = %d\n", i, parent[i]);

    if ((start == end) || (end == -1))
        printf("{start => %02d\n", start);
    else {
        find_path(start, parents[end], parents);
        printf("          %02d <=\n", end);
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
    int v, i, p;
    dprintf("bfs - enter\n");

    init_ring();
    rngput(start);
    
    discovered[start] = 1;
    while (!rngempty()) {
        v = rngget();
        process_vertex(v);
        processed[v] = 1;
        for (i = 0; i < g->degree[v]; i++) {
            if (valid_edge(g->edges[v][i].v) == 1) {
                if (discovered[g->edges[v][i].v] == 0) {
                    rngput(g->edges[v][i].v);                   
                    discovered[g->edges[v][i].v] = 1;
                    p = g->edges[v][i].v;
                    dprintf("p = %d\n", p);
                    parent[g->edges[v][i].v] = v;
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

void connected_components(graph *g)
{
    int i, c;
    initialize_search(g);
    c = 0;
    for (i = 1; i < g->nvertices; i++) {
        if (discovered[i] == 0) {
            c = c + 1;
            printf("Component %d: ", c);
            dfs(g, i);
            printf("\n");
        }
    }
}

void compute_indegrees(graph *g, int in[])
{
    int i, j;
    for (i = 1; i <= g->nvertices; i++) in[i] = 0;
    for (i = 1; i <= g->nvertices; i++) {
        for (j = 0; j < g->degree[i]; j++) {
            in[g->edges[i][j].v]++;
        }
    }
}

#if 0
void topsort(graph *g, int sorted[])
{
    int indegree[MAXV];
    queue zeroin;
    int x, y;
    int i, j;

    compute_indegrees(g, indegree);
    init_queue(&zeroin);
    for (i = 1; i < g->nvertices; i++)
        if (indegree[i] == 0) enqueue(&zeroin, i);

    j = 0;
    while (!empty(&zeroin)) {
        j = j + 1;
        x = dequeue(&zeroin);
        sorted[j] = x;
        for (i = 0; i < g->degree[x]; i++) {
            y = g->edges[x][i].v;
            indegree[y]--;
            if (indegree[y] == 0) enqueue(&zeroin, y);
        }
    }

    if (j != g->nvertices) {
        printf("Not a DAG -- only %d vertices found\n", j);
    } else {
        printf("Woohoo got a DAG -- %d vertices found\n", j);
    }

}
#endif

void prim(graph *g, int start)
/* requires weights */
{
    int i, j;
    bool intree[MAXV];
    int distance[MAXV];
    int parent[MAXV];
    int v, w, weight, dist;

    for (i = 1; i <= g->nvertices; i++) {
        intree[i] = FALSE;
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[start] = 0;
    v = start;

    while (intree[v] == FALSE) {
        intree[v] = TRUE;
        for (i = 0; i < g->degree[v]; i++) {
            w = g->edges[v][i].weight;
            weight = g->edges[v][i].weight;
            if ((distance[w] > weight) && (intree[w] == FALSE)) {
                distance[w] = weight;
                parent[w] = v;
            }
        }

        v = 1;
        dist = INT_MAX;
        for (i = 2; i <= g->nvertices; i++)
            if ((intree[i] == FALSE) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
            }
    }
}

void dijkstra(graph *g, int start)
/* requires weights */
{
    int i, j;
    bool intree[MAXV];
    int distance[MAXV];
    int parent[MAXV];
    int v, w, weight, dist;

    for (i = 1; i <= g->nvertices; i++) {
        intree[i] = FALSE;
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[start] = 0;
    v = start;

    while (intree[v] == FALSE) {
        intree[v] = TRUE;
        for (i = 0; i < g->degree[v]; i++) {
            w = g->edges[v][i].weight;
            weight = g->edges[v][i].weight;
            if (distance[w] > (distance[v] + weight)) {
                distance[w] = distance[v] + weight;
                parent[w] = v;
            }
        }

        v = 1;
        dist = INT_MAX;
        for (i = 2; i <= g->nvertices; i++)
            if ((intree[i] == FALSE) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
            }
    }
}

int main()
{
    int start, end, sorted[MAXV];
    graph *g = (graph *) malloc(sizeof(graph));
    read_graph(g, 1);
    print_graph(g);
    initialize_search(g);
    start = 1;
    end = 4;
    //connected_components(g);
    //topsort(g, sorted);
    //dfs(g, start);
    bfs(g, start);
    printf("shortest path from %d to %d\n", start, end);
    find_path(start, end, parent);
    //printf("}\n");
    //printf("nedges = %d\n", nedges);
    return 0;
}

