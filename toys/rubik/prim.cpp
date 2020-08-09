#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

#define MAX_VERTS 8
#define INF 9999

struct Graph {
    vector<vector<pair<int, int>>> adj;
};

void addEdge(Graph *g, int u, int v, int wt)
{
    g->adj[u].push_back(make_pair(v, wt));
    g->adj[v].push_back(make_pair(u, wt));
}

void Prim(Graph *g, int s)
{
    set<int> X = { s };
    set<int> V;
    set<pair<int, int>> T;

    // populate V
    for (auto v : g->adj) {
        for (auto e : v)
            V.insert(e.first);
    }
    auto viter = V.begin();

    while (X != V) {
        int v = (int)(*viter++);
        int w;
        int wt;
        bool v_not_in_X = (X.find(v) == X.end());
        if (v_not_in_X) { // cross the frontier
            bool found = false;
            int min_wt = INF;
            int min_w;
            for (auto e : g->adj[v]) {
                w = e.first;
                wt = e.second;
                if (wt < min_wt) {
                    min_wt = wt;
                    min_w = w;
                }
            }
            T.insert(make_pair(v, min_w));
        }
        X.insert(v); // add to X
    }
    for (auto e : T) cout << e.first << "," << e.second << endl;
}

int main()
{
    Graph g;
    g.adj.resize(MAX_VERTS);
    for (auto e : g.adj) e.resize(MAX_VERTS);

    addEdge(&g, 1, 2, 1);
    addEdge(&g, 1, 3, 4);
    addEdge(&g, 1, 4, 3);
    addEdge(&g, 2, 4, 2);
    addEdge(&g, 3, 4, 5);
    
    Prim(&g, 1);

    return 0;
}

