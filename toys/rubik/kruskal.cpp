#include "graph9.hpp"

// union-find API
class subset {
public:
    int parent, rank;
};

// find set of an element i
// uses path compression.
int Find(subset subsets[], int i)
{
    // find root and make root as parent of i
    // path compression
    if (subsets[i].parent != i)
        subsets[i].parent = Find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
    int xroot = Find(subsets, x);
    int yroot = Find(subsets, y);
    // attach smaller rank tree under root of high
    // rank tree (union by rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    // if ranks are the same, make one as root and
    // increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void *a, const void *b)
{
    Edge* a1 = (Edge*) a;
    Edge* b1 = (Edge*) b;
    return (a1->key > b1->key);
}

void kruskal(Graph& g)
{
    int V = g.v; // number of vertices
    Edge result[V];
    int e = 0;
    int i = 0;

    qsort(g.arr_E, g.e, sizeof(g.arr_E[0]), myComp);
}

int main()
{
    Graph g(4,5);

    addEdge(g, 0, 1, 10);
    addEdge(g, 0, 2, 6);
    addEdge(g, 0, 3, 5);
    addEdge(g, 1, 3, 15);
    addEdge(g, 2, 3, 4);
    
    kruskal(g);
}

