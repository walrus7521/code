#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int max(int a,int b) {
    if(a>b) return(a); 
    else return(b); 
}
#if 0

////

// is "v" reachable
void dfs(int a[10][10], int n, int reach[10], int v) {
    int i;
    reach[v] = 1;
    for (i = 0; i < n; i++) {
        printf("a[%d][%d]: %d\n", v, i, a[v][i]);
        if (a[v][i] && !reach[i]) { 
            printf("\n %d->%d",v,i); 
            dfs(a, n, reach, i);
        }
    }
}

void test_dfs()
{
    int n = 6;
    int reach[10];
    int p[10][10] = { { 0, 0, 1, 1, 1, 0 }, 
                      { 0, 0, 0, 0, 1, 1 }, 
                      { 1, 0, 0, 1, 0, 1 }, 
                      { 1, 0, 1, 0, 0, 0 }, 
                      { 1, 1, 0, 0, 0, 1 }, 
                      { 0, 1, 1, 0, 1, 0 } };

    show(p,n);
    dfs(p, n, reach, 1);

    int i, count;
    for (i=1;i<=n;i++) { 
        if(reach[i])
        count++; 
    }
    printf("\n"); 
    if(count==n)
        printf("\n Graph is connected"); 
    else
        printf("\n Graph is not connected");
    printf("\n");
    
}
#endif

void show(int p[10][10], int n) {
    int i, j;
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            printf("%d\t", p[i][j]);
        printf("\n"); 
    }
    printf("\n");
}

// note: index starts at 1 (not zero)
int b[20][20] = { { 0, 0, 0, 0, 0, 0, 0 }, 
                  { 0, 1, 1, 1, 1, 0, 0 }, 
                  { 0, 0, 1, 0, 0, 0, 0 }, 
                  { 0, 0, 0, 1, 0, 1, 1 }, 
                  { 0, 0, 0, 0, 1, 0, 0 }, 
                  { 0, 0, 0, 0, 0, 1, 0 }, 
                  { 0, 0, 0, 0, 0, 0, 1 } };

int q[20],visited[20],n,i,j,f=0,r=-1,v; 
void bfs(int v) {
    for (i=1;i<=n;i++) 
        if(b[v][i] && !visited[i])
            q[++r]=i; 
    if(f<=r) {
        visited[q[f]]=1;
        bfs(q[f++]); 
    }
}

void warshall(int g[10][10], int n)
{
    int i, j, k;
    for (k = 0; k < n; k++) { //k in range(0,n): # num intermediate vertices
        for (i = 0; i < n; i++) { // in range(0,n): # source vertex (scan row)
            for (j = 0; j < n; j++) { // in range(0,n): # dest vertex (scan col)
                g[i][j]=max(g[i][j],g[i][k] && g[k][j]);
            }
        }
        show(g, n);
    }
}

void test_warshall()
{
    int w[10][10] = { { 0, 1, 0, 0 }, 
                      { 0, 0, 0, 1 }, 
                      { 0, 0, 0, 0 }, 
                      { 1, 0, 1, 0 } };

    show(w, 4);
    warshall(w, 4);
    printf("\n");
    show(w, 4);
}

void test_bfs()
{
    n = 6;
    v = 3;
    bfs(v);
    printf("\n The vertices which are reachable from %d are:\n\n", v); 
    for (i=1;i<=n;i++)
        if(visited[i]) 
            printf("%d\t",i);
    printf("\n");
    
}

int main()
{
    //test_bfs();
    test_warshall();
}
