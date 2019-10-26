package main

import (
    "fmt"
    "sync"
)

type Item int

type Node struct {
    value Item
}

func (n *Node) String() string {
    return fmt.Sprintf("%v", n.value)
}

type Directed int

const (
    DIRECTED Directed = iota
    UNDIRECTED
)

type ItemGraph struct {
    nodes []*Node
    edges map[Node][]*Node
    directed Directed
    lock  sync.RWMutex
}

func (g *ItemGraph) AddNode(n *Node) {
    g.lock.Lock()
    defer g.lock.Unlock()
    g.nodes = append(g.nodes, n)
}

func (g *ItemGraph) AddEdge(n1, n2 *Node) {
    g.lock.Lock()
    defer g.lock.Unlock()
    if g.edges == nil {
        g.edges = make(map[Node][]*Node)
    }
    g.edges[*n1] = append(g.edges[*n1], n2)
    if g.directed == UNDIRECTED {
        g.edges[*n2] = append(g.edges[*n2], n1)
    }
}

func (g *ItemGraph) String() {
    g.lock.RLock()
    defer g.lock.RUnlock()
    s := ""
    for i := 0; i < len(g.nodes); i++ {
        s += g.nodes[i].String() + " -> "
        near := g.edges[*g.nodes[i]]
        for j := 0; j < len(near); j++ {
            s += near[j].String() + " "
        }
        s += "\n"
    }
    fmt.Println(s)
}

func main() {
    graph := ItemGraph{directed: DIRECTED}
    node1 := Node{42}
    node2 := Node{17}
    node3 := Node{93}
    graph.AddNode(&node1)
    graph.AddNode(&node2)
    graph.AddNode(&node3)
    graph.AddEdge(&node1, &node2)
    graph.AddEdge(&node1, &node3)
    graph.AddEdge(&node3, &node2)
    graph.String()
}

