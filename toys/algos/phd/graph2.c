#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE_RING 32
typedef int e_v;
#include "ring.inc"

int max(int a,int b) {
    if(a>b) return(a); 
    else return(b); 
}

int min(int a,int b) {
    if(a<b) return(a);
    else return(b);
}

void show(int n, int p[][n]) {
    int i, j;
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            printf("%03d\t", p[i][j]);
        printf("\n"); 
    }
    printf("\n");
}

// is "v" reachable
int reach[20];
void dfs(int n, int v, int a[][n]) {
    int i;
    reach[v] = 1;
    printf("dfs: %d\n", v);
    for (i = 0; i < n; i++) {
        if (a[v][i] && !reach[i]) { 
            dfs(n, i, a);
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
    dfs(n, 0, p);

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
                g[i][j]=max(g[i][j],g[i][k] && g[k][j]);
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
                g[i][j]=min(g[i][j],g[i][k] + g[k][j]);
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

int main()
{
    //test_bfs();
    //test_dfs();
    //test_warshall();
    test_floyd();
}
