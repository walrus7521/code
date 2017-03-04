#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#if 0

int max(int a,int b) {
    if(a>b) return(a); 
    else return(b); 
}

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

void warshal(int p[10][10], int n) {
    int i,j,k;
    for (k=1;k<=n;k++)
        for (i=1;i<=n;i++) 
            for (j=1;j<=n;j++)
                p[i][j]=max(p[i][j],p[i][k]&&p[k][j]);
}

void test_warshall()
{
    int n = 4;
    int p[10][10] = { { 0, 1, 0, 0 }, 
                      { 0, 0, 0, 1 }, 
                      { 0, 0, 0, 0 }, 
                      { 1, 0, 1, 0 } };    

    warshal(p,n);
    show(p,n);
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

int main()
{
    //test_warshall();
    test_dfs();
    return 0;
}
#endif

void show(int p[10][10], int n) {
    int i, j;
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            printf("%d\t", p[i][j]);
        printf("\n"); 
    }
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
    test_bfs();
}
