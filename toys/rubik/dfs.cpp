#include "util.h"

int dfs_num[MAX_NUM];
int dfs_parent[MAX_NUM];

void graphCheck(int u)
{
    dfs_num[u] = DFS_GRAY;
    TRvii (AdjList[u], v) {
        if (dfs_num[v->first] == DFS_WHITE) { // GRAY to WHITE
            printf(" Tree Edge (%d, %d)\n", u, v->first);
            dfs_parent[v->first] = u; // parent of these children is me
            graphCheck(v->first);
        } 
        else if (dfs_num[v->first] == DFS_GRAY) { // GRAY to GRAY
            if (v->first == dfs_parent[u])
                printf(" Bidirectional (%d, %d) - (%d, %d)\n", u, v->first, v->first, u);
            else
                printf(" Back Edge (%d, %d) (Cycle)\n", u, v->first);
        }
        else if (dfs_num[v->first] == DFS_BLACK) // GRAY to BLACK
            printf(" Forward/Cross Edge (%d, %d) (Cycle)\n", u, v->first);
    }
    dfs_num[u] = DFS_BLACK;
}

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
            printf("Edge %d Component %d, visit:", i, ++numComponent);
            graphCheck(i);
            //dfs(i);
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
            printf("calling edge: %d\n", i);
            floodfill(i, ++numComponent);
        }
    REP (i, 0, V-1)
        printf("Vertex %d has color %d\n", i, dfs_num[i]);
}

int main()
{
    read_graph();
    memset(dfs_num, DFS_WHITE, sizeof(dfs_num));
    memset(dfs_parent, DFS_WHITE, sizeof(dfs_num));
    // dfs(0);
    find_connected();
    //flood_fill_util();
    printf("\n");
}

