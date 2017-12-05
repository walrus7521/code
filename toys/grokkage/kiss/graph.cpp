#include "types.hpp"

using namespace std;

template <typename T>
void show(const graph_t<T> &g) {
    for (int i = 0; i < g.n_vert; i++) {
        for (int j = 0; j < g.n_vert; j++) { cout << g.m[i][j] << " "; }
        cout << endl;
    }
}

template <typename T>
void bfs(graph_t<T> &g, int start) {
    int v;
    queue<T> q;
    cout << "nvert: " << g.n_vert << endl;
    for (int i = 0; i < g.n_vert; i++) {
        g.parent[i] = -1, g.visited[i] = 0;
    }
    q.push(start);
    g.visited[start] = 1;
    while (!q.empty()) {
        v = q.front(); q.pop();
        cout << "v: " << v << endl;
        for (int i = 0; i < g.n_vert; i++) {
            if (g.m[v][i] == 1 && !g.visited[i]) {
                q.push(i);
                g.visited[i] = 1;
                g.parent[i] = v;
            }
        }
    }
}

int main()
{
    graph_t<int> g(4);
    /* directed graph */
    g.m = { { 0, 1, 1, 0 }, 
            { 0, 0, 1, 0 }, 
            { 1, 0, 0, 1 }, 
            { 0, 0, 0, 1 } };

    show(g);
    bfs(g, 2);
}

