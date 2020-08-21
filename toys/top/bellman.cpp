#include "util.h"


void bellman(int s)
{
    vector<int> dist(V, INF); dist[s] = 0;
    REP (i, 0, V-1)
        REP (u, 0, V-1)
        TRvii (AdjList[u], v)
            dist[v->first] = min(dist[v->first], dist[u] + v->second);
    REP (i, 0, V-1)
        printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

    // check for negative cycle
    bool negative_cycle_exists = false;
    REP (u, 0, V-1)
        TRvii (AdjList[u], v)
            if (dist[v->first] > dist[u] + v->second)
                negative_cycle_exists = true;
    printf("negative cycle exists? %d\n", negative_cycle_exists);

    
}

int main()
{
    read_graph(DIRECTED);
    bellman(0);
}
