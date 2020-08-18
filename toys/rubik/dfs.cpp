#include "util.h"

int dfs_num[MAX_NUM];
void dfs(int u)
{
    dfs_num[u] = DFS_BLACK;
    printf(" %d", u);
    TRvii(AdjList[u], v) // traversing vector of ii
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

void floodfill(int u, int color)
{
    dfs_num[u] = color;
    TRvii(AdjList[u], v) // traversing vector of ii
        if (dfs_num[v->first] == DFS_WHITE) // avoid cycle
            floodfill(v->first, color);
}

void flood_fill_util()
{
    int numComponent = 0;
    REP (i, 0, V-1)
        if (dfs_num[i] == DFS_WHITE) {
            floodfill(i, ++numComponent);
        }
    REP (i, 0, V-1)
        printf("Vertex %d has color %d\n", i, dfs_num[i]);
}

int main()
{
    read_graph();
    memset(dfs_num, DFS_WHITE, sizeof(dfs_num));
    // dfs(0);
    //find_connected();
    flood_fill_util();
    printf("\n");
}

