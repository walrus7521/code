#include <stdio.h>
#include <stdlib.h>
#include "flow.hpp"

// Notes: use flow4.in for true bipartite
// 0 1 0 1
// 1 0 1 0
// 0 1 0 1
// 1 0 1 0

using namespace std;

edge *find_edge(flow_graph *g, int x, int y)
{
    for (int i=0; i<g->degree[x]; i++) 
        if (g->edges[x][i].v == y) 
            return( &g->edges[x][i] );
    return(NULL);
}

void insert_flow_edge(flow_graph *g, int x, int y, bool directed, int w)
{
    printf("insert: edge(%d, %d)\n", x, y);
    if (g->degree[x] > MAXDEGREE)
        printf("Warning: insertion(%d,%d) exceeds degree bound\n",x,y);

    g->edges[x][g->degree[x]].v = y;
    g->edges[x][g->degree[x]].capacity = w;
    g->edges[x][g->degree[x]].flow = 0;
    g->edges[x][g->degree[x]].residual = w;
    g->degree[x]++;

    if (directed == false)
        insert_flow_edge(g,y,x,true,w);
    else
        g->nedges ++;
}

void add_residual_edges(flow_graph *g)
{
    for (int i=1; i<=g->nvertices; i++) 
        for (int j=0; j<g->degree[i]; j++)
            if (find_edge(g,g->edges[i][j].v,i) == NULL) {
                printf("adding residual edge(%d,%d)\n", 
                        g->edges[i][j].v, i);
                insert_flow_edge(g,g->edges[i][j].v,i,true,0);
            }
}


void print_flow_graph(flow_graph *g)
{
    for (int i=1; i<=g->nvertices; i++) {
        printf("%d: ",i);
        for (int j=0; j<g->degree[i]; j++)
            printf(" %d(%d,%d,%d)",g->edges[i][j].v,
                g->edges[i][j].capacity,
                g->edges[i][j].flow,
                g->edges[i][j].residual);
        printf("\n");
    }
}

void find_path(int start, int end,int parents[])
/* int start;       first vertex on path */
/* int end;         last vertex on path */
/* int parents[];   array of parent pointers */
{
    if ((start == end) || (end == -1))
        printf("\n%d",start);
    else {
        find_path(start,parents[end],parents);
        printf(" %d",end);
    }
}

int path_volume(flow_graph *g, int start, int end, int parents[])
{
    edge *e;            /* edge in question */
    if (parents[end] == -1) return(0);
    e = find_edge(g,parents[end],end);
    if (start == parents[end])
        return(e->residual);
    else
        return( min(path_volume(g,start,parents[end],parents), e->residual) );
}


void augment_path(flow_graph *g, int start, int end, int parents[], int volume)
{
    edge *e; /* edge in question */

    if (start == end) return;

    e = find_edge(g,parents[end],end);
    e->flow += volume;
    e->residual -= volume;
    
    e = find_edge(g,end,parents[end]);
    e->residual += volume;

    augment_path(g,start,parents[end],parents,volume);
}

void netflow(flow_graph *g, int source, int sink)
{
    int volume; /* weight of the augmenting path */
    add_residual_edges(g);
    initialize_search(g);
    bfs(g,source);
    volume = path_volume(g, source, sink, parent);
    while (volume > 0) {
        augment_path(g,source,sink,parent,volume);
        initialize_search(g);
        bfs(g,source);
        volume = path_volume(g, source, sink, parent);
    }
}

int main()
{
    flow_graph g;       /* graph to analyze */
    int source, sink;   /* source and sink vertices */
    int i;              /* counter */
    int m;              /* number of edges */
    int x,y,w;          /* placeholder for edge and weight */

    bool directed = true;

    initialize_graph(&g);

    scanf("%d %d",&source,&sink);
    scanf("%d %d\n",&g.nvertices, &m);
    for (i=1; i<=m; i++) {
        scanf("%d %d %d\n",&x,&y,&w);
        insert_flow_edge(&g,x,y,directed,w);
    }

    netflow(&g,source,sink);
    print_flow_graph(&g);

    int flow = 0; // total flow
    for (i=0; i<g.nvertices; i++)
        flow += g.edges[source][i].flow;

    printf("total flow = %d\n",flow);
    return 0;
}

