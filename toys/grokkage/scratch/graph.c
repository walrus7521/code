#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int w[][4] = { { 0, 1, 0, 0 }, 
               { 0, 0, 0, 1 }, 
               { 0, 0, 0, 0 }, 
               { 1, 0, 1, 0 } };


typedef struct vertex {
    int key;
    struct vertex *next;
} vertex_t;

typedef struct graph {
    int n_vertices;
    vertex_t **head;
} graph_t;

graph_t *new_graph(int n_vertices)
{
    graph_t *g = malloc(sizeof(graph_t));
    g->n_vertices = n_vertices;
    g->head = malloc(n_vertices * sizeof(vertex_t));
    return g;
}

vertex_t *new_vertex(int key)
{
    vertex_t *v = malloc(sizeof(vertex_t));
    v->key = key;
    v->next = NULL;
    return v;
}

void add_vertex(graph_t *g, vertex_t *v)
{
    vertex_t *t = g->head[v->key];
    g->head[v->key] = v;
    v->next = t;
}

void show(graph_t *g)
{
    printf("graph: %d\n", g->n_vertices);
    for (int i = 0; i < g->n_vertices; i++) {
        vertex_t *t = g->head[i];
        while (t) {
            printf("%d\n", t->key);
            t = t->next;
        }
    }
}

int main()
{
    graph_t *g = new_graph(42);
    vertex_t *v = new_vertex(1);
    add_vertex(g, v);
    show(g);
}

