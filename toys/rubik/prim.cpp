#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

#define MAX 8

struct Graph {
    vector<vector<pair<int, int>>> adj;
};

void addEdge(Graph *g, int u, int v, int wt)
{
    g->adj[u].push_back(make_pair(v, wt));
    g->adj[v].push_back(make_pair(u, wt));
}

void showGraph(Graph *g)
{
    for (int v = 0; v < g->adj.size(); v++)
        for (int e = 0; e < g->adj[v].size(); e++)
            cout << v << ", " << g->adj[v][e].first << 
                ", " << g->adj[v][e].second << endl;
}

int main()
{
    Graph g;
    g.adj.resize(MAX);
    for (auto e : g.adj) e.resize(MAX);

    addEdge(&g, 1, 2, 1);
    addEdge(&g, 1, 3, 4);
    addEdge(&g, 1, 4, 3);
    addEdge(&g, 2, 4, 2);
    addEdge(&g, 3, 4, 5);
    
    set<int> U = { 1 };
    set<int> V = { 1, 2, 3, 4 };
    set<pair<int, int>> T;

    auto viter = V.begin();

    while (U != V) {
        int v = (int)(*viter++);
        int w;
        int wt;
        bool v_not_in_U = (U.find(v) == U.end());
        if (v_not_in_U) { // cross the frontier
            bool found = false;
            int min_wt = 9999;
            int min_w;
            for (auto e : g.adj[v]) {
                w = e.first;
                wt = e.second;
                if (wt < min_wt) {
                    min_wt = wt;
                    min_w = w;
                }
            }
            T.insert(make_pair(v, min_w));
        }
        U.insert(v); // add to U
    }

    for (auto e : T) cout << e.first << "," << e.second << endl;
 
    return 0;
}

