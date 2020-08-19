#include "util.h"

// applications:

void bfs(int s)
{
    queue<int> q;
    map<int, int> dist; // dist: visited and distance from source
    q.push(s); dist[s] = 0;
    while (!q.empty()) {
        int u =  q.front(); q.pop(); // queue: layer by layer
        printf("Visit: %d, Layer: %d\n", u, dist[u]);
        TRvii (AdjList[u], v) {
            if (!dist.count(v->first)) { // dist.find(v) != dist.end() also works
                dist[v->first] = dist[u] + 1; // if v not visited before + reachable from u
                q.push(v->first); // enqueue v for next steps
            }
        }
    }
}

int main()
{
    read_graph(UNDIRECTED);

    bfs(0);

    printf("\n");
}

