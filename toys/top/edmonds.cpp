#include "util.h"

map<int, int> p;
int f, s, t;

void augmentPath(int v, int minEdge)
{
    if (v == s) {
        f = minEdge;
        return;
    }
    else if (p.count(v)) { // augment if there is a path
        // we need AdjMatrix for fast lookup here
        augmentPath(p[v], min(minEdge, AdjMatrix[p[v]][v]));
        AdjMatrix[p[v]][v] -= f; // forward edges -> decrease
        AdjMatrix[v][p[v]] += f; // backward edges -> increase
    }
}

void edmonds()
{
    int max_flow = 0;

    while (1) {
        f = 0;

        queue<int> q; map<int,int> dist; // O(E) BFS and record path p
        q.push(s); dist[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;

            TRvii (AdjList[u], v) { // each neighbor of u
                // check AdjMatrix as edges may disappear
                if (AdjMatrix[u][v->first] > 0 && !dist.count(v->first)) {
                    dist[v->first] = dist[u] + 1; // then v is reachable from u
                    q.push(v->first); // enqueue v for next steps
                    p[v->first] = u; // u is parent of v->first
                }
            }
        }
        augmentPath(t, INF);
        if (f == 0) break;
        max_flow += f;
    }
    printf("max flow = %d\n", max_flow);

}

int main()
{
    read_graph(DIRECTED);
    show_matrix();
    s = 0, t = 5;
    edmonds();
}
