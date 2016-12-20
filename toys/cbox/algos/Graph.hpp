#include <iostream>
#include <list>
 
using namespace std;
 
// This class represents a directed graph using adjacency list representation
class Graph
{
public:
    Graph(int nV) : V(nV) {
        adj = new list<int>[V];
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v’s list.
    }
    void Bfs(int s) {  // prints BFS traversal from a given source s
        // Mark all the vertices as not visited
        bool *visited = new bool[V];
        for(int i = 0; i < V; i++)
            visited[i] = false;
        list<int> queue;
        visited[s] = true; // mark current node visited
        queue.push_back(s); // and enqueue it
        list<int>::iterator i; // used for adjacent vertices of a vertex
        while(!queue.empty()) {
            // Dequeue a vertex from queue and print it
            s = queue.front(); // dequeue a vertex
            cout << s << " "; // print it
            queue.pop_front();
 
            // Get all adjacent vertices of the dequeued vertex s
            // If a adjacent has not been visited, then mark it visited
            // and enqueue it
            for(i = adj[s].begin(); i != adj[s].end(); ++i) {
                if(!visited[*i]) {
                    visited[*i] = true;
                    queue.push_back(*i);
                }
            }
        }
    }  
private:
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
};
 


