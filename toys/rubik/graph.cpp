#include <cstdio>
#include <vector>
#include <list>
using namespace std;

const int V = 5;
vector<int> adj[V];
bool visited[V];

void init()
{
    for (auto const& i : visited) {
        visited[i] = false;
    }
}

void addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void BFS(int s)
{
    bool visited[V] = {false};
    list<int> queue;
    queue.push_back(s);
    visited[s] = true;
    while (queue.size()) {
        int v = queue.front();
        queue.pop_front();
        printf("%d ", v);
        for (auto const& i : adj[v]) {
            if (visited[i] == false) {
                queue.push_back(i);
                visited[i] = true;
            }
        }
    }

}

void DFS(int s)
{
    list<int> stack;
    stack.push_front(s);
    while (stack.size()) {
        int v = stack.front();
        stack.pop_front();
        if (visited[v] == false) {
            printf("%d ", v);
            visited[v] = true;
        }
        for (auto const& i : adj[v]) {
            if (visited[i] == false) {
                stack.push_front(i);
            }
        }
    }

}

int main()
{
    init();
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 2);
    addEdge(2, 0);
    addEdge(2, 3);
    BFS(2);
    printf("\n");
    DFS(0);
    printf("\n");
}


