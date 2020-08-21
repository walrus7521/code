#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <set>
#include <map>
#include <cstdlib>
#include <cstring>

using namespace std;

#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)

#define TRvii(c, it) \
    for (vii::iterator it = (c).begin(); it != (c).end(); ++it)

#define INF         (99999)
#define MAX_NUM     (256)
#define DFS_WHITE   (-1)
#define DFS_BLACK   (1) // these are numbered as numComponents
#define DFS_GRAY    (2)
#define DFS_BLUE    (3)
#define DFS_RED     (4)
#define DFS_GREEN   (5)
#define DFS_YELLOW  (6)

typedef pair<int, int> ii;
typedef vector<ii> vii;

// Graphs
int E, V;
vector<vii> AdjList; // array V of pairs u and wt
priority_queue<pair<int, ii>> EdgeList;

typedef enum {
    DIRECTED,
    UNDIRECTED
} graph_type;

graph_type gr_type;

void init_graph() {
    AdjList.clear();
    EdgeList = priority_queue<pair<int, ii>>(); // reset
    AdjList.resize(MAX_NUM);
}

void read_graph(graph_type type) { // Boiler plate graph scanner
    int wt, u, v;
    gr_type = type;
    init_graph();
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &wt);
        AdjList[u].push_back(make_pair(v, wt));
        EdgeList.push(make_pair(-wt, make_pair(u, v)));// negate wts for min heap
        if (gr_type == UNDIRECTED)
            AdjList[v].push_back(make_pair(u, wt));
    }
}

// Sets
vector<int> pset(1000);
void initSet(int _size) {pset.resize(_size); REP(i, 0, _size-1) pset[i] = i;}
int findSet(int i) {return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));}
void unionSet(int i, int j) {pset[findSet(i)] = findSet(j);}
bool isSameSet(int i, int j) {return findSet(i) == findSet(j);}

