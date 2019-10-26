// client.go

package main

import (
    "fmt"
    "golang.org/x/net/websocket"
)

func main() {
    ws, err := websocket.Dial("ws://10.0.0.138:8080", "", "http://10.0.0.138:8080")

    if err != nil {
        fmt.Println(err)
        return
    }

    for {
        var m string

        websocket.Message.Receive(ws, &m)

        fmt.Println(m)
    }
}
