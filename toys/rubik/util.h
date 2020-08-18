#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <cstdlib>

using namespace std;

#define MAX_NUM 256
#define DFS_WHITE   (-1)
#define DFS_BLACK   (1) // these are numbered as numComponents
#define DFS_BLUE    (2)
#define DFS_RED     (3)
#define DFS_GREEN   (4)
#define DFS_YELLOW  (5)

typedef pair<int, int> ii;
typedef vector<ii> vii;

int E, V;
vector<vii> AdjList; // array V of pairs u and wt

void init_graph() {
    AdjList.clear();
    AdjList.resize(MAX_NUM);
}

void read_graph() {
    int wt, u, v;
    // Boiler plate graph scanner
    init_graph();
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &wt);
        AdjList[u].push_back(make_pair(v, wt));
    }
}


#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)

#define TRvii(c, it) \
    for (vii::iterator it = (c).begin(); it != (c).end(); ++it)

// Sets
vector<int> pset(1000);
void initSet(int _size) {pset.resize(_size); REP(i, 0, _size-1) pset[i] = i;}
int findSet(int i) {return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));}
void unionSet(int i, int j) {pset[findSet(i)] = findSet(j);}
bool isSameSet(int i, int j) {return findSet(i) == findSet(j);}

