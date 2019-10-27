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

func (list *List) Size() int {
    return list.count
}

func (list *List) IsEmpty() bool {
    return (list.count == 0)
}

func (list *List) AddHead(value int) {
    list.head = &ListNode{value, list.head}
    list.count++
}

func (list *List) AddTail(value int) {
    curr := list.head
    newNode := &ListNode{value, nil}
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

func (list *List) DeleteNode(delValue int) bool {
	temp := list.head
	if list.IsEmpty() {
		fmt.Println("EmptyListException")
		return false
	}

	if delValue == list.head.value {
		list.head = list.head.next
		list.count--
		return true
	}

	for temp.next != nil {
		if temp.next.value == delValue {
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
		if temp.value == data {
			return true
		}
		temp = temp.next
	}
	return false
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
    mylist  := List{}
    values  := []int {42, 43, 44, 17}
    cvalues := []rune {'a','b','c','d'} // unicode
    svalues := []string {"aa","bb","cc","dd"}

    for _,v := range values {
        mylist.AddHead(v)
    }

    fmt.Printf("%d items in list: ", mylist.Size())
    mylist.Print()
    var index = 0
    for mylist.IsEmpty() != true {
        var v = values[index]
        var r = cvalues[index]
        var s = svalues[index]
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

