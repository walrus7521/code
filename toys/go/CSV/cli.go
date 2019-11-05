package main

import (
    "fmt"
    "net"
    "encoding/gob"
)

const PORT = 4000
func client() {
    // connect to the server
    c, err := net.Dial("tcp", "127.0.0.1:4000")
    //c, err := net.Dial("tcp", ":" + strconv.Itoa(PORT))
    if err != nil {
        fmt.Println(err)
        return
    }

    for {
        // send a message
        var msg string        
        _,err := fmt.Scanf("%s", &msg)
        fmt.Println("Sending", msg)
        err = gob.NewEncoder(c).Encode(msg)
        if err != nil {
            fmt.Println(err)
        }
    }
    c.Close()
}

func main() {

    client()
}
