#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE_RING 32
typedef int e_v;
#include "ring.inc"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void show(int n, int p[][n]) {
    int i, j;
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            printf("%d\t", p[i][j]);
        printf("\n"); 
    }
    printf("\n");
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

    
    show(n,p);
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

void warshall(int n, int g[][n])
{
    int i, j, k;
    for (k = 0; k < n; k++) { //k in range(0,n): # num intermediate vertices
        for (i = 0; i < n; i++) { // in range(0,n): # source vertex (scan row)
            for (j = 0; j < n; j++) { // in range(0,n): # dest vertex (scan col)
                g[i][j]=MAX(g[i][j],g[i][k] && g[k][j]);
            }
        }
        show(n,g);
    }
}

void test_warshall()
{
    int w[][4] = { { 0, 1, 0, 0 }, 
                   { 0, 0, 0, 1 }, 
                   { 0, 0, 0, 0 }, 
                   { 1, 0, 1, 0 } };

    show(4,w);
    warshall(4,w);
    printf("\n");
    show(4,w);
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
        show(n,g);
    }
}

void test_floyd()
{
   
    int f[][4] = { {   0, 999,   3, 999 }, 
                   {   2,   0, 999, 999 }, 
                   { 999,   7,   0,   1 }, 
                   {   6, 999, 999,   0 } };
    int n = 4;
    show(n,f);
    floyd(n,f);
    show(n,f);
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

    show(n,weight);
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

int main()
{
    //test_bfs();
    //test_dfs();
    test_warshall();
    //test_floyd();
    //test_prim();
}
