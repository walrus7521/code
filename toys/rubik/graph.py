#!/usr/bin/env python3

import networkx
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


if __name__ == "__main__":
#   g = Graph(5)
#   init(g)
 
#   v = 2;
#    print ("BFS from vertex {0})", v) 
#   g.BFS(v) 
#   print ("DFS from vertex {0})", v) 
#   g.DFSr(0)
#   g.DFSnr(0)
#   print();

#   g.draw()
#   getchar()
    dfs("you")    

