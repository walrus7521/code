package main

import (
    "fmt"
      //"strings"
    "log"
    "os"
    "runtime/trace")

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

const MAX_DEPTH int = 16

func (n *Node) _print_t(is_left int, offset int, depth int, s *[MAX_DEPTH][255]byte) int {
    var b [MAX_DEPTH]byte
    var i int
    width := 5
    if n == nil {
        return 0
    }
    bstr := fmt.Sprintf("%s", b)
    bstr = fmt.Sprintf("(%03d)", n.key)
    for i, _ := range bstr {
        b[i] = byte(bstr[i])
    }

    left  := n.left._print_t(1, offset, depth + 1, s)
    right := n.right._print_t(0, offset + left + width, depth + 1, s)

    for i = 0; i < width; i++ {
        (*s)[depth][offset + left + i] = b[i];
    }
    if depth > 0 && is_left > 0 {
        for i = 0; i < width + right; i++ {
            (*s)[depth - 1][offset + left + width/2 + i] = '-'
        }
        (*s)[depth - 1][offset + left + width/2] = '.'
    } else if (depth >0 && is_left == 0) {
        for i = 0; i < left + width; i++ {
            (*s)[depth - 1][offset - width/2 + i] = '-'
        }
        (*s)[depth - 1][offset + left + width/2] = '.'
    }
    return left + width + right;
}

func (tree *Node) print_t() int {
    var  s[MAX_DEPTH][255]byte;
    var i int;
    for i = 0; i < MAX_DEPTH; i++ {
        str := fmt.Sprintf("%s", s[i])
        fmt.Sprintf(str, "%80s", " ");
    }
    tree._print_t(0, 0, 0, &s);

    for i = 0; i < MAX_DEPTH; i++ {
        str := fmt.Sprintf("%s", s[i])
        fmt.Printf("%s\n", str);
    }
    return 0
}

func (t *Tree) LeftRotate(x *Node) {
    fmt.Println("LeftRotate")
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

// https://www.geeksforgeeks.org/c-program-red-black-tree-insertion
func (t *Tree) RBInsertFixup(z *Node) {
    fmt.Println("fixup")
    for z.p.color == RED {
        if z.p.key == z.p.p.left.key {
            y := z.p.p.right
            if y.color == RED {
                z.p.color = BLACK
                y.color = BLACK
                z.p.p.color = RED
                z = z.p.p
            } else if z.key == z.p.right.key {
                z = z.p
                fmt.Println("rotr 1")
                t.LeftRotate(z)
            }
            z.p.color = BLACK
            z.p.p.color = RED
            fmt.Println("rotl 1")
            t.RightRotate(z.p.p)
        } else {
            y := z.p.p.left
            if y.color == RED {
                z.p.color = BLACK
                y.color = BLACK
                z.p.p.color = RED
                z = z.p.p
            } else if z.key == z.p.left.key {
                z = z.p
                fmt.Println("rotl 2")
                t.RightRotate(z)
            }
            z.p.color = BLACK
            z.p.p.color = RED
            fmt.Println("rotr 2")
            t.LeftRotate(z.p.p)
        }
    }
    t.root.color = BLACK
}

func (t *Tree) RBInsertFixup2(x *Node) {
    fmt.Println("fixup")
    if x == t.root {
        fmt.Println("x is root")
    }
    if x.color == BLACK {
        fmt.Println("fixup BLACK")
    }
    if x.color == RED {
        fmt.Println("fixup RED")
    }
    for x != t.root && x.color == RED {
        fmt.Println("fixup black")
        if x == x.p.left {
            w := x.p.right
            if w.color == RED {
                w.color = BLACK
                x.p.color = RED
                fmt.Println("rotr")
                t.LeftRotate(x.p)
                w = x.p.right
            }
            if w.left.color == BLACK && w.right.color == BLACK {
                w.color = RED
                x = x.p
            } else if w.right.color == BLACK {
                w.left.color = BLACK
                w.color = RED
                fmt.Println("rotr")
                t.RightRotate(w)
                x = x.p.right
            }
            w.color = BLACK
            x.p.color = BLACK
            fmt.Println("rotl")
            t.LeftRotate(x.p)
        } else {
            w := x.p.left
            if w.color == RED {
                w.color = BLACK
                x.p.color = RED
                fmt.Println("rotr")
                t.RightRotate(x.p)
                w = x.p.left
            }
            if w.right.color == BLACK && w.left.color == BLACK {
                w.color = RED
                x = x.p
            } else if w.left.color == BLACK {
                w.right.color = BLACK
                w.color = RED
                fmt.Println("rotl")
                t.LeftRotate(w)
                x = x.p.left
            }
            w.color = BLACK
            x.p.color = BLACK
            fmt.Println("rotr")
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
    fmt.Println("Transplant")
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
            //fmt.Println("Transplant parent right")
            t.Transplant(y, y.right)
            y.right = z.right
            y.right.p = y
        }
        //fmt.Println("post-Transplant parent right")
        t.Transplant(z, y)
        y.left = z.left
        y.left.p = y
    }
}

func (n *Node) Print() {
    if n == nil {
        return
    }
    n.left.Print()
    if n.p != nil {
        fmt.Printf("%d %d\n", n.key, n.p.key)
    } else {
        fmt.Printf("%d\n", n.key)
    }
    n.right.Print()
}

func test_tree() {
    //a := []int {4,10,3,2}
    //a := []int {10, 5, 4, 3, 7, 16, 13, 11, 20, 18, 17, 19, 30};
    a := []int {1,2,3,4,5,6,7,8,9,10,13};

    t := Tree{nil}
    for _,k :=  range a {
        //t.Insert(&Node{nil, nil, nil, k, RED})
        t.RBInsert(&Node{nil, nil, nil, k, BLACK})
    }
    t.root.print_t()
    //t.root.Print()
    n := t.Find(7)
    if n != nil {
        fmt.Println("Got: ", n.key)
        t.Delete(n)
    }
    //t.root.Print()
    t.root.print_t()
    //m := t.Min()
    //if m != nil {
    //    fmt.Println("Min: ", m.key)
    //}

}

func main() {
    f, err := os.Create("trace.out")
    if err != nil {
        log.Fatalf("failed to create trace output file: %v", err)
    }
    defer func() {
        if err := f.Close(); err != nil {
            log.Fatalf("failed to close trace file: %v", err)
        }
    }()

    if err := trace.Start(f); err != nil {
        log.Fatalf("failed to start trace: %v", err)
    }
    defer trace.Stop()

    // your program here
    test_tree()
}


