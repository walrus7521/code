#include "util.h"

int main()
{
    priority_queue<pair<int, ii>> EdgeList;
    int E, V, wt, u, v;
    scanf_s("%d %d", &V, &E);
    printf("[%d %d]\n", V, E);
    for (int i = 0; i < E; i++) {
        scanf_s("%d %d %d", &u, &v, &wt);
        EdgeList.push(make_pair(-wt, make_pair(u, v)));// negate wts for min heap
        printf("%d %d %d\n", u, v, wt);
    }

    int mst_cost = 0;
    initSet(V);
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

