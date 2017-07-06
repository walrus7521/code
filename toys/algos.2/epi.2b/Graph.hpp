#include <iostream>
#include <list>
 
using namespace std;
 
class vertex 
{
public:
    vertex(int id, string val, int weight) 
        : num(id), data(val), wt(weight) {}
    int num;
    int wt;
    string data;
};

// This class represents a directed graph using adjacency list representation
class Graph
{
public:
    Graph(int nV) : V(nV) {
        adj = new list<vertex>[V];
    }
    void addEdge(int v, int w, string val, int wt) {
        // create vertex with dest id, value, and edge weight
        vertex vert(w, val, wt);
        adj[v].push_back(vert); // Add w to adj list.
    }
    void Bfs(int s) {  // prints BFS traversal from a given source s
        // Mark all the vertices as not visited
        bool *visited = new bool[V];
        for(int i = 0; i < V; i++)
            visited[i] = false;
        list<int> queue;
        visited[s] = true; // mark current node visited
        queue.push_back(s); // and enqueue it
        list<vertex>::iterator i; // used for adjacent vertices of a vertex
        while(!queue.empty()) {
            // Dequeue a vertex from queue and print it
            s = queue.front(); // dequeue a vertex
            cout << s << " "; // print it
            queue.pop_front();
 
            // Get all adjacent vertices of the dequeued vertex s
            // If a adjacent has not been visited, then mark it visited
            // and enqueue it
            for(i = adj[s].begin(); i != adj[s].end(); ++i) {
                int idx = i->num;
                if(!visited[idx]) {
                    visited[idx] = true;
                    queue.push_back(idx);
                }
            }
        }
    }  
    void show()
    {
        for (int i = 0; i < V; ++i) {
            for (auto &v : adj[i]) {
                cout << v.num << ": " << v.data << endl;
            }
        }
    }
private:
    int V;    // No. of vertices
    list<vertex> *adj;    // Pointer to an array containing adjacency lists
};
 

