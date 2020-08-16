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
    int idx_E;
    Edge *arr_E;
    set<int> V;
    vector<vector<pair<int, int>>> adj;
    int v, e; // number of vertices and edges
    Graph(int n_verts, int n_edges) {
        this->idx_E = 0;
        this->v = n_verts;
        this->e = n_edges;
        this->adj.resize(n_verts);
        for (auto e : this->adj) e.resize(n_verts);
        this->arr_E = new Edge[n_edges];
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
    g.arr_E[g.idx_E].p = make_pair(u, v);
    g.arr_E[g.idx_E].key = key;
    g.idx_E++;
}


