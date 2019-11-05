package main

import (
    "fmt"
    "io"
    "net"
    "encoding/gob"
    "encoding/csv"
    //"bytes"
    //"bufio"
    //"strings"
    "os"
)

func handleServerConnection(c net.Conn) {
    // receive the message
    var msg string
    err := gob.NewDecoder(c).Decode(&msg)
    if err != nil {
        fmt.Println(err)
    } else {
        fmt.Println("Received", msg)
    }
    c.Close()
}

func server() {
    // listen on a port
    ln, err := net.Listen("tcp", ":9999")
    if err != nil {
        fmt.Println(err)
        return
    }

    for {
        fmt.Println("waiting")
        // accept a connection
        c, err := ln.Accept()
        if err != nil {
            fmt.Println(err)
            continue
        }
        // handle the connection
        go handleServerConnection(c)
    }
}

func get_stream(input, errors chan<- string) {
    var one   []string
    var two   []string
    var three []string
    var count int = 0

    csvr := csv.NewReader(os.Stdin)
    csvr.Comma = ','
    csvr.Comment = '#'
    for {
        row, err := csvr.Read()
        if err != nil {
            if err == io.EOF {
                err = nil
            }
            errors <- "eof"
            break
        }
            //fmt.Println(len(row))
            //fmt.Println(row)
            //for _, x := range row {
            //    fmt.Printf("=> %s\n", x)
            //}
        count++
        one   = append(one,   row[0])
        two   = append(two,   row[1])
        three = append(three, row[2])
        buf := fmt.Sprintf("[%d] =%s,%s,%s", count, row[0], row[1], row[3])
        if len(buf) == 0 {
            errors <- "no more data"
        } else {
            input <- buf
        }
    }
}

func main() {
    go server()

    userInput := make(chan string)
    errors := make(chan string)

    defer func() {
        close(userInput)
        close(errors)
        fmt.Println("i'm out!")
    }()

    //go get_userInput(userInput)
    go get_stream(userInput, errors)
    for {
        select {
        case e := <-errors:
            fmt.Println(e)
            return
        case x := <-userInput:
            fmt.Printf("dude %s\n", x)
            break
        }
    }
}

