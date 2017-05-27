#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <memory>

using namespace std;

template <typename T>
struct Graph {
    int dim;
    vector<vector<T>> mat;
};

template <typename T>
shared_ptr<Graph<T>> create(int dim)
{
    shared_ptr<Graph<T>> g(new Graph<T>);
    g->mat.resize(dim);
    g->dim = dim;
    return g;
}

template <typename T>
void graph_show(shared_ptr<Graph<T>> g, string name) {
    int i, j,n = g->mat.size();
    cout << "graph: " << name << endl;
    for (i=0; i < n; i++) {
        for (j = 0; j < n; j++) 
            cout << g->mat[i][j] << '\t';
        cout << endl;
    }
    cout << endl;
}

// is "v" reachable
int reach[20];
template <typename T>
void dfs_r(int v, shared_ptr<Graph<T>> g) {
    int i, n = g->mat.size();
    reach[v] = 1;
    cout << "dfs: " << v << endl;
    for (i = 0; i < n; i++) {
        if (g->mat[v][i] && !reach[i]) { 
            dfs_r(i, g);
        }
    }
}

void test_dfs()
{
    int n = 6;

    shared_ptr<Graph<int>> g = create<int>(6);
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
        if(reach[i]) count++; 
    }
    cout << "count: " << count << ", n: " << n << endl;
    if(count == n)
        cout << "Graph is connected" << endl; 
    else
        cout << "Graph is not connected" << endl;
}

int main()
{
    test_dfs();
    return 0;
}

