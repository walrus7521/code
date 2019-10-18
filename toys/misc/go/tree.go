package main

import "fmt"

type Color int

const (
    RED Color = iota
    BLACK
)

type Tree struct {
    root *Node
}

type Node struct {
    left, right, p *Node
    key int
    color Color
}

func (t *Tree) LeftRotate(x *Node) {
    fmt.Println("LeftRotate")
    return
    y := x.right
    x.right = y.left
    if y.left != nil {
        y.left.p = x
    }
    y.p = x.p
    if x.p == nil {
        t.root = y
    } else if x == x.p.left {
        x.p.left = y
    } else {
        x.p.right = y
    }
    y.left = x
    x.p = y
}

func (t *Tree) RightRotate(y *Node) {
    fmt.Println("RightRotate")
    return
    x := y.left
    y.left = x.right
    if x.right != nil {
        x.right.p = y
    }
    x.p = y.p
    if y.p == nil {
        t.root = x
    } else if y == y.p.right {
        y.p.right = x
    } else {
        y.p.left = x
    }
    x.right = y
    y.p = x
}

func (t *Tree) RBInsertFixup(x *Node) {
    for x != t.root && x.color == BLACK {
        if x == x.p.left {
            w := x.p.right
            if w.color == RED {
                w.color = BLACK
                x.p.color = RED
                t.LeftRotate(x.p)
                w = x.p.right
            }
            if w.left.color == BLACK && w.right.color == BLACK {
                w.color = RED
                x = x.p
            } else if w.right.color == BLACK {
                w.left.color = BLACK
                w.color = RED
                t.RightRotate(w)
                x = x.p.right
            }
            w.color = BLACK
            x.p.color = BLACK
            t.LeftRotate(x.p)
        } else {
            w := x.p.left
            if w.color == RED {
                w.color = BLACK
                x.p.color = RED
                t.RightRotate(x.p)
                w = x.p.left
            }
            if w.right.color == BLACK && w.left.color == BLACK {
                w.color = RED
                x = x.p
            } else if w.left.color == BLACK {
                w.right.color = BLACK
                w.color = RED
                t.LeftRotate(w)
                x = x.p.left
            }
            w.color = BLACK
            x.p.color = BLACK
            t.RightRotate(x.p)
        }
    }
    t.root.color = BLACK
}

func (t *Tree) RBInsert(z *Node) {
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
    } else {
        if z.key < y.key {
            y.left = z
        } else {
            y.right = z
        }
    }
    z.left = nil
    z.right = nil
    z.color = RED
    t.RBInsertFixup(z)
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
        //t.Insert(&Node{nil, nil, nil, k, RED})
        t.RBInsert(&Node{nil, nil, nil, k, RED})
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

