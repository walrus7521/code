package main

import (
        "strconv"
        "strings"
        "fmt"
        "os"
       )

func echo1() {
    var s, sep string
    for i:= 1; i < len(os.Args); i++ {
        s += sep + os.Args[i]
        sep = " "
    }
    fmt.Println(s)
}

func echo2() {
    s, sep := "", " "
    for _, arg := range os.Args[1:] {
        s += sep + arg
        sep = " "
    }
    fmt.Println(s)
}

func echo2a() {
    s, del := "", " : "
    for i, arg := range os.Args[1:] {
        s = strconv.Itoa(i) + del + arg
        fmt.Println(s)
    }
}

func echo3() {
    fmt.Println(strings.Join(os.Args[1:], " "))
}

func echo4() {
    fmt.Println(os.Args[0:])
}

func main() {
    //echo1()
    echo2a()
    //echo3()
    //echo4()
}

