#include "util.h"

int dfs_num[MAX_NUM];
void dfs(int u)
{
    dfs_num[u] = DFS_BLACK;
    printf(" %d", u);
    TRvii(AdjList[u], v)
        if (dfs_num[v->first] == DFS_WHITE) // avoid cycle
            dfs(v->first);
}

// find connected components in undirected graph
void find_connected()
{
    int numComponent = 0;
    REP (i, 0, V-1)
        if (dfs_num[i] == DFS_WHITE) {
            printf("Component %d, visit:", ++numComponent);
            dfs(i);
            printf("\n");
        }
}

int main()
{
    read_graph();
    memset(dfs_num, DFS_WHITE, sizeof(dfs_num));
    find_connected();
    printf("\n");
}

