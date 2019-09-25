package main;

import (
    "fmt"
)

func printf(str string, args ...interface{}) (int, error) {
    _, err := fmt.Printf(str, args...);
    return len(args), err;
}

func main() {
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

