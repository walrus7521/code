package main

import (
    "fmt"
    "net"
    "bufio"
    "strconv"
)

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

func main() {

    serve()

}

