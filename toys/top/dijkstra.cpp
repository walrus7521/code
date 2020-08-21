#include "util.h"

void dijkstra(int s)
{
    vector<int> dist(V, INF);
    dist[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0, s));

    while (!pq.empty()) {
        ii top = pq.top(); pq.pop();
        int d = top.first, u = top.second;

        if (d == dist[u]) // process each vertex only once
            TRvii (AdjList[u], it) { // all outgoing edges
                int v = it->first, weight_u_v = it->second;
                if (dist[u] + weight_u_v < dist[v]) { // if can relax
                    dist[v] = dist[u] + weight_u_v; // relax
                    pq.push(ii(dist[v], v));
                }

            }
    }
    cout << "source: " << s << endl;
    REP (v, 0, V-1) {
        if (v == s) continue;
        cout << "v: " << v << "-> " << dist[v] << endl;
    }
    
}

int main()
{
    read_graph(UNDIRECTED);
    dijkstra(0);
}
