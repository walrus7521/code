package main

import (
        "io/ioutil"
        "bufio"
        "fmt"
        "os"
        "strings"
)

type LnFile struct {
    Count int
    Filenames []string
}

func countLines2(f *os.File, counts map[string]*LnFile) {
    input := bufio.NewScanner(f)
    for input.Scan() {
        key := input.Text()
        _, ok := counts[key];
        if ok {
            counts[key].Count++;
            counts[key].Filenames = append(counts[key].Filenames, f.Name())
        } else {
            counts[key] = new(LnFile)
            counts[key].Count = 1
            counts[key].Filenames = append(counts[key].Filenames, f.Name())
        }
    }
    // ignoring errors from input.Err()
}

func dup4() {
    counts := make(map[string]*LnFile)
    files  := os.Args[1:]
    if len(files) == 0 {
        countLines2(os.Stdin, counts)
    } else {
        for _, arg := range files {
            f, err := os.Open(arg)
            if err != nil {
                fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
                continue
            }
            countLines2(f, counts)
            f.Close()
        }
    }
    for line, n := range counts {
        if n.Count > 1 {
            fmt.Println("%d %v\t%s\n", n.Count, n.Filenames, line)
        }
    }
}

func dup3() {
    counts := make(map[string]int)
    for _, filename := range os.Args[1:] {
        data, err := ioutil.ReadFile(filename)
        if err != nil {
            fmt.Fprintf(os.Stderr, "dup3: %v\n", err)
            continue
        }
        for _, line := range strings.Split(string(data), "\n") {
            counts[line]++
        }
    }
    for line, n := range counts {
        if n > 1 {
            fmt.Println("%d\t%s\n", n, line)
        }
    }
}

func countLines(f *os.File, counts map[string]int) {
    input := bufio.NewScanner(f)
    for input.Scan() {
        counts[input.Text()]++;
    }
    // ignoring errors from input.Err()
}

func dup2() {
    counts := make(map[string]int)
    files  := os.Args[1:]
    if len(files) == 0 {
        countLines(os.Stdin, counts)
    } else {
        for _, arg := range files {
            f, err := os.Open(arg)
            if err != nil {
                fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
                continue
            }
            countLines(f, counts)
            f.Close()
        }
    }
    for line, n := range counts {
        if n > 1 {
            fmt.Println("%d\t%s\n", n, line)
        }
    }
}

func dup1() {
    counts := make(map[string]int)
    input  := bufio.NewScanner(os.Stdin)
    for input.Scan() {
        counts[input.Text()]++
    }
    for line, n:= range counts {
        if n > 1 {
            fmt.Println("%d\t%s\n", n, line)
        }
    }
}

func main() {
    //dup1()
    //dup2()
    //dup3()
    dup4()
}

