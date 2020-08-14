#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// data structure to store graph edges
struct Edge {
	int src, dest;
};

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors to represent an adjacency list
	vector<vector<int>> adjList;

	// Graph Constructor
	Graph(vector<Edge> const &edges, int N)
	{
		// resize the vector to N elements of type vector<int>
		adjList.resize(N);

		// add edges to the undirected graph
		for (auto &edge: edges)
		{
			adjList[edge.src].push_back(edge.dest);
			adjList[edge.dest].push_back(edge.src);
		}
	}
};

// node to store vertex and its parent info in BFS
struct Node
{
	int v, parent;
};

// Perform BFS on graph starting from vertex src and
// returns true of cycle is found in the graph
bool BFS(Graph const &graph, int src, int N)
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
		for (int u : graph.adjList[node.v])
		{
			if (!discovered[u])
			{
				// mark it discovered
				discovered[u] = true;

				// construct the queue node containing info
				// about vertex and push it into the queue
				q.push({ u, node.v });
			}

			// u is discovered and u is not a parent
			else if (u != node.parent)
			{
				// we found a cross-edge ie. cycle is found
				return true;
			}
		}
	}

	// No cross-edges found in the graph
	return false;
}

// Check if an undirected graph contains cycle or not
int main()
{
	// initialize edges as per above diagram
	vector<Edge> edges =
	{
		{1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {5, 9},
		{5, 10}, {4, 7}, {4, 8}, {7, 11}, {7, 12}, {6, 10}
		// edge (6->10) introduces a cycle in the graph
	};

	// Number of nodes in the graph
	int N = 13;

	// create a graph from given edges
	Graph graph(edges, N);

	// Do BFS traversal in connected components of graph
	if (BFS(graph, 1, N))
		cout << "Graph contains cycle";
	else
		cout << "Graph doesn't contain any cycle";

	return 0;
}
