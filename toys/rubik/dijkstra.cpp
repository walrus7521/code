#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>

using namespace std;

#define MAX_VERTS 8
#define INF 9999

struct Vertex {
    int dx, vertex;
    Vertex(int vertex, int dx) {
        this->vertex = vertex;
        this->dx = dx;
    }
};

struct Graph {
    vector<vector<pair<int, int>>> adj;
};

void addEdge(Graph *g, int u, int v, int wt)
{
    g->adj[u].push_back(make_pair(v, wt));
    g->adj[v].push_back(make_pair(u, wt));
}

struct comp {
    bool operator()(Vertex *l, Vertex *r) { return (l->dx > r->dx); }
};

void dijkstra(Graph *g, int s)
{
    set<int> V;
    vector<int> distance; distance.resize(MAX_VERTS);
    vector<int> previous; previous.resize(MAX_VERTS);
    vector<bool> visited; visited.resize(MAX_VERTS);
    priority_queue<Vertex*, vector<Vertex*>, comp> Q;
 
    // populate V
    for (auto v : g->adj) {
        for (auto e : v)
            V.insert(e.first);
    }
     
    distance[s] = 0; // Initialize single source
    for (auto v : V) {
        if (v != s) {
            distance[v] = INF;
            previous[v] = 0;
            visited[v] = false;
        }
        Q.push(new Vertex(v, distance[v]));
    }
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
    
    dijkstra(&g, 1);
}

