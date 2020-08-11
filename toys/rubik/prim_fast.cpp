#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

#define MAX_VERTS 8
#define INF 9999

// https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
typedef vector<vector<pair<int, int>>> graph;

void showGraph(graph& g)
{
    for (int v = 0; v < g.size(); v++)
        for (int e = 0; e < g[v].size(); e++)
            cout << v << ", " << g[v][e].first << 
                ", " << g[v][e].second << endl;
}

void addEdge(graph& g, int u, int v, int key)
{
    g[u].push_back(make_pair(v, key));
    g[v].push_back(make_pair(u, key));
}

void prim(graph& g, int s)
{
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> pq;
    vector<int> key(MAX_VERTS, INF);
    vector<int> parent(MAX_VERTS, -1);
    vector<bool> inMST(MAX_VERTS, false);

    pq.push(make_pair(s, 0));
    key[s] = 0;
    while (!pq.empty()) {
        int u = pq.top().first; pq.pop();
        inMST[u] = true;
        for (auto e : g[u]) {
            int v = e.first;
            int wt = e.second;
            if (wt < key[v] && !inMST[v]) {
                key[v] = wt;
                pq.push(make_pair(v, key[v]));
                parent[v] = u;
            }
        }
    }
    for (int i = 0; i < 8; i++)
        if (parent[i] > -1) cout << parent[i] << " - " << i << endl;
}

int main()
{
    graph gg;
    gg.resize(MAX_VERTS);
    for (auto e : gg) e.resize(MAX_VERTS);

    addEdge(gg, 1, 2, 1);
    addEdge(gg, 1, 3, 4);
    addEdge(gg, 1, 4, 3);
    addEdge(gg, 2, 4, 2);
    addEdge(gg, 3, 4, 5);

    //showGraph(gg);

    prim(gg, 1);
}

