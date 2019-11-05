package main

import (
    "encoding/gob"
    "encoding/csv"
    "fmt"
    "io"
    "os"
    "net"
    //"time"
    "context"
)

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

type Row = []string

func send_csv(ctx context.Context, c net.Conn) (<-chan Row, <-chan error) {
    //var one   []string
    //var two   []string
    //var three []string
    //var count int = 0

    rows := make(chan Row, 100)
    errs := make(chan error, 1)
    csvr := csv.NewReader(os.Stdin)
    csvr.Comma = ','
    csvr.Comment = '#'
    csvr.Read() // strip header
    loop:
    for {
        select {
            case <-ctx.Done():
                errs <- fmt.Errorf("parse stopped")
                break loop
            default:
                row, err := csvr.Read()
                fmt.Println(row)
                if err != nil {
                    if err == io.EOF {
                        err = nil
                    }
                    break
                }
                rows <- row
        }
        //fmt.Println(len(row))
        //fmt.Println(row)
        //for _, x := range row {
        //    fmt.Printf("=> %s\n", x)
        //}
        //count++
        //one   = append(one,   row[0])
        //two   = append(two,   row[1])
        //three = append(three, row[2])
        //msg := fmt.Sprintf("[%d] = %s,%s,%s\n", count, row[0], row[1], row[3])
        //fmt.Printf(msg)
        //err = gob.NewEncoder(c).Encode(msg)
    }
    close(rows)
    close(errs)
    //msg := "Hello, World"
    //fmt.Println("Sending", msg)
    //err := gob.NewEncoder(c).Encode(msg)
    //if err != nil {
    //    fmt.Println(err)
    //}
    fmt.Println("close")
    //c.Close()
    return rows, errs
}

func client() {
    // connect to the server
    //c, err := net.Dial("tcp", "127.0.0.1:9999")
    //if err != nil {
    //    fmt.Println(err)
    //    return
    //}

    fmt.Println("send csv")
    // send the message
    ctx := context.Background()
    rows, errs := send_csv(ctx, nil)
    for e := range errs {
        fmt.Println(e)
    }
    for r := range rows {
        fmt.Println(r)
    }
    //msg := "Hello, World"
    //fmt.Println("Sending", msg)
    //err = gob.NewEncoder(c).Encode(msg)
    //if err != nil {
    //    fmt.Println(err)
    //}
    //c.Close()
}

func main() {
    //go server()
    //time.Sleep(0 * time.Second)
    go client()
    var input string
    fmt.Scanln(&input)
}

