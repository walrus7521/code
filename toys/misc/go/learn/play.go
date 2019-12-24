package main;

import (
    "fmt"
    "container/list"
    "os"
    "io/ioutil"
    "bufio"
    "strings"
    "path/filepath"
    "hash/crc32"
    "crypto/sha1"
    "pkg/mymath"
)

func printf(str string, args ...interface{}) (int, error) {
    _, err := fmt.Printf(str, args...);
    return len(args), err;
}

func listDir() {
    filepath.Walk(".", func(path string, info os.FileInfo, err error) error {
    fmt.Println(path)
    return nil
    })
}

func testList() {
    var x list.List
    x.PushBack(1)
    x.PushBack(2)
    x.PushBack(3)
    for e := x.Front(); e != nil; e=e.Next() {
        fmt.Println(e.Value.(int))
    }
    //x.PushFront(1)
    //x.PushFront(2)
    //x.PushFront(3)
    for e := x.Back(); e != nil; e=e.Prev() {
        fmt.Println(e.Value.(int))
    }
}

func testHash() {
    // create a hasher
    h := crc32.NewIEEE()
    // write our data to it
    h.Write([]byte("test"))
    // calculate the crc32 checksum
    v := h.Sum32()
    fmt.Println(v)
}

func testSHA() {
    h := sha1.New()
    h.Write([]byte("test"))
    bs := h.Sum([]byte{})
    fmt.Println(bs)
}

func testPkg() {
    xs := []float64{1,2,3,4}
    avg := mymath.Average(xs)
    fmt.Println(avg)
}

func testCli() {
    var s, sep string
    for i := 0; i < len(os.Args); i++ {
        s += sep + os.Args[i]
        sep = "\n"
    }
    fmt.Println(s)
    for i,s := range os.Args[:] {
        fmt.Printf("%d - %s\n", i, s)
    }
    fmt.Println(strings.Join(os.Args[1:], " "))
    fmt.Println(os.Args[1:])
}

func testDupLines() {
    counts := make(map[string]int)
    input := bufio.NewScanner(os.Stdin)
    for input.Scan() {
        counts[input.Text()]++
    }
    // NOTE: ignoring potential errors from input.Err()
    for line, n := range counts {
        if n > 1 {
            fmt.Printf("%d\t%s\n", n, line)
        }
    }
}

func testCountFileLines() {
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
            fmt.Printf("%d\t%s\n", n, line)
        }
    }
}

func main() {
    testCountFileLines()
    return
    testDupLines()
    testCli()
    testPkg()
    testSHA()
    testHash()
    testList()
    listDir()
    count := 1;
    closure := func(msg string) {
        ln, err := printf("%d %s\n", count, msg);
        fmt.Printf("%d %d\n", ln, err);
        count++;
    }

    loops := 1;
    for loops > 0 {
        fmt.Printf("\nnum loops?\n");
        fmt.Scanf("%d", &loops);
        for i := 0; i < loops; i++ {
            fmt.Printf("%d ", i);
        }
    }

    closure("A Message");
    closure("Another Message");


    for {
L:
        for {
        fmt.Printf("dude: %d\n", count);
        count++;
        break L;
        }
    }
}

