#include "graph9.hpp"

struct comp {
    bool operator()(Vertex *l, Vertex *r) { return (l->key > r->key); }
};

void dijkstra(Graph& g, int s)
{
    set<int> V;
    vector<int> distance; distance.resize(g.adj.size());
    vector<int> previous; previous.resize(g.adj.size());
    vector<bool> visited; visited.resize(g.adj.size());
    priority_queue<Vertex*, vector<Vertex*>, comp> Q;
 
    // populate V
    for (auto v : g.adj) {
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
        for (auto e : g.adj[u->vertex]) {
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
    Graph g(8);

    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 3, 4);
    addEdge(g, 1, 4, 3);
    addEdge(g, 2, 4, 2);
    addEdge(g, 3, 4, 5);
    
    dijkstra(g, 1);
}

