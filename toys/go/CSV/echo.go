package main

// $ 6g echo.go && 6l -o echo echo.6
// $ ./echo
//
//  ~ in another terminal ~
//
// $ nc localhost 3540


import (
    "net"
    "bufio"
    "strconv"
    "fmt"
)

const PORT = 3540

func clientConns(listener net.Listener) chan net.Conn {
    ch := make(chan net.Conn)
    i := 0
    go func() {
        for {
            client, _ := listener.Accept()
            if client == nil {
                fmt.Printf("couldn't accept: ") //err.String())
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

func serve() {
    server, _ := net.Listen("tcp", ":" + strconv.Itoa(PORT))
    if server == nil {
        panic("couldn't start listening: ") //err.String())
    }
    conns := clientConns(server)
    for {
        go handleConn(<-conns)
    }
}

func main() {
    serve()
}


