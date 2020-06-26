#!/usr/bin/env python3

from collections import deque
 
class Graph:
    def __init__(self, V):
        self.V = V  # no of vertices
        self.adj = [[] for i in range(V)]
        self.visited = [False] * (len(self.adj))

    def addEdge(self, u, v):
        self.adj[u].append(v)

    def draw(self):
        pass

    def BFS(self, s):
        queue = []
        queue.append(s)
        self.visited[s] = True
        while queue:
            s = queue.pop(0)
            print(s, end = " ")
            for i in self.adj[s]:
                if self.visited[i] == False:
                    queue.append(i)
                    self.visited[i] = True

    def DFSr(self, v):
        self.visited[v] = True
        print(v, end = " ")
        for i in self.adj[v]:
            if self.visited[i] == False:
                self.DFSr(i)

    def DFSnr(self, v):
        stack = []
        self.visited[v] = True
        stack.append(v)
        while stack:
            s = stack[-1] # last item on list
            stack.pop()
            if (not self.visited[s]):
                print(s, end = " ")
                self.visited[s] = True
            for i in self.adj[s]:
                if self.visited[i] == False:
                    stack.append(i)
                    

        
def getchar():
    a = input('').split(" ")[0]

def init(g):
    g.addEdge(0, 1) 
    g.addEdge(0, 2) 
    g.addEdge(1, 2) 
    g.addEdge(2, 0) 
    g.addEdge(2, 3) 
#   g.addEdge(3, 3) 
 
def init2(g):
    g.addEdge(1, 0) 
    g.addEdge(0, 2) 
    g.addEdge(2, 1) 
    g.addEdge(0, 3) 
    g.addEdge(1, 4) 
 
# adjacency lists
graph = {}
graph["you"]    = ["alice", "bob", "claire"]
graph["bob"]    = ["anuj", "peggy"]
graph["alice"]  = ["peggy"]
graph["claire"] = ["thom", "jonny"]
graph["anuj"]   = []
graph["peggy"]  = []
graph["thom"]   = []
graph["jonny"]  = []

def dfs(name):
    search_queue = deque()
    searched = []
    search_queue += graph[name]
    print(name)
    searched.append(name)
    while search_queue:
        person = search_queue.popleft()
        if not person in searched:
            print(person)
            search_queue += graph[person]
            searched.append(person)

# Dijkstra
graph2 = {}
graph2["start"] = {}
graph2["start"]["a"] = 6
graph2["start"]["b"] = 2
graph2["a"] = {}
graph2["a"]["fin"] = 1
graph2["b"] = {}
graph2["b"]["a"] = 3
graph2["b"]["fin"] = 5
graph2["fin"] = {}

infinity = float("inf")
costs = {}
costs["a"] = 6
costs["b"] = 2
costs["fin"] = infinity

parents = {}
parents["a"] = "start"
parents["b"] = "start"
parents["fin"] = None

processed = []

def find_lowest_cost_node(costs):
    lowest_cost = infinity
    lowest_cost_node = None
    for node in costs:
        cost = costs[node]
        if cost < lowest_cost and node not in processed:
            lowest_cost = cost
            lowest_cost_node = node
    return lowest_cost_node


def dijkstra():
    node = find_lowest_cost_node(costs)
    while node is not None:
        cost = costs[node]
        neighbors = graph2[node]
        for n in neighbors.keys():
            new_cost = cost + neighbors[n]
            if costs[n] > new_cost:
                costs[n] = new_cost
                parents[n] = node
        processed.append(node)
        node = find_lowest_cost_node(costs)

def do_dijkstra():
    dijkstra()
    # print reverse path from fin to start
    print("fin")
    node = parents["fin"]
    while node:
        print(node)
        try:
            node = parents[node]
        except KeyError:
            return

#   print(parents["fin"])
#   print(parents["a"])
#   print(parents["b"])


if __name__ == "__main__":
    g = Graph(5)
    init(g)
 
    v = 2;
#   print ("BFS from vertex {0})", v) 
#   g.BFS(v) 
    print ("DFS from vertex {0})", v) 
    g.DFSr(0)
#   g.DFSnr(0)
#   print();

#   g.draw()
#   getchar()
#   dfs("you")
#   do_dijkstra()

