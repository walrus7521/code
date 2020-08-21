#include "util.h"

// for Maximum Spanning Tree - sort edges in decreasing order, ie, max heap
void kruskal()
{
    int mst_cost = 0;
    // use Union-Find to exclude cycles
    initSet(V);
    // eventually the number of disjoint sets is one
    while (!EdgeList.empty()) {
        pair<int, ii> front = EdgeList.top(); EdgeList.pop();
        if (!isSameSet(front.second.first, front.second.second)) {
            // no cycle
            mst_cost += (-front.first); // add negated -weight of e
            unionSet(front.second.first, front.second.second); // link vertices
            printf("add: %d -- %d == %d\n", front.second.first, 
                    front.second.second, -front.first);
        }
    }
    printf("mst cost: %d\n", mst_cost);
}

int main()
{
    read_graph(UNDIRECTED);
    kruskal();
}
