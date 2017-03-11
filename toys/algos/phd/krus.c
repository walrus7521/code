#include <stdio.h>

int i,j,k,a,b,u,v,n,ne=1;
int min,minCost=0,parent[9]; int find(int);
int uni(int,int);

int main() {
#if 0
#endif
    printf("\n"); printf("Output:\n");


    n = 6;
    int cost[][7] = { {0,    0,   0,   0,   0,   0,   0 }, 
                      {0,    0,   3, 999, 999,   6,   5 }, 
                      {0,    3,   0,   1, 999, 999,   4 }, 
                      {0,  999,   1,   0,   6, 999,   4 }, 
                      {0,  999, 999,   6,   0,   8,   5 }, 
                      {0,    6, 999, 999,   0,   0,   2 }, 
                      {0,    5,   4,   4,   5,   2,   0 } };
    
 
    printf("\n");
    printf("\n The edges of Minimum Spanning Tree are\n\n");
    while(ne<n) {
        for(i=1,min=999;i<=n;i++) {
            for(j=1;j<=n;j++) {
                if(cost[i][j]<min) {
                    min=cost[i][j]; a=u=i;
                    b=v=j;
                } 
            }
        } 
        u=find(u); 
        v=find(v);
        if(uni(u,v)) {
            printf("\n%d edge (%d,%d) =%d\n",ne++,a,b,min);
            minCost +=min; 
        }
        cost[a][b]=cost[b][a]=999; 
    }
    printf("\n\tWeight of the minimum spanning tree = %d\n",minCost); 
}
    
int find(int i) 
{
    while(parent[i]) 
        i=parent[i];
    return i; 
}

int uni(int i,int j) 
{
    if(i!=j) {
        parent[j]=i;
        return 1; 
    }
    return 0; 
}
 
