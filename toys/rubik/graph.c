#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _graph {
    int V;
    int **adj;
    int *parents;
    int *costs;
    bool *processed;
} graph_t;

#define INFINITY (9999)
#define NONE     (-1)

void init(graph_t *g, int V)
{
    g->V = V;
    g->adj = (int**) malloc(V * sizeof(int));
    g->parents = malloc(V * sizeof(int));
    g->costs = malloc(V * sizeof(int));
    g->processed = (bool*) malloc(V * sizeof(bool));
    for (int i = 0; i < V; i++) {
        g->parents[i] = NONE;
        g->processed[i] = false;
        g->costs[i] = INFINITY;
        g->adj[i] = (int*) malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            g->adj[i][j] = NONE;
        }
    }

}

void add_edge(graph_t *g, int u, int v, int wt)
{
    g->adj[u][v] = wt;
}

void show_graph(graph_t *g)
{
    for (int i = 0; i < g->V; i++) {
        printf("%d : ", i);
        for (int j = 0; j < g->V; j++) {
            if (g->adj[i][j] > -1) {
                printf("%d:%d ", j, g->adj[i][j]);
            }
        }
        printf("\n");
    }
}

void show_path(graph_t *g, int v)
{
    printf("%d ", g->parents[v]);
    for (int i = 0; i < g->V; i++) {
        printf("%d ", g->parents[i]);
    }
    printf("\n");
}

int find_lowest_cost_node(graph_t *g)
{
    int lowest_cost = INFINITY;
    int lowest_cost_node = NONE;
    for (int node = 0; node < g->V; node++) {
        int cost = g->costs[node];
        if (cost < lowest_cost && !g->processed[cost]) {
            lowest_cost = cost;
            lowest_cost_node = node;
        }
    }
    printf("low: %d\n", lowest_cost_node);
    return lowest_cost_node;
}

void dijkstra(graph_t *g)
{
    int node = find_lowest_cost_node(g);
    while (node != NONE) {
        int cost = g->costs[node];
        printf("d: node %d cost: %d\n", node, cost);
        for (int i = 0; i < g->V; i++) {
            int n = g->adj[node][i]; // neighbors of node
            if (n == NONE) continue;
            int new_cost = cost + n;
            if (g->costs[n] > new_cost) {
                g->costs[n] = new_cost;
                g->parents[n] = node;
            }
        }
        g->processed[node] = true;
        node = find_lowest_cost_node(g);
    }
}

int main()
{
    graph_t g;
    init(&g, 4);

    add_edge(&g, 0, 1, 6);
    add_edge(&g, 0, 2, 2);
    add_edge(&g, 1, 3, 1);
    add_edge(&g, 2, 1, 3);
    add_edge(&g, 2, 3, 5);
    g.costs[1] = 6;
    g.costs[2] = 2;
    g.costs[3] = INFINITY;
    g.parents[1] = 0;
    g.parents[2] = 0;
    g.parents[3] = NONE;

    dijkstra(&g);

    show_graph(&g);
    show_path(&g, 3);
}

