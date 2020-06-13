#!/usr/bin/env python3

from collections import defaultdict 
import networkx
 
class Graph:
    def __init__(self):
        self.graph = defaultdict(list)
        self.gx    = networkx.Graph()

    def addEdge(self, u, v):
        self.graph[u].append(v)
        self.gx.add_edge(u, v)

    def draw(self):
        networkx.spring_layout(self.gx)
        networkx.draw_spring(self.gx, with_labels=True, node_color='y')
        #networkx.draw_networkx(self.gx)

    def BFS(self, s):
        visited  = [False] * (len(self.graph))
        queue = []
        queue.append(s)
        visited[s] = True
        while queue:
            s = queue.pop(0)
            print(s, end = " ")
            for i in self.graph[s]:
                if visited[i] == False:
                    queue.append(i)
                    visited[i] = True
        
    def DFSUtil(self, v, visited): 
        # Mark the current node as visited  
        # and print it 
        visited[v] = True
        print(v, end = ' ') 
        # Recur for all the vertices  
        # adjacent to this vertex 
        for i in self.graph[v]: 
            if visited[i] == False: 
                self.DFSUtil(i, visited) 
  
    # The function to do DFS traversal. It uses 
    # recursive DFSUtil() 
    def DFS(self, v): 
        # Mark all the vertices as not visited 
        visited = [False] * (max(self.graph)+1) 
        # Call the recursive helper function  
        # to print DFS traversal 
        self.DFSUtil(v, visited) 


def get_char():
    a = input('').split(" ")[0]
   
if __name__ == "__main__":
    g = Graph()

    g.addEdge(0, 1) 
    g.addEdge(0, 2) 
    g.addEdge(1, 2) 
    g.addEdge(2, 0) 
    g.addEdge(2, 3) 
    g.addEdge(3, 3) 
  
    v = 2;
    print ("BFS from vertex {0})", v) 
    g.BFS(v) 
    print();
    print ("DFS from vertex {0})", v) 
    g.DFS(v) 
    print();
    

