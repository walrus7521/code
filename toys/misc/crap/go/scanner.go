package main;

import (
    "bufio"
    "fmt"
    "os"
)

// demo reading multiple files
// and readling line by line
func main() {
    data := make([]string, 0)
    counts := make(map[string]int)
    files := os.Args[1:] // list of files
    if len(files) == 0 {
        countLines(os.Stdin, counts, &data)
    } else {
        for _, arg := range files {
            f, err := os.Open(arg)
            if err != nil {
                fmt.Fprintf(os.Stderr, "dup2: %v\n", err);
                continue
            }
            countLines(f, counts, &data)
            f.Close()
        }
    }

    fmt.Printf("hash: %d\n", len(counts))
    for line, n := range counts {
        if n > 0 {
            fmt.Printf("%d\t%s\n", n, line)
        }
    }

    fmt.Printf("array: %d\n", len(data))
    for i := 0; i < len(data); i++ {
        fmt.Printf("[%d] => %s\n", i, data[i]);
    }
}

func countLines(f *os.File, counts map[string]int, data *[]string) {
    input := bufio.NewScanner(f)
    for input.Scan() {
        counts[input.Text()]++
        *data = append(*data, input.Text())
    }
}

