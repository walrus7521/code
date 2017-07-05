package main

import (
    "bufio"
    "fmt"
    "os"
)

func read_lines() {
    scanner := bufio.NewScanner(os.Stdin)
    for scanner.Scan() {
        line := scanner.Text()
        if line == "." {
            break
        }
        fmt.Println(line) // or do something else with line
    }
}

func read_line() {
    scanner := bufio.NewScanner(os.Stdin)
    scanner.Scan()
    line := scanner.Text()
    fmt.Println(line)
}

func main() {
    //read_line()
    read_lines()
}
