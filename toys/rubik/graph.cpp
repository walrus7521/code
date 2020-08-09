#include "utils.h"

const int V = 7;
bool visited[V];
vector<vii> AdjList;
vi dfs_num;
const int DFS_BLACK = 1;
const int DFS_WHITE = -1;

void init()
{
    AdjList.resize(V);
    dfs_num.resize(V);
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        dfs_num[i] = DFS_WHITE;
    }
}

void addEdge(int u, int v, int wt)
{
    AdjList[u].push_back(make_pair(v, wt));
}

#if 0
void showGraph(Graph *g)
{
    for (int v = 0; v < g->adj.size(); v++)
        for (int e = 0; e < g->adj[v].size(); e++)
            cout << v << ", " << g->adj[v][e].first << 
                ", " << g->adj[v][e].second << endl;
}
#endif

void bfs(int s)
{
    queue<int> q;
    q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        visited[u] = true;
        printf(" %d", u);
        for (int i = 0; i < (int) AdjList[u].size(); i++) {
            ii v = AdjList[u][i];
            if (!visited[v.first]) {
                q.push(v.first);
            }
        }
    }
}

void dfs(int u)
{
    printf(" %d", u);
    dfs_num[u] = DFS_BLACK;
    for (int i = 0; i < (int) AdjList[u].size(); i++) {
        ii v = AdjList[u][i];
        if (dfs_num[v.first] == DFS_WHITE)
            dfs(v.first);
    }

}

void dump()
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < (int) AdjList[i].size(); j++) {
            ii v = AdjList[i][j];
            printf("[%d] %d %d\n", i, v.first, dfs_num[v.first]);
        }
    }

}


int main()
{
    init();
#if 0
    addEdge(0, 1, 0);
    addEdge(0, 2, 0);
    addEdge(1, 2, 0);
    addEdge(2, 0, 0);
    addEdge(2, 3, 0);
    addEdge(3, 3, 0);
#endif
    addEdge(1, 0, 0);
    addEdge(0, 2, 0);
    addEdge(2, 1, 0);
    addEdge(0, 3, 0);
    addEdge(1, 4, 0);

    //printf("\ndfs:\n");
    //dfs(0);
    printf("\nbfs:\n");
    bfs(0);
    printf("\n");
    //dump();
    //printf("\n");
}


