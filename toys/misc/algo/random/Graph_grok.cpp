#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <memory>
#include <limits>

using namespace std;

template <typename T>
struct Graph {
    int dim;
    vector<vector<T>> mat;
    vector<int> reachable;
    vector<int> visited;
    vector<int> parent;
};

template <typename T>
using GraphPtr = shared_ptr<Graph<T>>;

template <typename T>
GraphPtr<T> create(int dim)
{
    GraphPtr<T> g(new Graph<T>);

    g->mat.resize(dim);
    g->dim = dim;
    g->reachable.resize(dim*dim);
    g->visited.resize(dim*dim);
    g->parent.resize(dim*dim);
    return g;
}

template <typename T>
void graph_show(GraphPtr<T> g, string name) {
    int i, j,n = g->mat.size();
    cout << "graph: " << name << endl;
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            cout << g->mat[i][j] << '\t';
        cout << endl;
    }
    cout << endl;
}

template <typename T>
void bfs(GraphPtr<T> g, int start) {
    int v;
    int i;
    for (i = 0; i < g->dim; i++) {
        g->parent[i] = -1;
        g->visited[i] = 0;
    }
    g->visited[start] = 1;
    //init_ring();
    //rngput(start);
#if 0
    while (!rngempty()) {
        v = rngget();
        printf("v: %d\n", v);
        for (i = 0; i < n; i++) {
            if (g[v][i] == 1 && !visited[i]) {
                rngput(i);
                visited[i] = 1;
                parent[i] = v;
            }
        }
    }
#endif
}



template <typename T>
void dfs_r(int v, GraphPtr<T> g) {
    int i, n = g->mat.size();
    g->reachable[v] = 1;
    cout << "dfs: " << v << endl;
    for (i = 0; i < n; i++) {
        if (g->mat[v][i] && !g->reachable[i]) { 
            dfs_r(i, g);
        }
    }
}

void test_dfs()
{
    int n = 6;

    GraphPtr<int> g = create<int>(6);
    g->mat = { { 0, 0, 1, 1, 1, 0 }, 
               { 0, 0, 0, 0, 1, 1 }, 
               { 1, 0, 0, 1, 0, 1 }, 
               { 1, 0, 1, 0, 0, 0 }, 
               { 1, 1, 0, 0, 0, 1 }, 
               { 0, 1, 1, 0, 1, 0 } };

    graph_show(g,"dfs");
    dfs_r(0, g);
    int i, count=0;
    for (i = 0; i < n; i++) { 
        if(g->reachable[i]) count++; 
    }
    cout << "count: " << count << ", n: " << n << endl;
    if(count == n)
        cout << "Graph is connected" << endl; 
    else
        cout << "Graph is not connected" << endl;
}

template <typename T>
bool bellman_ford(GraphPtr<T> G, int source)
{
    vector<double> dis_to_source(G->mat.size(), numeric_limits<double>::max());
    dis_to_source[source] = 0;

    for (size_t times = 1; times < G->mat.size(); ++times) {
        bool have_update = false;
        for (size_t i = 0; i < G->mat.size(); ++i) {
            for (size_t j = 0; j < G->mat[i].size(); ++j) {
                if (dis_to_source[i] != numeric_limits<double>::max() &&
                    dis_to_source[j] > dis_to_source[i] + G->mat[i][j]) {
                    have_update = true;
                    dis_to_source[j] = dis_to_source[i] + G->mat[i][j];
                }
            }
        }
        if (have_update == false) {
            return false;
        }
    }
    // detects cycle if there is any further update
    for (size_t i = 0; i < G->mat.size(); ++i) {
        for (size_t j = 0; j < G->mat[i].size(); ++j) {
            if (dis_to_source[i] != numeric_limits<double>::max() &&
                dis_to_source[j] > dis_to_source[i] + G->mat[i][j]) {
                return true;
            }
        }
    }
    return false;

}

void test_bell()
{
    GraphPtr<double> g = create<double>(6);
    g->mat = { { 0, 0, 1, 1, 1, 0 }, 
               { 0, 0, 0, 0, 1, 1 }, 
               { 1, 0, 0, 1, 0, 1 }, 
               { 1, 0, 1, 0, 0, 0 }, 
               { 1, 1, 0, 0, 0, 1 }, 
               { 0, 1, 1, 0, 1, 0 } };

    graph_show(g, "bellman");
    int source = 3;
    for (int i = 0; i < 6; ++i) {
        printf("bell[%d]: %d\n", i, bellman_ford(g, i));
    }

}

int main()
{
    //test_dfs();
    test_bell();
    return 0;
}

