// client.go
// go get golang.org/x/net/websocket
// https://github.com/websockets/ws/issues/790

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

        fmt.Print("Enter text: ")
        var input string
        fmt.Scanln(&input)
        fmt.Print(input)
        websocket.Message.Send(ws, &input)

        fmt.Println("\nwaiting for reply")
        websocket.Message.Receive(ws, &m)
        fmt.Println("got response")

        fmt.Println(m)
    }
}
