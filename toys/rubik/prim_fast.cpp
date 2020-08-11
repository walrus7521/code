#include "graph9.hpp"

using namespace std;

void prim(Graph& g, int s)
{
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> pq;
    vector<int> key(g.adj.size(), INF);
    vector<int> parent(g.adj.size(), -1);
    vector<bool> inMST(g.adj.size(), false);

    pq.push(make_pair(s, 0));
    key[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().first; pq.pop();
        inMST[u] = true;
        for (auto e : g.adj[u]) {
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
    Graph g(8);

    addEdge(&g, 1, 2, 1);
    addEdge(&g, 1, 3, 4);
    addEdge(&g, 1, 4, 3);
    addEdge(&g, 2, 4, 2);
    addEdge(&g, 3, 4, 5);

    prim(g, 1);
}

