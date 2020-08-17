#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>

using namespace std;

typedef pair<int, int> ii;

#define REP(i, a, b) \
    for (int i = int(a); i <= int(b); i++)
// Sets
vector<int> pset(1000);
void initSet(int _size) {pset.resize(_size); REP(i, 0, _size-1) pset[i] = i;}
int findSet(int i) {return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));}
void unionSet(int i, int j) {pset[findSet(i)] = findSet(j);}
bool isSameSet(int i, int j) {return findSet(i) == findSet(j);}

