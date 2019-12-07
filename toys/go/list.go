package main;

import "fmt"

// add tail
// push front/back
// pop front/back
// reverse

type List struct {
    head *ListNode
    count int
}

type ListNode struct {
    key int
    next *ListNode
}

func (list *List) Size() int {
    return list.count
}

func (list *List) IsEmpty() bool {
    return (list.count == 0)
}

func (list *List) AddHead(key int) {
    list.head = &ListNode{key, list.head}
    list.count++
}

func (list *List) AddTail(key int) {
    curr := list.head
    newNode := &ListNode{key, nil}
    list.count++

    if curr == nil {
        list.head = newNode
        return
    }

    for curr.next != nil {
        curr = curr.next
    }

    curr.next = newNode
}

func (list *List) DeleteNode(delkey int) bool {
	temp := list.head
	if list.IsEmpty() {
		fmt.Println("EmptyListException")
		return false
	}

	if delkey == list.head.key {
		list.head = list.head.next
		list.count--
		return true
	}

	for temp.next != nil {
		if temp.next.key == delkey {
			temp.next = temp.next.next
			list.count--
			return true
		}
		temp = temp.next
	}
	return false
}

func (list *List) Find(data int) bool {
	temp := list.head
	for temp != nil {
		if temp.key == data {
			return true
		}
		temp = temp.next
	}
	return false
}

func (list *List) Print() {
    temp := list.head
    for temp != nil {
        fmt.Print(temp.key, " ")
        temp = temp.next
    }
    fmt.Println("")
}

func main() {
    mylist  := List{}
    keys  := []int {42, 43, 44, 17}
    ckeys := []rune {'a','b','c','d'} // unicode
    skeys := []string {"aa","bb","cc","dd"}

    for _,v := range keys {
        mylist.AddHead(v)
    }

    fmt.Printf("%d items in list: ", mylist.Size())
    mylist.Print()
    var index = 0
    for mylist.IsEmpty() != true {
        var v = keys[index]
        var r = ckeys[index]
        var s = skeys[index]
        var c = string(r)
        index++
        fmt.Printf("dude: %d %c %s => %s\n", v, r, c, s)
        mylist.DeleteNode(v)
    }

    fmt.Printf("%d items in list: ", mylist.Size())
    mylist.Print()
    if mylist.Find(4) == true {
        fmt.Printf("found\n")
    } else {
        fmt.Printf("not found\n")
    }
}

