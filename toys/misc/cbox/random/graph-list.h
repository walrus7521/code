#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxV 1000

typedef struct _g_node {
    int v;
    struct _g_node *next;
} g_node;

typedef g_node* e_v;
#include "slist.h"

typedef struct _graph {
    int v;
    int e;
    struct _g_node **adj;//[maxV];
    int *visited;
    int *indegree;
    int *toporder;
} graph;

int graph_index(char c)
{
    return c - 'A' + 1;
}

char graph_name(int i)
{
    return 'A' + i - 1;
}

graph *create(int vertices)
{
    int v;
    graph *g;
    g_node **adj;
    g = (graph *) malloc(sizeof(graph));
    adj = (g_node **) malloc((vertices+1) * sizeof(g_node *));
    g->adj = adj;
    g->v = vertices;
    for (v = 1; v <= vertices; v++) {
        g->adj[v] = NULL;
    }
    g->visited  = (int *) malloc(sizeof(int) * vertices);
    //printf("successfully created graph with %d vertices\n", g->v);
    return g;
}

void add_edge_wt(graph *g, int u, int v, int wt)
{
    g_node *t = (g_node *) malloc(sizeof(g_node));
    t->v = v; 
    t->next = g->adj[u]; 
    g->adj[u] = t;
    g->e++;
}

int id = 0;
int val[maxV];
void dfsvisit(graph *g, int k, int goal)
{
    g_node *t;
    val[k] = ++id;
    if (k == goal) {
        printf(":1: found the goal: from %c to %c\n", graph_name(k), graph_name(goal));
        return;
    }
    for (t = g->adj[k]; t != NULL; t = t->next)
        if (val[t->v] == 0) {
            printf(" %c ", graph_name(t->v));
            if (t->v == goal) {
                printf(":2: found the goal: from %c to %c\n", graph_name(k), graph_name(goal));
                return;
            }
            dfsvisit(g, t->v, goal);
        }
}

void listdfs(graph *g)
{
    int k, goal = 5;
    for (k = 1; k <= g->v; k++) val[k] = 0;
    for (k = 1; k <= g->v; k++)
        if (val[k] == 0) {
            printf("start the dfs on %c:\n", graph_name(k));
            dfsvisit(g, k, goal);
            printf("\n");
        }
}

void bfsvisit(graph *g, int k, int goal)
{
    g_node *t;
    link *l;
    int u;
    list *que = slist_init();
    t = g->adj[k];
    slist_push_back(que, t);
    while (!slist_empty(que)) {
        l = slist_pop_front(que);
        t = l->value;
        u = t->v;
        val[u] = ++id;
        for(t = g->adj[u]; t != NULL; t = t->next) {
            if (val[t->v] == 0) {
                printf(" %c ", graph_name(t->v));
                if (t->v == goal) {
                    //printf(":2: found the goal: from %c to %c\n", graph_name(k), graph_name(goal));
                }
                slist_push_back(que, t);
                val[t->v] = -1;
            }
        }
    }
}

void listbfs(graph *g)
{
    int k, goal = 5;
    for (k = 1; k <= g->v; k++) val[k] = 0;
    for (k = 1; k <= g->v; k++) 
        if (val[k] == 0) {
            printf("start the bfs on %c: ", graph_name(k));
            bfsvisit(g, k, goal);
            printf("\n");
        }
}

void show(graph *g)
{
    int u;
    char v1, v2;
    g_node *t;
    for (u = 1; u <= g->v; u++) {
        //printf(" %02d %c :=> ", u, u + 'A' - 1);
        printf(" %02d :=> ", u);
        t = g->adj[u];
        while (t) {
            printf("(%d %d), ", u, t->v);
//            v1 = graph_name(u);
//            v2 = graph_name(t->v);
//            printf("(%c %c), ", v1, v2);
            t = t->next;
        }
        printf("\n");
    }
    for (u = 1; u <= g->v; u++) {
        //printf("dfs[%c] = %c\n", graph_name(u), graph_name(val[u]));
        //printf("dfs[%d] = %d\n", u, val[u]);
    }
}

void read_graph(graph *g)
/*
 * format is:
 * V E # integers
 * A B # upper case chars as vertices
 * C B # A = 1, B = 2, ...
 */
{
    int j, x, y, V, E, wt;
    char v1, v2;
    scanf("%d %d\n", &V, &E);
    printf("V=%d, E=%d\n", V, E);
    for (j = 1; j <= E; j++) {
        scanf("%c %c %d\n", &v1, &v2, &wt);
        x = graph_index(v1); y = graph_index(v2);
        printf("v1 = %c => %d, v2 = %c => %d: weight %d\n", v1, x, v2, y, wt);
        add_edge_wt(g, x, y, wt);
        add_edge_wt(g, y, x, wt);
    }

}

int graph_list_test()
{
    graph *g = create(10);
    read_graph(g);
    //listdfs(g);
    listbfs(g);
    show(g);
    return 0;
}
