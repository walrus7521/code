package main

import (
    "fmt"
    "io"
    "net"
    "encoding/gob"
    "encoding/csv"
    "bufio"
    "strconv"
    //"bytes"
    //"bufio"
    //"strings"
    "os"
)

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

func clientConns(listener net.Listener) chan net.Conn {
    ch := make(chan net.Conn)
    i := 0
    go func() {
        for {
            client, _ := listener.Accept()
            if client == nil {
                fmt.Println("couldn't accept")
                continue
            }
            i++
            fmt.Printf("%d: %v <fcuk> %v\n", i, client.LocalAddr(), client.RemoteAddr())
            ch <- client
        }
    }()
    return ch
}

func handleConn(client net.Conn) {
    b := bufio.NewReader(client)
    for {
        line, err := b.ReadBytes('\n')
        if err != nil { // EOF, or worse
            break
        }
        client.Write(line)
    }
}

const PORT = 3540
func serve() {
    // listen on a port
    server, _ := net.Listen("tcp", ":" + strconv.Itoa(PORT))
    if server == nil {
        panic("couldn't start listening: ") //err.String())
    }
    conns := clientConns(server)
    for {
        go handleConn(<-conns)
    }
/*
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
 */
}

func client() {
    // connect to the server
    //c, err := net.Dial("tcp", "127.0.0.1:9999")
    c, err := net.Dial("tcp", ":" + strconv.Itoa(PORT))
    if err != nil {
        fmt.Println(err)
        return
    }

    // send the message
    msg := "Hello, World"
    fmt.Println("Sending", msg)
    err = gob.NewEncoder(c).Encode(msg)
    if err != nil {
        fmt.Println(err)
    }
    c.Close()
}

func main() {

    serve()
    //go client()

    /*
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
    */
}

