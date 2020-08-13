#include "graph9.hpp"

using namespace std;

// node to store vertex and its parent info in BFS
struct Node
{
    int v, parent;
};

bool BFS(Graph const &g, int src, int N)
{
    // stores vertex is discovered or not
    vector<bool> discovered(N);

    // mark source vertex as discovered
    discovered[src] = true;

    // create a queue used to do BFS and
    // push source vertex into the queue
    queue<Node> q;
    q.push({src, -1});

    // loop till queue is empty
    while (!q.empty())
    {
        // pop front node from queue and print it
        Node node = q.front();
        q.pop();

        // do for every edge (v -> u)
        for (auto u : g.adj[node.v])
        {
            if (!discovered[u.first])
            {
                // mark it discovered
                discovered[u.first] = true;

                // construct the queue node containing info
                // about vertex and push it into the queue
                q.push({ u.first, node.v });
            }

            // u is discovered and u is not a parent
            else if (u.first != node.parent)
            {
                // we found a cross-edge ie. cycle is found
                return true;
            }
        }
    }

    // No cross-edges found in the graph
    return false;
}

bool check_cycle(Graph& t, Edge& e)
{
    Graph tmp_g(t.adj.size()+1);

    tmp_g = t;
    addEdge(tmp_g, e.p.first, e.p.second, e.key);
    return BFS(tmp_g, e.p.first, tmp_g.adj.size());
}

void kruskal(Graph& g, int s)
{
    priority_queue<pair<int, int>, vector<pair<int,int>>> pq;
    vector<int> key(g.adj.size(), INF);
    vector<int> parent(g.adj.size(), -1);
    vector<bool> inMST(g.adj.size(), false);
    Graph T(g.adj.size());

    pq.push(make_pair(s, 0));
    key[s] = 0;

    for (auto e : g.E) {
        bool has_cycle = check_cycle(T, e);
        if (!has_cycle) {
            cout <<"add e: " << e.p.first << "," << e.p.second << " cost: " << e.key << endl;
            addEdge(T, e.p.first, e.p.second, e.key);
        } else {
            cout <<"cycle e: " << e.p.first << "," << e.p.second << " cost: " << e.key << endl;
        }
    }
    showGraph(T);
}

int main()
{
    Graph g(8);

    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 3, 4);
    addEdge(g, 1, 4, 3);
    addEdge(g, 2, 4, 2);
    addEdge(g, 3, 4, 5);

    kruskal(g, 1);
}

