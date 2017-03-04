#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int max(int a,int b) {
    if(a>b) return(a); 
    else return(b); 
}


void show(int p[10][10], int n) {
    int i, j;
    printf("\n Transitive closure: \n"); 
    for (i=1;i<=n;i++) {
        for (j=1;j<=n;j++) printf("%d\t",p[i][j]);
        printf("\n"); 
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
    int n = 4, i, j;
    int p[10][10] = { { 0, 1, 0, 0 }, 
                      { 0, 0, 0, 1 }, 
                      { 0, 0, 0, 0 }, 
                      { 1, 0, 1, 0 } };    

    warshal(p,n);
    show(p,n);
}

int main()
{
    test_warshall();
    return 0;
}

