#include "utils.h"

#define DFS_WHITE -1
#define DFS_BLACK 1

vector<vii> AdjList;
vi dfs_num;
int numCC;

void printPath(vi &parent, int u, int s)
{
    if (u == s) { printf("%d", u); return; }
    printPath(parent, parent[u], s);
    printf(" %d", u);
}


void dfs(int u)
{
    printf(" %d", u);  // this vertex is visited
    dfs_num[u] = DFS_BLACK; // mark vertex as visited
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
        ii v = AdjList[u][j]; // v is a (neighbor, weight) pair
        if (dfs_num[v.first] == DFS_WHITE) // important check to avoid cycle
            dfs(v.first); // visit unvisited neighbors v of vertex u
    }
}

void bfs(int n_verts, int source)
{
    vi parent; // the predecessor/parent vector
    vi dist(n_verts, 1000000000); // init distances to large enough value
    int layer = -1; // for our output printing purpose
    bool isBipartite = true; // addition of one boolean flag, initially true
    queue<int> q; // needed for layer-by-layer traversal

    dist[source] = 0; // distance to source is 0 (default)
    q.push(source); // start from source
    parent.assign(n_verts, -1);

    while (!q.empty()) {
        int u = q.front(); q.pop(); // queue: layer by layer!
        if (dist[u] != layer) printf("\nLayer %d: ", dist[u]);
        layer = dist[u];
        printf("visit %d, ", u);
        for (int j = 0; j < (int)AdjList[u].size(); j++) {
            ii v = AdjList[u][j]; // for each neighbors of u
            if (dist[v.first] == 1000000000) {
                dist[v.first] = dist[u] + 1; // v unvisited + reachable
                parent[v.first] = u; // addition: the parent of vertex v->first is u
                q.push(v.first); // enqueue v for next step
            }
            else if ((dist[v.first] % 2) == (dist[u] % 2)) // same parity
                isBipartite = false;
        }
    }
    printf("\nShortest path: ");
    printPath(parent, 7, source), printf("\n");
    printf("isBipartite? %d\n", isBipartite);
}

void test_dfs()
{
    int V, total_neighbors, id, weight;

    freopen("in_01.txt", "r", stdin); // pretty rad

    scanf("%d", &V);
    AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList
    for (int i = 0; i < V; i++) {
        scanf("%d", &total_neighbors);
        for (int j = 0; j < total_neighbors; j++) {
            scanf("%d %d", &id, &weight);
            AdjList[i].push_back(ii(id, weight));
        }
    }

    printf("Standard DFS Demo (the input graph must be UNDIRECTED)\n");
    numCC = 0;
    dfs_num.assign(V, DFS_WHITE); // sets all vertices to DFS_WHITE (unvisited)
    for (int i = 0; i < V; i++) // vertex loop
        if (dfs_num[i] == DFS_WHITE)  // if not visited
            printf("Component %d:", ++numCC), dfs(i), printf("\n");   // 3 lines here!
    printf("There are %d connected components\n", numCC);
}

void test_bfs()
{
    int v1, v2;
    int n_verts, n_edge;
    freopen("in_04.txt", "r", stdin);

    scanf("%d %d", &n_verts, &n_edge);

    AdjList.assign(n_verts, vii()); // assign blank vectors of pair<int, int>s to AdjList
    for (int i = 0; i < n_edge; i++) {
        scanf("%d %d", &v1, &v2);
        AdjList[v1].push_back(ii(v2, 0));
        AdjList[v2].push_back(ii(v1, 0));
    }

    int source = 5;
    bfs(n_verts, source);
}

void test_union_find() {
    printf("Assume that there are 5 disjoint sets initially\n");
    UnionFind UF(5); // create 5 disjoint sets
    printf("%d\n", UF.numDisjointSets()); // 5
    UF.unionSet(0, 1);
    printf("%d\n", UF.numDisjointSets()); // 4
    UF.unionSet(2, 3);
    printf("%d\n", UF.numDisjointSets()); // 3
    UF.unionSet(4, 3);
    printf("%d\n", UF.numDisjointSets()); // 2
    printf("isSameSet(0, 3) = %d\n", UF.isSameSet(0, 3)); // will return 0 (false)
    printf("isSameSet(4, 3) = %d\n", UF.isSameSet(4, 3)); // will return 1 (true)
    for (int i = 0; i < 5; i++) // findSet will return 1 for {0, 1} and 3 for {2, 3, 4}
        printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, UF.findSet(i), i, UF.sizeOfSet(i));
    UF.unionSet(0, 3);
    printf("%d\n", UF.numDisjointSets()); // 1
    for (int i = 0; i < 5; i++) // findSet will return 3 for {0, 1, 2, 3, 4}
        printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, UF.findSet(i), i, UF.sizeOfSet(i));
}

int main()
{
    //test_dfs();
    //test_bfs();
    test_union_find();
}

