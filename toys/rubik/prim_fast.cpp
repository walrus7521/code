#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>

using namespace std;

#define MAX_VERTS 8
#define INF 9999

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
    Edge(int u, int v, int key) {
        this->p.first = u;
        this->p.second = v;
        this->key = key;
    }
};

struct compe {
    bool operator()(Edge e1, Edge e2) const { return true; /*e1.key > e2.key*/ }
};

struct Graph {
    set<Edge, compe> edges;
    vector<vector<pair<int, int>>> adj;
};

void addEdge(Graph *g, int u, int v, int key)
{
    g->adj[u].push_back(make_pair(v, key));
    g->adj[v].push_back(make_pair(u, key));
    g->edges.insert((Edge(u, v, key)));
    g->edges.insert((Edge(v, u, key)));
}

struct compp {
    bool operator()(Vertex *l, Vertex *r) { return (l->key > r->key); }
};

void prim(Graph *g, int s)
{
    set<int> X = { s };
    set<pair<int, int>> T;
    set<int> V;
    priority_queue<Vertex*, vector<Vertex*>, compp> H;
 
    // populate V
    for (auto v : g->adj) {
        for (auto e : v)
            V.insert(e.first);
    }

    for (auto v : V) {
        if (v != s) {
            bool is_in = (g->edges.find(Edge(s, v, 0)) != g->edges.end());
            cout << "is in: " << is_in << endl;
            H.push(new Vertex(v, 0));
        }
    }
#if 0
    while (!Q.empty()) {
        Vertex *u = Q.top(); Q.pop(); //<- Extract MIN from Q
        visited[u->vertex] = true;
        for (auto e : g->adj[u->vertex]) {
            int v = e.first;
            if (visited[v]) continue;
            int dx = distance[u->vertex] + e.second;
            if (dx < distance[v]) { // Relax
                distance[v] = dx;
                previous[v] = u->vertex;
            }
        }
    }
    cout << "source: " << s << endl;
    for (auto v : V) {
        if (v == s) continue;
        cout << "v: " << v << "-> " << previous[v] << " = " << distance[v] << endl;
    }
#endif
}

int main()
{
    Graph g;
    set<Edge*> edge;
    g.adj.resize(MAX_VERTS);
    for (auto e : g.adj) e.resize(MAX_VERTS);

    addEdge(&g, 1, 2, 1);
    addEdge(&g, 1, 3, 4);
    addEdge(&g, 1, 4, 3);
    addEdge(&g, 2, 4, 2);
    addEdge(&g, 3, 4, 5);
    
    prim(&g, 1);
}

