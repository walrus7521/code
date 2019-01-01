package main;

import (
    "bufio"
    "fmt"
    "os"
)

// demo of mapping lines and using an array
func main() {
    //counts := make(map[string]int) // on heap
    counts := map[string]int{} // on stack
    var data []string

    input := bufio.NewScanner(os.Stdin)
    for input.Scan() {
        counts[input.Text()]++
        data = append(data, input.Text())
    }

    fmt.Println(len(counts))
    for line, n := range counts {
        fmt.Printf("%d, %s\n", n, line)
        if n > 1 {
            fmt.Printf("%d\t%s\n", n, line)
        }
    }

    for i := 0; i < len(data); i++ {
        fmt.Printf("[%d] => %s\n", i, data[i]);
    }
}
