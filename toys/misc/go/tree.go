package main

import "fmt"

type Tree struct {
    root *Node
}

type Node struct {
    left, right *Node
    key int
}

func (t *Tree) Add(new *Node) {
    if t.root == nil {
        fmt.Println("insert %d root", new.key)
        t.root = new
        return
    }
    var p *Node = nil
    n := t.root
    for n != nil {
        p = n
        if new.key < n.key {
            n = n.left
        } else {
            n = n.right
        }
    }
    if new.key < p.key {
        fmt.Println("insert %d left", new.key)
        p.left = new
    } else {
        fmt.Println("insert %d right", new.key)
        p.right = new
    }
}

func (t *Tree) Delete(key int) {
}

func (n *Node) Print() {
    if n == nil {
        return
    }
    n.left.Print()
    fmt.Println("%d", n.key)
    n.right.Print()
}

func main() {
    a := []int {4,1,3,2,1}
    t := Tree{nil}
    for _,k :=  range a {
        t.Add(&Node{nil, nil, k})
    }
    t.root.Print()
}
