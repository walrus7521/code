#include <stdio.h>
#include <stdlib.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

#define dprintf printf
//#define dprintf(...)

/* Queue - Begin
 */

typedef struct _link {
    struct _link *next;
    int value;
} link;

typedef struct {
    int count;
    link *front, *rear;
} queue;
#define queue_empty(head) ((head)->count == 0)

void enqueue(queue *q, int x)
{
    dprintf("enqueue %d\n", x);
    link *t = (link *) malloc(sizeof(link));
    t->value = x;    
    t->next = NULL;
    if (queue_empty(q)) {
        q->front = q->rear = t;
    } else {
        q->rear->next = t;
        q->rear = t;
    }
    q->count++;
}

int dequeue(queue *q)
{
    int x;
    link *t;
    if (queue_empty(q)) return -1;
    t = q->front;
    q->front = q->front->next;
    q->count--;
    if (queue_empty(q)) q->rear = NULL;
    x = t->value;
    free(t);
    dprintf("dequeue %d\n", x);
    return x;
}

void init_queue(queue *q)
{
    q->front = q->rear = NULL;
    q->count = 0;
}

/* Queue - End
 */



#define TRUE    1
#define FALSE   0

typedef int bool;

#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */


typedef struct {
	int v;				/* neighboring vertex */
	int capacity;			/* capacity of edge */
	int flow;			/* flow through edge */
	int residual;			/* residual capacity of edge */
} edge;

typedef struct {
	edge edges[MAXV][MAXDEGREE];	/* adjacency info */
	int degree[MAXV];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} flow_graph;



void initialize_graph(flow_graph* g)
{
	int i;				/* counter */

	g->nvertices = 0;
	g->nedges = 0;

	for (i=0; i<MAXV; i++) g->degree[i] = 0;
}

void insert_flow_edge(flow_graph *g, int x, int y, bool directed, int w)
{
	if (g->degree[x] > MAXDEGREE)
		printf("Warning: insertion(%d,%d) exceeds degree bound\n",x,y);

	g->edges[x][g->degree[x]].v = y;
	g->edges[x][g->degree[x]].capacity = w;
	g->edges[x][g->degree[x]].flow = 0;
	g->edges[x][g->degree[x]].residual = w;
	g->degree[x] ++;

	if (directed == FALSE)
		insert_flow_edge(g,y,x,TRUE,w);
	else
		g->nedges ++;
}

void read_flow_graph(flow_graph *g, bool directed)
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x,y,w;			/* placeholder for edge and weight */

	initialize_graph(g);

	scanf("%d %d\n",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d %d\n",&x,&y,&w);
		insert_flow_edge(g,x,y,directed,w);
	}
}

bool valid_edge(edge e)
{
	if (e.residual > 0) return (TRUE);
	else return(FALSE);
}

void process_vertex(int v)
{
}

void process_edge(int x, int y)
{
}

edge *find_edge(flow_graph *g, int x, int y)
{
	int i;				/* counter */

	for (i=0; i<g->degree[x]; i++) 
		if (g->edges[x][i].v == y) 
			return( &g->edges[x][i] );

	return(NULL);
}


void add_residual_edges(flow_graph *g)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) 
		for (j=0; j<g->degree[i]; j++)
			if (find_edge(g,g->edges[i][j].v,i) == NULL)
				insert_flow_edge(g,g->edges[i][j].v,i,TRUE,0);
}


void print_flow_graph(flow_graph *g)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		for (j=0; j<g->degree[i]; j++)
			printf(" %d(%d,%d,%d)",g->edges[i][j].v,
				g->edges[i][j].capacity,
				g->edges[i][j].flow,
				g->edges[i][j].residual);
		printf("\n");
	}
}

bool processed[MAXV];		/* which vertices have been processed */
bool discovered[MAXV];          /* which vertices have been found */
int parent[MAXV];		/* discovery relation */

bool finished = FALSE;          /* if true, cut off search immediately */


void initialize_search(flow_graph *g)
{
        int i;                          /* counter */

        for (i=1; i<=g->nvertices; i++) {
                processed[i] = FALSE;
                discovered[i] = FALSE;
                parent[i] = -1;
        }
}


void bfs(flow_graph *g, int start)
{
	queue q;			/* queue of vertices to visit */
	int v;				/* current vertex */
	int i;				/* counter */

	init_queue(&q);
	enqueue(&q,start);
	discovered[start] = TRUE;

	while (queue_empty(&q) == 0) {
		v = dequeue(&q);
		process_vertex(v);
		processed[v] = TRUE;
		for (i=0; i<g->degree[v]; i++) 
		    if (valid_edge(g->edges[v][i]) == TRUE) {
			if (discovered[g->edges[v][i].v] == FALSE) {
				enqueue(&q,g->edges[v][i].v);
				discovered[g->edges[v][i].v] = TRUE;
				parent[g->edges[v][i].v] = v;
			}
			if (processed[g->edges[v][i].v] == FALSE) 
				process_edge(v,g->edges[v][i].v);
		    }
	}
}


void find_path(int start, int end,int parents[])
/* int start;      	first vertex on path */
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
	edge *e;			/* edge in question */
	edge *find_edge();

	if (parents[end] == -1) return(0);

	e = find_edge(g,parents[end],end);

	if (start == parents[end])
		return(e->residual);
	else
		return( min(path_volume(g,start,parents[end],parents), e->residual) );
}


void augment_path(flow_graph *g, int start, int end, int parents[], int volume)
{
	edge *e;			/* edge in question */
	edge *find_edge();

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
	int volume;			/* weight of the augmenting path */

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
	flow_graph g;			/* graph to analyze */
	int source, sink;		/* source and sink vertices */
	int flow;			/* total flow */
	int i;				/* counter */

	scanf("%d %d",&source,&sink);
	read_flow_graph(&g,TRUE);

	netflow(&g,source,sink);

	print_flow_graph(&g);

	flow = 0;
	for (i=0; i<g.nvertices; i++)
		flow += g.edges[source][i].flow;

	printf("total flow = %d\n",flow);
    return 0;
}



