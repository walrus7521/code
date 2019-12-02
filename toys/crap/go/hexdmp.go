package main

import (
    "fmt"
    "io"
    "os"
    "encoding/hex"
)

func main() {

    stdoutDumper := hex.Dumper(os.Stdout)

    var name string
    if len(os.Args) > 1 {
        name = os.Args[1]
    } else {
        fmt.Println("need file name")
        os.Exit(1)
    }

    f, err := os.Open(name) // any binary file
    if err != nil {
        fmt.Println(err)
        return
    }
    defer f.Close()
    data := make([]byte, 4096)
    //zeroes := 0
    for {
        data = data[:cap(data)]
        n, err := f.Read(data)
        if err != nil {
            if err == io.EOF {
                break
            }
            fmt.Println(err)
            return
        }
        data = data[:n]
        stdoutDumper.Write([]byte(data))
        //for _, b := range data {
        //    if b == 0 {
        //        zeroes++
        //    }
        //}
    }
    //fmt.Println("zeroes:", zeroes)
    fmt.Println()

}
