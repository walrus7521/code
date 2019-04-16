#include "types.h"
#include "utils.h"
#include <float.h>
#include <limits.h>

void graph_show(graph_t *g, char *name)
{
    int i, j;
    printf("%s\n", name);
    for (i = 0; i < g->n_vert; i++) {
        for (j = 0; j < g->n_vert; j++) { 
            if (g->m[i][j] == INF) {
                printf("INF, ");
            } else {
                printf("%03d, ", g->m[i][j]);
            }
        }
        printf("\n");
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

void init(graph_t *g)
{
    int i;
    for (i = 0; i < g->n_vert; i++) {
        g->parent[i] = -1, g->visited[i] = 0;
    }
}

// unconfirmed
int D[32];
int final[32];
void dijkstra(graph_t *g, int start)
{
    int i, v, w, min, n;
    int found = 0;

    n = g->n_vert;
    D[0] = 0;
    final[0] = 1;
    for (v = 1; v < n; v++) {
        final[v] = 0;
        D[v] = g->m[0][v];
    }

    for (i = 1; i < n; i++) {
        found = 0;
        // find closest vertex to 0
        min = INF; // infinity
        for (w = 1; w < n; w++) {
            if (!final[w]) {
                if (D[w] < min) {
                    found = 1;
                    v = w;
                    min = D[w];
                    printf("min: %d\n", min);
                }
            }
        }
        // question, what if v was never modified?
        if (found) {
            printf("%d found %d min=%d\n", i, v, min);
        } else {
            printf("%d not found\n", i);
        }
        final[v] = 1; // add v to set S

        // update remaining distances
        for (w = 1; w < n; w++) {
            if (!final[w]) {
                if (min + g->m[v][w] < D[w]) {
                    D[w] = min + g->m[v][w];
                    printf("update D[%d]: %d\n", w, D[w]);
                }
            }
        }
    }

    // now look at distance and final
    for (i = 0; i < n; i++) {
        printf("F[%d] = %d\n", i, final[i]);
        printf("D[%d] = %d\n", i, D[i]);
    }
    return;
}

int queue[32];
int head=0,tail=0;
void bfs(graph_t *g, int v) 
{
    int i;
    init(g);
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
#if 0
    printf("\n The vertices which are reachable from %d are:\n\n", start); 
    for (int i=0;i<g->n_vert;i++)
        if(g->visited[i]) printf("%d\t",i);
    printf("\n");
    find_path(0, 3, g->parent);
#endif
}

void dfs_util(graph_t *g, int v)
{
    int i;
    g->visited[v] = 1;
    printf("dfs: %d\n", v);
    for (i = 0; i < g->n_vert; i++) {
        if (g->m[v][i] && !g->visited[i]) {
            g->parent[i] = v;
            dfs_util(g, i);
        }
    }
}

void dfs(graph_t *g, int v)
{
    init(g);
    dfs_util(g, v);
    return;
}

int stack[32];
// broken
void dfs2(graph_t *g, int start)
{
    int i, k;
    init(g); head = 0;
    stack[head++] = start;
    while (head != 0) {
        k = stack[--head];
        g->visited[k] = 1;
        printf("dfs2: %d\n", k);
        for (i = 0; i < g->n_vert; i++) {
            if (g->m[k][i] && !g->visited[i]) {
                g->visited[i] = 1;
                stack[head++] = i;
            }
        }
    }
}

void topsort(graph_t *g)
{
    int i, j, k, indeg[32], flag[32], count=0;

    for (i = 0; i < g->n_vert; i++) {
        indeg[i]=0;
        flag[i]=0;
    }

    for(i = 0; i < g->n_vert; i++)
        for(j = 0; j < g->n_vert; j++)
            indeg[i] += g->m[j][i];

    printf("\ntopsort: ");
    while (count < g->n_vert) {
        for (k = 0; k < g->n_vert; k++) {
            if ((indeg[k] == 0) && (flag[k] == 0)){
                printf("%d ", (k+1));
                flag[k] = 1;
            }
 
            for(i = 0; i < g->n_vert; i++) {
                if (g->m[i][k] == 1)
                    indeg[k]--;
            }
        }
        count++;
    }
    printf("\n\n");
}

void prim(graph_t *g)
{
    int a,b,u,v,i,j,ne=1;
    int visited[10]={0},min,minWeight=0;

    for (i = 0; i < 6; i++) {
        visited[i] = 0;
    }

    visited[0] = 1;
    ne = 1;
    while (ne < g->n_vert) {
        for(i=0,min=999; i < g->n_vert; i++) {
            min = 999;
            for(j=0;j<g->n_vert;j++) {
                if ((g->m[i][j] < min) && i!=j /*&& visited[i] != 0*/)
                {
                    min=g->m[i][j];
                    a=u=i;
                    b=v=j;
                }
            }
            //printf("min for v:%d = %d\n", i, min);
            if (visited[u]==0 || visited[v]==0) // greedy
            {
                printf("\n Edge %d:(%d %d) weight:%d",ne++,a,b,min);
                minWeight+=min;
                visited[b]=1;
                //visited[a]=1;
            }
            g->m[a][b]=g->m[b][a]=999;
            ne++;
        }
    }
    printf("\n");
    printf("\n Weight of the minimum spanning tree = %d",minWeight);
    printf("\n");
    
}

bool bellman_ford(graph_t *g, int source)
{
    //vector<double> dis_to_source(G->mat.size(), numeric_limits<double>::max());
    double dis_to_source[g->n_vert];
    int i;
    for (i = 0; i < g->n_vert; i++) {
        dis_to_source[i] = DBL_MAX;
    }
    dis_to_source[source] = 0;

    size_t times;
    int j;
    for (times = 1; times < g->n_vert; ++times) {
        bool have_update = false;
        for (i = 0; i < g->n_vert; ++i) {
            for (j = 0; j < g->n_vert; ++j) {
                if (dis_to_source[i] != DBL_MAX &&
                    dis_to_source[j] > dis_to_source[i] + g->m[i][j]) {
                    have_update = true;
                    dis_to_source[j] = dis_to_source[i] + g->m[i][j];
                }
            }
        }
        if (have_update == false) {
            return false;
        }
    }
    // detects cycle if there is any further update
    for (i = 0; i < g->n_vert; ++i) {
        for (j = 0; j < g->n_vert; ++j) {
            if (dis_to_source[i] != DBL_MAX &&
                dis_to_source[j] > dis_to_source[i] + g->m[i][j]) {
                return true;
            }
        }
    }
    return false;

}

//void floyd(int n, int g[][n])
void floyd(graph_t *g)
{
    int i, j, k;
    for (k = 0; k < g->n_vert; k++) { //k in range(0,n): # num intermediate vertices
        for (i = 0; i < g->n_vert; i++) { // in range(0,n): # source vertex (scan row)
            for (j = 0; j < g->n_vert; j++) { // in range(0,n): # dest vertex (scan col)
                g->m[i][j]=MIN(g->m[i][j],g->m[i][k] + g->m[k][j]);
            }
        }
    }
}

void warshall(graph_t *g)
{
    int i, j, k;
    for (k = 0; k < g->n_vert; k++) { //k in range(0,n): # num intermediate vertices
        for (i = 0; i < g->n_vert; i++) { // in range(0,n): # source vertex (scan row)
            for (j = 0; j < g->n_vert; j++) { // in range(0,n): # dest vertex (scan col)
                g->m[i][j]=MAX(g->m[i][j],g->m[i][k] && g->m[k][j]);
            }
        }
    }
}

int main()
{
    graph_t g = {.n_vert = 4, /* directed graph */
                  { { 0, 1, 1, 0 }, 
                    { 0, 0, 1, 0 }, 
                    { 1, 0, 0, 1 }, 
                    { 0, 0, 0, 1 } } };

    graph_t g2 = {.n_vert = 5, /* directed graph */
                  { { INF,   5,   3, INF,   2 }, 
                    { INF, INF,   2,   6, INF }, 
                    { INF,   1, INF,   2, INF }, 
                    { INF, INF, INF, INF, INF }, 
                    { INF,   6,  10,   4, INF } } };

    // dfs = {2, 0, 1, 3}
    // bfs = {2, 0, 3, 1}
    graph_t g3 = {.n_vert = 4, /* directed graph */
                  { { 0, 1, 1, 0 }, 
                    { 0, 0, 0, 1 }, 
                    { 0, 0, 0, 1 }, 
                    { 0, 0, 0, 0 } } };

    graph_t g4 = {.n_vert = 6,
                    { { 0, 0, 1, 1, 1, 0 }, 
                      { 0, 0, 0, 0, 1, 1 }, 
                      { 1, 0, 0, 1, 0, 1 }, 
                      { 1, 0, 1, 0, 0, 0 }, 
                      { 1, 1, 0, 0, 0, 1 }, 
                      { 0, 1, 1, 0, 1, 0 } } };


    int start = 2;
    printf("bfs:\n");
    bfs(&g3, start);
    printf("dfs:\n");
    dfs(&g3, 2); // should be {2,0,1,3} 
    printf("dfs2:\n");
    dfs2(&g3, 2); // should be {2,0,1,3}
    dijkstra(&g2, 0);
    topsort(&g3);
    int i;
    for (i = 0; i < 6; ++i) {
        printf("bell[%d]: %d\n", i, bellman_ford(&g4, i));
    }

    graph_t weights = {.n_vert = 6,
                       { {   0,   3, 999, 999,   6,   5}, 
                         {   3,   0,   1, 999, 999,   4}, 
                         { 999,   1,   0,   6, 999,   4}, 
                         { 999, 999,   6,   0,   8,   5}, 
                         {   6, 999, 999,   8,   0,   2}, 
                         {   5,   4,   4,   5,   2,   0} } };
    
    prim(&weights);

    graph_t f = {.n_vert = 4,
                 { {   0, 999,   3, 999 }, 
                   {   2,   0, 999, 999 }, 
                   { 999,   7,   0,   1 }, 
                   {   6, 999, 999,   0 } } };
    graph_show(&f, "floyd");
    floyd(&f);
    graph_show(&f, "floyd");

    graph_t war = {.n_vert = 4,
                 { { 0, 1, 0, 0 }, 
                   { 0, 0, 0, 1 }, 
                   { 0, 0, 0, 0 }, 
                   { 1, 0, 1, 0 } } };

    printf("\n");
    graph_show(&war,"warshall");
    warshall(&war);
    printf("\n");
    graph_show(&war, "warshall");

}

