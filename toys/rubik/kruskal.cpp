#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>
using namespace std;

typedef pair<int, int> ii;

// Sets
vector<int> pset(1000);
void initSet(int _size) {pset.resize(_size); for(int i=0;i<=_size;i++) pset[i] = i;}
int findSet(int i) {return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));}
void unionSet(int i, int j) {pset[findSet(i)] = findSet(j);}
bool isSameSet(int i, int j) {return findSet(i) == findSet(j);}

int main()
{
    priority_queue<pair<int, ii>> EdgeList;
    int E, V, wt, u, v;
    scanf("%d %d", &V, &E);
    printf("[%d %d]\n", V, E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &wt);
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

