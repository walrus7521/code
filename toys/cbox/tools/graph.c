#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "graph.h"

#define SIZE_RING 32
typedef int e_v;
#include "ring.inc"

void graph_show(int n, int p[][n], char *name) {
    int i, j;
    printf("graph: %s\n", name);
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            printf("%d\t", p[i][j]);
        printf("\n"); 
    }
    printf("\n");
}

void array_show(int n, int a[], char *name)
{
    int i;
    printf("array: %s\n", name);
    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
    printf("\n");
}

void topsort(int n, int a[][n])
{
    int indegree[32]; // 32 is max vertices
    int sorted[32];
    int x, y; // current and next vertex
    int i, j; // counters
    int v; // vertex

    // compute indegrees of graph vertices
    for (i = 0; i < n; i++) {
        sorted[i] = 0;
        indegree[i] = 0;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (a[i][j] == 1) {
                indegree[i]++;
                indegree[j]++;
            }
        }
    }

    init_ring();
    for (i = 0; i < n; i++) {
        if (indegree[i] == 1) rngput(indegree[i]);
    }

    j = 0;
    while (!rngempty()) {
        v = rngget();
        sorted[j++] = v;
        for (i = 0; i < n; i++) {
        }
    }
    for (i = 0; i < n; i++) printf("%d\n", sorted[i]);

}

void test_topsort()
{
    int w[][4] = { { 0, 1, 0, 0 }, 
                   { 0, 0, 0, 1 }, 
                   { 0, 0, 0, 0 }, 
                   { 1, 0, 1, 0 } };

    graph_show(4,w,"topsort");
    topsort(4,w);
    printf("\n");
    graph_show(4,w,"topsort");
}

// is "v" reachable
int reach[20];
void dfs_r(int n, int v, int a[][n]) {
    int i;
    reach[v] = 1;
    printf("dfs: %d\n", v);
    for (i = 0; i < n; i++) {
        if (a[v][i] && !reach[i]) { 
            dfs_r(n, i, a);
        }
    }
}

int q[20],visited[20],parent[20]={-1},f=0,r=-1;
void bfs_r(int v, int n, int g[][n]) {
    int i;
    for (i = 0; i < n; i++) 
        if (g[v][i] && !visited[i]) {
            parent[i] = v;
            q[++r]=i; // append to queue
        }
    if(f < r) {
        visited[q[f]]=1;
        bfs_r(q[f++], n, g); 
    }
}

void bfs2(int start, int n, int g[][n]) {
    int v;
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = -1;
        visited[i] = 0;
    }
    visited[start] = 1;
    init_ring();
    rngput(start);
    while (!rngempty()) {
        v = rngget();
        printf("v: %d\n", v);
        for (i = 0; i < n; i++) {
            if (g[v][i] == 1 && !visited[i]) {
                rngput(i);
                visited[i] = 1;
                parent[i] = v;
            }
        }
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

void test_bfs()
{
/*                      0 1 2 3 4 5
 *                      ===========
 *  0: 1,2,3        0:  1 1 1 1 0 0
 *  1:              1:  0 1 0 0 0 0
 *  2: 4,5          2:  0 0 1 0 1 1
 *  3:              3:  0 0 0 1 0 0
 *  4:              4:  0 0 0 0 1 0
 *  5:              5:  0 0 0 0 0 1
 */
   
    int c[][6] = { { 1, 1, 1, 1, 0, 0 }, 
                   { 0, 1, 0, 0, 0, 0 }, 
                   { 0, 0, 1, 0, 1, 1 }, 
                   { 0, 0, 0, 1, 0, 0 }, 
                   { 0, 0, 0, 0, 1, 0 }, 
                   { 0, 0, 0, 0, 0, 1 } };
    int n = 6;
    int v = 0;
    int i;
    for (i = 0; i < 10; i++) {
        parent[i] = -1;
    }
    bfs2(v, n, c);
    printf("\n The vertices which are reachable from %d are:\n\n", v); 
    for (i=0;i<n;i++)
        if(visited[i]) 
            printf("%d\t",i);
    printf("\n");
    find_path(0, 4, parent);
    
}

void test_dfs()
{
    int n = 6;
    int p[][10] = { { 0, 0, 1, 1, 1, 0 }, 
                    { 0, 0, 0, 0, 1, 1 }, 
                    { 1, 0, 0, 1, 0, 1 }, 
                    { 1, 0, 1, 0, 0, 0 }, 
                    { 1, 1, 0, 0, 0, 1 }, 
                    { 0, 1, 1, 0, 1, 0 } };

    
    graph_show(n,p,"dfs");
    dfs_r(n, 0, p);

    int i, count;
    for (i = 0; i < n; i++) { 
        if(reach[i]) count++; 
    }
    printf("count: %d, n: %d\n", count, n);
    printf("\n"); 
    if(count == n)
        printf("\n Graph is connected"); 
    else
        printf("\n Graph is not connected");
    printf("\n");
    
}

int find_lowest_cost_node(int costs[], int visited[], int n)
{
    int min = 999;
    int low_node = INV;
    int node;
    for (node = 0; node < n; node++) {
        int v = visited[node];
        if ((costs[node] < min) && (0 == v)) {
            min = costs[node];
            low_node = node;
            //printf("update min: %d, node: %d\n", min, low_node);
        }
    }
    //printf("find lowest node: %d\n", low_node);
    return low_node;
}

void test_dijkstra()
{
    int i, cost, n, new_cost, node;
    int N = 4;
    
    //int graph[][4] = { {0, 6, 2, 0},
    //                   {0, 0, 0, 1},
    //                   {0, 3, 0, 5},
    //                   {0, 0, 0, 0} };

    int graph[][4] = { {INV,   6,   2, INV},
                       {INV, INV, INV,   1},
                       {INV,   3, INV,   5},
                       {INV, INV, INV, INV} };

    
    int costs[] = { 0,
                    6,
                    3, // modified from 2
                    999 };

    int parents[] = { 0,
                      0,
                      0,
                      999};
    int visited[] = {0,0,0,0};

    array_show(N,costs,"costs");
    array_show(N,parents,"parents");
    graph_show(N,graph,"dijkstra");
    array_show(N,visited,"visited");

//    # grab node closes to start
//    node = find_lowest_cost_node(costs, visited)
//    print "cost: ", costs[node]
//    while node != "":
//        cost = costs[node]
//        neighbors = graph[node]
//        for n in neighbors.keys():
//            new_cost = cost + neighbors[n]
//            if costs[n] > new_cost:
//                costs[n] = new_cost
//                parents[n] = node
//        visited.append(node) # mark node as visited
//        node = find_lowest_cost_node(costs, visited)
//    print "parents: ", parents

    node = find_lowest_cost_node(costs, visited, N);
    while (node != INV) {
        cost = costs[node];
        printf("cost[%d]: %d\n", node, cost);
        for (i = 0; i < N; i++) {
            n = graph[node][i];
            if (n == INV) continue;
            new_cost = cost + n;
            printf("n: %d, new_cost: %d\n", n, new_cost);
            if (costs[i] > new_cost) {
                costs[i] = new_cost;
                parents[i] = node;
            }
        }
        visited[node] = 1;
        array_show(N,visited,"visited");
        node = find_lowest_cost_node(costs, visited, N);
    }
    array_show(N,costs,"costs");
    array_show(N,parents,"parents");

}

void test_kruskal() 
{
    int min, minCost = 0;
    int i,j,k,a,b,u,v,n,ne=1;
    int par[20] = {-1};

    n = 6;
    int cost[][7] = { {0,    0,   0,   0,   0,   0,   0 }, 
                      {0,    0,   3, 999, 999,   6,   5 }, 
                      {0,    3,   0,   1, 999, 999,   4 }, 
                      {0,  999,   1,   0,   6, 999,   4 }, 
                      {0,  999, 999,   6,   0,   8,   5 }, 
                      {0,    6, 999, 999,   0,   0,   2 }, 
                      {0,    5,   4,   4,   5,   2,   0 } };
    
 
    printf("\nThe edges of Minimum Spanning Tree are\n\n");
    while(ne<n) {
        for(i=1,min=999;i<=n;i++) {
            for(j=1;j<=n;j++) {
                if(cost[i][j]<min) {
                    min=cost[i][j]; a=u=i;
                    b=v=j;
                } 
            }
        } 
        u=gfind(u,par); 
        v=gfind(v,par);
        if(uni(u,v,par)) {
            printf("%d edge (%d,%d) =%d\n",ne++,a,b,min);
            minCost +=min; 
        }
        cost[a][b]=cost[b][a]=999; 
    }
    printf("\nWeight of the minimum spanning tree = %d\n",minCost); 
}
    

int gfind(int i, int par[]) 
{
    while(par[i]) 
        i=par[i];
    return i; 
}

int uni(int i,int j, int par[]) 
{
    if(i!=j) {
        par[j]=i;
        return 1; 
    }
    return 0; 
}


void warshall(int n, int g[][n])
{
    int i, j, k;
    for (k = 0; k < n; k++) { //k in range(0,n): # num intermediate vertices
        for (i = 0; i < n; i++) { // in range(0,n): # source vertex (scan row)
            for (j = 0; j < n; j++) { // in range(0,n): # dest vertex (scan col)
                g[i][j]=MAX(g[i][j],g[i][k] && g[k][j]);
            }
        }
        graph_show(n,g,"warshall");
    }
}

void test_warshall()
{
    int w[][4] = { { 0, 1, 0, 0 }, 
                   { 0, 0, 0, 1 }, 
                   { 0, 0, 0, 0 }, 
                   { 1, 0, 1, 0 } };

    graph_show(4,w,"warshall");
    warshall(4,w);
    printf("\n");
    graph_show(4,w,"warshall");
}

void floyd(int n, int g[][n])
{
    int i, j, k;
    for (k = 0; k < n; k++) { //k in range(0,n): # num intermediate vertices
        for (i = 0; i < n; i++) { // in range(0,n): # source vertex (scan row)
            for (j = 0; j < n; j++) { // in range(0,n): # dest vertex (scan col)
                g[i][j]=MIN(g[i][j],g[i][k] + g[k][j]);
            }
        }
        graph_show(n,g,"floyd");
    }
}

void test_floyd()
{
   
    int f[][4] = { {   0, 999,   3, 999 }, 
                   {   2,   0, 999, 999 }, 
                   { 999,   7,   0,   1 }, 
                   {   6, 999, 999,   0 } };
    int n = 4;
    graph_show(n,f,"floyd");
    floyd(n,f);
    graph_show(n,f,"floyd");
}

void prim(int n, int g[][n])
{
    int a,b,u,v,i,j,ne=1;
    int visited[10]={0},min,minWeight=0;

    for (i = 0; i < 6; i++) {
        visited[i] = 0;
    }

    visited[0] = 1;
    ne = 1;
    while (ne < n) {
        for(i=0,min=999;i<n;i++) {
            min = 999;
            for(j=0;j<n;j++) {
                if ((g[i][j] < min) && i!=j /*&& visited[i] != 0*/)
                {
                    min=g[i][j];
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
            g[a][b]=g[b][a]=999;
            ne++;
        }
    }
    printf("\n");
    printf("\n Weight of the minimum spanning tree = %d",minWeight);
    printf("\n");
    
}

void test_prim()
{
    int n = 6;
    int weight[][6] = { {   0,   3, 999, 999,   6,   5}, 
                        {   3,   0,   1, 999, 999,   4}, 
                        { 999,   1,   0,   6, 999,   4}, 
                        { 999, 999,   6,   0,   8,   5}, 
                        {   6, 999, 999,   8,   0,   2}, 
                        {   5,   4,   4,   5,   2,   0} };

    graph_show(n,weight,"prim");
    prim(n, weight);

    /*
     * Edge 1:(1 2) weight:3 => Edge(A,B) = 3 => Edge(0,1)
     * Edge 2:(2 3) weight:1 => Edge(B,C) = 1 => Edge(1,2) 
     * Edge 3:(2 6) weight:4 => Edge(B,F) = 4 => Edge(1,5) 
     * Edge 4:(6 5) weight:2 => Edge(F,E) = 2 => Edge(5,4) 
     * Edge 5:(6 4) weight:5 => Edge(F,D) = 5 => Edge(5,3) 
     *
     * Weight of minimum spanning tree = 15
     *
     * my output:
     *
     *  0       3       999     999     6       5
     *  3       0       1       999     999     4
     *  999     1       0       6       999     4
     *  999     999     6       0       8       5
     *  6       999     999     8       0       2
     *  5       4       4       5       2       0
     *
     *   Edge 1:(0 1) weight:3 AB
     *   Edge 3:(1 2) weight:1 BC
     *   Edge 5:(2 5) weight:4 CF
     *   Edge 7:(3 5) weight:5 DF
     *   Edge 9:(4 5) weight:2 EF
     *
     *   Weight of the minimum spanning tree = 15
     * 
     */
}


int graph_test()
{
    test_bfs();
    //test_dfs();
    //test_warshall();
    //test_floyd();
    //test_prim();
    //test_kruskal();
    //test_dijkstra();
    //test_topsort();
    return 0;
}


