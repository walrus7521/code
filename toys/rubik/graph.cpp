#include "utils.h"

const int V = 7;
vector<int> adj[V];
bool visited[V];

vector<vii> AdjList;
vi dfs_num;
const int DFS_BLACK = 1;
const int DFS_WHITE = -1;
#define TRvii(c, it) \
    for (vii::iterator it = (c).begin(); it != (c).end(); it++)

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
    adj[u].push_back(v);
    AdjList[u].push_back(make_pair(v, wt));
}

void BFS(int s)
{
    bool visited[V] = {false};
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (q.size()) {
        int v = q.front();
        q.pop();
        printf("%d ", v);
        for (auto const& i : adj[v]) {
            if (visited[i] == false) {
                q.push(i);
                visited[i] = true;
            }
        }
    }

}

void DFS(int s)
{
    stack<int> stk;
    stk.push(s);
    while (!stk.empty()) {
        int v = stk.top();
        stk.pop();
        if (visited[v] == false) {
            printf("%d ", v);
            visited[v] = true;
        }
        //for (auto const& i : adj[v]) {
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (visited[*i] == false) {
                stk.push(*i);
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

    printf("\nBFS:\n");
    BFS(0);
    printf("\nDFS:\n");
    DFS(0);
    printf("\ndfs:\n");
    dfs(0);
    //dump();
    printf("\n");
}


