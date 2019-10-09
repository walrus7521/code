package main;

import "fmt"


type List struct {
    head *ListNode
    count int
}

type ListNode struct {
    value int
    next *ListNode
}


func (list *List) AddHead(value int) {
    list.head = &ListNode{value, list.head}
    list.count++
}

func (list *List) Print() {
    temp := list.head
    for temp != nil {
        fmt.Print(temp.value, " ")
        temp = temp.next
    }
    fmt.Println("")
}

func main() {
    mylist := List{}
    mylist.AddHead(42)
    mylist.AddHead(43)
    mylist.AddHead(44)
    mylist.Print()
    fmt.Printf("%d\n", mylist.count)
}

