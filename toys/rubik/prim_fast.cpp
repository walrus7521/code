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
    bool operator()(Edge e1, Edge e2) { return (e1.key > e2.key); }
};

struct Graph {
    set<Edge, compe> E;
    set<int> V;
    vector<vector<pair<int, int>>> adj;
};

void showGraph(Graph *g)
{
    for (int v = 0; v < g->adj.size(); v++)
        for (int e = 0; e < g->adj[v].size(); e++)
            cout << v << ", " << g->adj[v][e].first << 
                ", " << g->adj[v][e].second << endl;

    for (auto v : g->V) {
        cout << "v: " << v << endl;
    }
    for (auto e : g->E) {
        cout << "e: " << e.p.first << ", " << e.p.second << endl;
    }
}

void addEdge(Graph *g, int u, int v, int key)
{
    g->adj[u].push_back(make_pair(v, key));
    g->adj[v].push_back(make_pair(u, key));
    g->E.insert((Edge(u, v, key)));
    g->E.insert((Edge(v, u, key)));
    g->V.insert(u);
    g->V.insert(v);
}

struct compp {
    bool operator()(Vertex *l, Vertex *r) { return (l->key > r->key); }
};

void prim(Graph *g, int s)
{
    set<int> X = { s };
    set<pair<int, int>> T;
    priority_queue<Vertex*, vector<Vertex*>, compp> H;
    vector<int> key;
    vector<Edge> winner;
    key.resize(MAX_VERTS);
    winner.resize(MAX_VERTS);
 
    for (auto v : g->V) {
        if (v != s) {
            cout << "find: (" << s << "," << v << endl;
            int min = INF;
            int w;
            bool found = false;
            for (auto e : g->adj[v]) {
                if (X.find(e.first) == X.end()) {
                    if (e.second < min) {
                        min = e.second;
                        w = e.first;
                        found = true;
                    }
                }
            }
            if (found) {
                key[w] = min;
                winner[w] = Edge(s,w,min);
            } else {
                key[w] = INF;
                winner[w] = Edge(-1,-1,-1);
            }
            H.push(new Vertex(w, min));
        }
    }
    while (!H.empty()) {
        Vertex *w_star = H.top(); H.pop();
        X.insert(w_star->vertex);
        Edge e = winner[w_star->vertex];
        T.insert(make_pair(e.p.first, e.p.second));
        for (auto e : g->adj[w_star->vertex]) {
            if (X.find(e.first) != X.end()) continue;
            int y = e.first;
            int cost_wy = e.second;
            if (cost_wy < key[y]) {
                auto it = H.find(Edge(w_star->vertex, y, cost_wy));
                if (it != H.end()) {
                    H.erase(it);
                }
                key[y] = cost_wy;
                winner[y] = Edge(w_star->vertex, y, cost_wy);
                H.push(new Vertex(y, cost_wy));
            }
                    
        }
#if 0
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
#endif
    }
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
    
    showGraph(&g);

    prim(&g, 1);
}

