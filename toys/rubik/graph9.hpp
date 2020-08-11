#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>

using namespace std;

#define INF 9999

// https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/

struct Vertex {
    int key, vertex;
    Vertex(int vertex, int key) {
        this->vertex = vertex;
        this->key = key;
    }
};

struct Edge {
    int key;
    pair<int,int> p;
    Edge() {
        this->p.first = -1;
        this->p.second = -1;
        this->key = -1;
    }
    Edge(int u, int v, int key) {
        this->p.first = u;
        this->p.second = v;
        this->key = key;
    }
};

struct compe {
    bool operator()(Edge e1, Edge e2) const { return (e1.key > e2.key); }
};

struct Graph {
    set<Edge, compe> E;
    set<int> V;
    vector<vector<pair<int, int>>> adj;
    Graph(int max_verts) {
        this->adj.resize(max_verts);
        for (auto e : this->adj) e.resize(max_verts);
    }
};

void showGraph(Graph& g)
{
    for (int v = 0; v < g.adj.size(); v++)
        for (int e = 0; e < g.adj[v].size(); e++)
            cout << v << ", " << g.adj[v][e].first << 
                ", " << g.adj[v][e].second << endl;

    for (auto v : g.V) {
        cout << "v: " << v << endl;
    }
    for (auto e : g.E) {
        cout << "e: " << e.p.first << ", " << e.p.second << endl;
    }
}

void addEdge(Graph& g, int u, int v, int key)
{
    g.adj[u].push_back(make_pair(v, key));
    g.adj[v].push_back(make_pair(u, key));
    g.E.insert((Edge(u, v, key)));
    g.E.insert((Edge(v, u, key)));
    g.V.insert(u);
    g.V.insert(v);
}


