package main

// Running this code with go run main.go 2> trace.out sends the tracing output to the file trace.out, 
// which can then be read with: go tool trace trace.out.


import (
    "log"
    "os"
    "runtime/trace")

func test1() {
}

func test2() {
}

func test3() {
}

func main() {
    f, err := os.Create("trace.out")
    if err != nil {
        log.Fatalf("failed to create trace output file: %v", err)
    }
    defer func() {
        if err := f.Close(); err != nil {
            log.Fatalf("failed to close trace file: %v", err)
        }
    }()

    if err := trace.Start(f); err != nil {
        log.Fatalf("failed to start trace: %v", err)
    }
    defer trace.Stop()

    test1()
    go test2()
    test3()
}


