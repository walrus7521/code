#!/usr/bin/env python3

import networkx
 
class Graph:
    def __init__(self, V):
        self.V = V  # no of vertices
        self.adj = [[] for i in range(V)]
        self.gx    = networkx.Graph()

    def addEdge(self, u, v):
        self.adj[u].append(v)
        self.gx.add_edge(u, v)

    def draw(self):
        networkx.spring_layout(self.gx)
        networkx.draw_spring(self.gx, with_labels=True, node_color='y')
        #networkx.draw_networkx(self.gx)

    def BFS(self, s):
        visited  = [False] * (len(self.adj))
        queue = []
        queue.append(s)
        visited[s] = True
        while queue:
            s = queue.pop(0)
            print(s, end = " ")
            for i in self.adj[s]:
                if visited[i] == False:
                    queue.append(i)
                    visited[i] = True
        
    def DFS(self, v):
        stack = []
        visited = [False] * (len(self.adj))
        stack.append(v)
        while stack:
            s = stack[-1] # last item on list
            stack.pop()
            if (not visited[s]):
                print(s, end = " ")
                visited[s] = True
            for i in self.adj[s]:
                if visited[i] == False:
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
 
if __name__ == "__main__":
    g = Graph(5)
    init2(g)
 
    v = 2;
    print ("BFS from vertex {0})", v) 
    g.BFS(v) 
    print();
#exit(0)
    print ("DFS from vertex {0})", v) 
    g.DFS(0) 
    print();

#   g.draw()
#   getchar()
    

