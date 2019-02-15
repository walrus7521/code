#include <stdio.h> 
#include <stdlib.h> 
  
struct adj_list_node { 
    int dest; 
    struct adj_list_node* next; 
}; 

struct adj_list { 
    struct adj_list_node *head;  
}; 
  
struct Graph { 
    int V; // this will be the size of the adjacency list
    struct adj_list* array; 
}; 
  
struct adj_list_node* new_adj_list_node(int dest) 
{ 
    struct adj_list_node* node = (struct adj_list_node*) malloc(sizeof(struct adj_list_node));
    node->dest = dest; 
    node->next = NULL; 
    return node; 
} 
  
struct Graph* new_graph(int V) 
{ 
    int i; 
    struct Graph* graph =  
        (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->V = V; 
    graph->array =  (struct adj_list*) malloc(V * sizeof(struct adj_list));
    for (i = 0; i < V; ++i) graph->array[i].head = NULL; // make each adj list empty
  
    return graph; 
} 
  
// Adds an edge to an undirected graph 
void add_edge(struct Graph* graph, int src, int dest) 
{ 
    // Add an edge from src to dest.  A new node is  
    // added to the adjacency list of src.  The node 
    // is added at the begining 
    struct adj_list_node* node = new_adj_list_node(dest); 
    node->next = graph->array[src].head; 
    graph->array[src].head = node; 
  
    // Since graph is undirected, add an edge from 
    // dest to src also 
    node = new_adj_list_node(src); 
    node->next = graph->array[dest].head; 
    graph->array[dest].head = node; 
} 
  
void show_graph(struct Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->V; ++v) { 
        struct adj_list_node* pCrawl = graph->array[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl) { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 
  
int main() 
{ 
    int V = 5; 
    struct Graph* graph = new_graph(V); 
    add_edge(graph, 0, 1); 
    add_edge(graph, 0, 4); 
    add_edge(graph, 1, 2); 
    add_edge(graph, 1, 3); 
    add_edge(graph, 1, 4); 
    add_edge(graph, 2, 3); 
    add_edge(graph, 3, 4); 
  
    show_graph(graph); 
  
    return 0; 
} 

