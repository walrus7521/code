#include "utils2.h"

vector<int> pset(1000); // 1000 is just an initial number, it is user-adjustable.

void initSet(int _size) { 
    pset.resize(_size); REP (i, 0, _size - 1) pset[i] = i; 
}
int findSet(int i) { 
    return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); 
}
void unionSet(int i, int j) { 
    pset[findSet(i)] = findSet(j); 
}
bool isSameSet(int i, int j) { 
    return findSet(i) == findSet(j); 
}

void dumpSets() {
    REP(i, 0, pset.size()) printf("find(%d): %d\n", i, findSet(i));
}

int main()
{
    initSet(5);
    unionSet(1,3);
    dumpSets();
}

