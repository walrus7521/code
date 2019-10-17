package main

import "fmt"

type Tree struct {
    root *Node
}

type Node struct {
    left, right, p *Node
    key int
}

func (t *Tree) Insert(z *Node) {
    var y *Node = nil
    x := t.root
    for x != nil {
        y = x
        if z.key < x.key {
            x = x.left
        } else {
            x = x.right
        }
    }
    z.p = y
    if y == nil {
        t.root = z
    } else if z.key < y.key {
        y.left = z
    } else {
        y.right = z
    }
}

func (t *Tree) Min() *Node {
    if t.root == nil {
        return nil
    }
    n := t.root
    var p *Node = nil
    for n != nil {
        p = n
        n = n.left
    }
    return p;
}

func (t *Tree) Find(key int) *Node {
    n := t.root
    for n != nil && n.key != key {
        if key < n.key {
            n = n.left
        } else {
            n = n.right
        }
    }
    return n
}

func (t *Tree) Transplant(u *Node, v *Node) {
    fmt.Printf("Transplant: %d, %d\n", u.key, v.key)
    if u.p == nil {
        t.root = v
    } else if u == u.p.left {
        u.p.left = v
    } else {
        u.p.right = v
    }
    if v != nil {
        v.p = u.p
    }
}

func (t *Tree) Delete(z *Node) {
    fmt.Println("Delete: ", z.key)
    if z.left == nil {
        //fmt.Println("Transplant right")
        t.Transplant(z, z.right)
    } else if z.right == nil {
        //fmt.Println("Transplant left")
        t.Transplant(z, z.left)
    } else {
        y := t.Min()
        if y.p != z {
            t.Transplant(y, y.right)
            y.right = z.right
            y.right.p = y
            //fmt.Println("Transplant parent right")
        }
        t.Transplant(z, y)
        y.left = z.left
        y.left.p = y
        //fmt.Println("post-Transplant parent right")
    }
}

func (n *Node) Print() {
    if n == nil {
        return
    }
    n.left.Print()
    fmt.Printf("%d\n", n.key)
    n.right.Print()
}

func main() {
    a := []int {4,10,3,2}
    t := Tree{nil}
    for _,k :=  range a {
        t.Insert(&Node{nil, nil, nil, k})
    }
    t.root.Print()
    n := t.Find(3)
    if n != nil {
        fmt.Println("Got: ", n.key)
        t.Delete(n)
    }
    t.root.Print()
    //m := t.Min()
    //if m != nil {
    //    fmt.Println("Min: ", m.key)
    //}
}

