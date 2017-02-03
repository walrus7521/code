#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

typedef struct _graph {
    int v;
    int e;
    int **adj;
    int *visited;
    int *indegree;
    int *toporder;
    int connected_components;
    int cycles;
} graph;

int graph_index(char c)
{
    return c - 'A' + 1;
}

char graph_name(int i)
{
    return 'A' + i - 1;
}

int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

graph *create(int vertices)
{
    int u, v;
    graph *g = (graph *) malloc(sizeof(graph));
    g->adj = (int **) malloc(sizeof(int *) * vertices);
    g->v = vertices;
    for (v = 1; v <= vertices; v++) {
        g->adj[v] = (int *) malloc(sizeof(int) * vertices);
    }
    g->visited  = (int *) malloc(sizeof(int) * vertices);
    g->indegree = (int *) malloc(sizeof(int) * vertices);
    g->toporder = (int *) malloc(sizeof(int) * vertices);
    for (u = 1; u <= g->v; u++) {
        g->visited[u] = 0;
        g->indegree[u] = 0;
        g->toporder[u] = -1;
    }
    for (u = 1; u <= g->v; u++)
        for (v = 1; v <= g->v; v++)
            g->adj[u][v] = 0;
    return g;
}

void add_edge_wt(graph *g, int u, int v, int wt)
{
    g->adj[u][v] = wt;
    g->indegree[v]++;
    g->toporder[u] = 0;
    g->toporder[v] = 0;
    g->e++;
}
int id = 0;
void visit(graph *g, int k)
{
    int i;
    g->visited[k] = ++id;
    for(i = 1; i <= g->v; i++) {
        if (g->adj[k][i] != 0) {
            if(g->visited[i] == 0) {
                printf("visiting(%c %c\n", graph_name(k), graph_name(i));
                visit(g, i);
            } else {
                g->cycles++;
                printf("detected cycle! %c %c\n", graph_name(k), graph_name(i));
            }
        }
    }
}
 
void listdfs(graph *g)
{
    int k;
    g->cycles = 0;
    g->connected_components = 0;
    for (k = 1; k <= g->v; k++) g->visited[k] = 0;
    for (k = 1; k <= g->v; k++)
        if (g->visited[k] == 0) {
            printf("start the dfs on %c:\n", graph_name(k));
            g->connected_components++;
            visit(g, k);
        }
    printf("there are %d connected components\n", g->connected_components);
    printf("there are %d cycles\n", g->cycles);
}

void gdump(void *l)
{
    link *t = (link *) l;
    printf("list->value = %d\n", t->value);
}

void bfs_traverse(graph *g, int u)
/*
      ABCDEFGH
      --------
 0 A: 01000000
 1 B: 10100001
 2 C: 01011000
 3 D: 00100000
 4 E: 00100111
 5 F: 00001000
 6 G: 00001000
 7 H: 01001000
got A  putting B
got B  putting C
putting H
got B  got B  got D  got E  putting F
putting G
got B  got B
 *
 */
{
    int i;
    link *l;
    list *que = slist_init();
    slist_push_back(que, u);
    while (!slist_empty(que)) {
        l = slist_pop_front(que);
        u = l->value;
        if (u == -1) {
            printf("queue is empty!!\n");
            return;
        }
        printf("got %c  ", u + 'A');
        slist_show(que, gdump);
        g->visited[u] = 1;
        for(i = 1; i <= g->v; i++) {
            if (g->adj[u][i] != 0) {
                if (g->visited[i] == 0) {
                    printf("putting %c\n", i + 'A');
                    slist_push_back(que, i);
                    g->visited[i] = 1;
                }
            }
        }
    }
}
 
void bfs(graph *g)
{
    int i, j;
    for(j = 1; j <= g->v; j++)
        g->visited[j] = 0;
    for (i = 1; i <= g->v; i++) {
        if (g->visited[i] == 0) {
            bfs_traverse(g, i);
        }
    }
}

void topsort(graph *g) 
{
    link *l;
    list *que = slist_init();
    int v, w, counter = 0;
    for (v = 1; v <= g->v; v++) {
        if (g->indegree[v] == 0) {
            slist_push_back(que, v);
        }
    }
    while (!slist_empty(que)) {
        l = slist_pop_front(que);
        v = l->value;
        if (g->toporder[v] != -1) g->toporder[v] = ++counter;
        for (w = 1; w <= g->v; w++) {
            if (g->adj[v][w] == 1) {
                if (--g->indegree[w] == 0) {
                    slist_push_back(que, w);
                }
            }
        } 
    }
    if (counter != g->v) {
        printf("graph has a cycle\n");
    }

    qsort (g->toporder, g->v, sizeof(int), comp);
    for (v = 1; v <= g->v; v++) {
        if (g->toporder[v] == -1) continue;
        printf("top[%c] = %d\n", v + 'A', g->toporder[v]);
    }
}

void mst(graph *g)
{
    /*
     * struct PriorityQueue *PQ = CreatePriorityQueue();
     * int v, w;
     * EnQueue(PQ, s);
     * Distances[s] = 0;
     * while (!IsEmptyQueue(PQ)) {
     *     v = DeleteMin(PQ);
     *     for all adjacent vertices w of v {
     *         Compute new distance d = Distance[v] + weight[v][w];
     *         if (Distance[w] == -1) {
     *             Distance[w] = weight[v][w];
     *             Insert w in the priority queue with priority d
     *             Path[w] = v;
     *         }
     *         if (Distance[w] > new distance d) {
     *             Distance[w] = weight[v][w];
     *             Update priority of vertex w to be d;
     *             Path[w] = v;
     *         }
     *     }
     * }
     *
     */
}

#define INFINITY 9999
void shortest_path(graph *g) 
{
    int final[32], distance[32];
    int i, w, v, min;
    for (v = 1; v <= g->v; v++) {
        final[v] = 0;
        distance[v] = g->adj[0][v];
    }
    final[0] = 1;
    distance[0] = 0;
    for (i = 1; i <= g->v; i++) {
        min = INFINITY;
        for (w = 1; w <= g->v; w++) {
            if (!final[w]) {
                if (distance[w] < min) {
                    v = w;
                    min = distance[w];
                }
            }
        }
        final[v] = 1;
        for (w = 1; w <= g->v; w++) {
            if (!final[w]) {
                if (min + g->adj[v][w] < distance[w]) {
                    distance[w] = min + g->adj[v][w];
                }
            }
        }
    }
    for (w = 1; w <= g->v; w++) {
        printf("distance[%02d] = %02d\n", w, distance[w]);
    }
}

void shortest_path_unweighted(graph *g, int s)
{
    link *l;
    list *que = slist_init();
    int v, w;
    int distance[32], last_path_node_visited[32];
    slist_push_back(que, s);
    for (v = 1; v <= g->v; v++) {
        distance[v] = -1;
        last_path_node_visited[v] = -1;
    }
    distance[s] = 0;
    while (!slist_empty(que)) {
        l = slist_pop_front(que);
        v = l->value;
        for (w = 1; w <= g->v; w++) {
            if (g->adj[v][w] == 1) {
                if (distance[w] == -1) {
                    distance[w] = distance[v] + 1;
                    last_path_node_visited[w] = v;
                    slist_push_back(que, w);
                }
            }
        }
    }
    for (v = 1; v <= g->v; v++) {
        printf("distance[%c] = %02d\n", v + 'A', distance[v]);
    }
    for (v = 1; v <= g->v; v++) {
        printf("last_path_node_visited[%c] = %02d\n", v + 'A', last_path_node_visited[v]);
    }
}

void transitive_closure(graph *g)
{
    int x, y, j;
    for (y = 1; y <= g->v; y++) {
        for (x = 1; x <= g->v; x++) {
            if (g->adj[x][y] == 1) {
                for (j = 1; j <= g->v; j++) {
                    if (g->adj[y][j] == 1) {
                        g->adj[x][j] = 1;
                    }
                }
            }
        }
    }
}

void show(graph *g)
{
    int u, v;
    printf("       ");
    for (u = 1; u <= g->v; u++)
        printf("%c", u + 'A' - 1);
    printf("\n");
    for (u = 1; u <= g->v; u++) {
        printf(" %02d %c: ", u, u + 'A' - 1);
        for (v = 1; v <= g->v; v++) {
            printf("%d", g->adj[u][v]);
        }
        printf("\n");
    }
    for (u = 1; u <= g->v; u++) 
        printf("dfs[%c] = %c\n", graph_name(u), graph_name(g->visited[u]));
}

void bfs2(graph *g)
/*
 *      ABCDEFGH
 *       --------
 *  0 A: 01000000
 *  1 B: 10100001
 *  2 C: 01011000
 *  3 D: 00100000
 *  4 E: 00100111
 *  5 F: 00001000
 *  6 G: 00001000
 *  7 H: 01001000
 *
 *  BFS2: A B C H D E F G 
 * 
 */
{
    link *l;
    list *que = slist_init();
    int visited[8] = {0};
    int v, w;
    for (v = 1; v <= g->v; v++) {
        visited[v] = 0;
    }
    for (v = 1; v <= g->v; v++) {
        if (!visited[v]) {
            slist_push_back(que, v);
            do {
                l = slist_pop_front(que);
                v = l->value;
                if (!visited[v]) {
                    visited[v] = 1;
                    printf(" %c \n", v + 'A');
                }
                for (w = 1; w <= g->v; w++) {
                    if (g->adj[v][w] == 1) {
                        if (!visited[w]) {
                            slist_push_back(que, w);
                        }
                    }
                }
            } while (!slist_empty(que));
        }    
    } 
}

void init(graph *g)
/*
      ABCDEFGH
      --------
 0 A: 01000000
 1 B: 10100001
 2 C: 01011000
 3 D: 00100000
 4 E: 00100111
 5 F: 00001000
 6 G: 00001000
 7 H: 01001000
DFS[A]: !A  !B  !C  !D  !E  !F  !G  !H
DFS[B]: !B  !A  !C  !D  !E  !F  !G  !H
DFS[C]: !C  !B  !A  !H  !E  !F  !G  !D
DFS[D]: !D  !C  !B  !A  !H  !E  !F  !G
DFS[E]: !E  !C  !B  !A  !H  !D  !F  !G
DFS[F]: !F  !E  !C  !B  !A  !H  !D  !G
DFS[G]: !G  !E  !C  !B  !A  !H  !D  !F
DFS[H]: !H  !B  !A  !C  !D  !E  !F  !G

*/
{
    add_edge_wt(g, 1, 2, 1);
    add_edge_wt(g, 2, 1, 1);
    add_edge_wt(g, 2, 3, 1);
    add_edge_wt(g, 2, 8, 1);
    add_edge_wt(g, 3, 2, 1);
    add_edge_wt(g, 3, 4, 1);
    add_edge_wt(g, 3, 5, 1);
    add_edge_wt(g, 4, 3, 1);
    add_edge_wt(g, 5, 3, 1);
    add_edge_wt(g, 5, 6, 1);
    add_edge_wt(g, 5, 7, 1);
    add_edge_wt(g, 5, 8, 1);
    add_edge_wt(g, 6, 5, 1);
    add_edge_wt(g, 7, 5, 1);
    add_edge_wt(g, 8, 2, 1);
    add_edge_wt(g, 8, 5, 1);
}

void init_dag(graph *g)
/*
 *        ABCDEFGHIJ
 *  00 A: 0000000000
 *  01 B: 0000001010
 *  02 C: 0000000000
 *  03 D: 0000000001
 *  04 E: 0000000000
 *  05 F: 0000001001
 *  06 G: 0000000100
 *  07 H: 0000000000
 *  08 I: 0000000000
 *  09 J: 1000000110
 * graph has a cycle
 * top[A] = 6
 * top[B] = 1
 * top[D] = 2
 * top[F] = 3
 * top[G] = 4
 * top[H] = 7
 * top[I] = 8
 * top[J] = 5
 */
{
    add_edge_wt(g, 1, 6, 1);
    add_edge_wt(g, 1, 8, 1);
    add_edge_wt(g, 3, 9, 1);
    add_edge_wt(g, 5, 6, 1);
    add_edge_wt(g, 5, 9, 1);
    add_edge_wt(g, 6, 7, 1);
    add_edge_wt(g, 9, 0, 1);
    add_edge_wt(g, 9, 7, 1);
    add_edge_wt(g, 9, 8, 1);
}

void init_shortest_path_unweighted(graph *g)
/*
 * 
 *        ABCDEFG
 *  00 A: 0101000
 *  01 B: 0001100
 *  02 C: 1000010
 *  03 D: 0000011
 *  04 E: 0000001
 *  05 F: 0000000
 *  06 G: 0000010
 * distance[A] = 01
 * distance[B] = 02
 * distance[C] = 00
 * distance[D] = 02
 * distance[E] = 03
 * distance[F] = 01
 * distance[G] = 03
 * last_path_node_visited[A] = 02
 * last_path_node_visited[B] = 00
 * last_path_node_visited[C] = -1
 * last_path_node_visited[D] = 00
 * last_path_node_visited[E] = 01
 * last_path_node_visited[F] = 02
 * last_path_node_visited[G] = 03
 * 
 */
{
    add_edge_wt(g, 0, 1, 1);
    add_edge_wt(g, 0, 3, 1);
    add_edge_wt(g, 1, 3, 1);
    add_edge_wt(g, 1, 4, 1);
    add_edge_wt(g, 2, 0, 1);
    add_edge_wt(g, 2, 5, 1);
    add_edge_wt(g, 3, 5, 1);
    add_edge_wt(g, 3, 6, 1);
    add_edge_wt(g, 4, 6, 1);
    add_edge_wt(g, 6, 5, 1);
}

#define maxV 50
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
    for (x = 1; x <= V; x++) g->adj[x][x] = 1;
    for (j = 1; j <= E; j++) {
        scanf("%c %c %d\n", &v1, &v2, &wt);
        x = graph_index(v1); y = graph_index(v2);
        printf("v1 = %c => %02d, v2 = %c => %02d: weight %d\n", v1, x, v2, y, wt);
        add_edge_wt(g, x, y, wt);
        add_edge_wt(g, y, x, wt);
    }

}

int graph_matrix_test()
{
    graph *g = create(13);
    //init(g);
    read_graph(g);
    listdfs(g);
    show(g);
    //bfs2(g);

    /* topsort demo */
    //init_dag(g);
    //show(g);
    //topsort(g);
    //shortest_path(g);

    //init_shortest_path_unweighted(g);
    //show(g);
    //shortest_path_unweighted(g, 2);

    //init_dag(g);
    //show(g);
    //transitive_closure(g);

    //read_graph(g);
    //show(g);
    
    return 0;
}
