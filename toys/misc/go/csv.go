package main;

import (
    "encoding/csv"
    "fmt"
    "os"
    "io"
)

func main() {
    var one   []string
    var two   []string
    var three []string
    var count int = 0
    for _, filename := range os.Args[1:] {
        f, err := os.Open(filename)
        if err != nil {
            fmt.Fprintf(os.Stderr, "csv: %v\n", err);
            continue
        }
        defer f.Close()
        csvr := csv.NewReader(f)
        csvr.Comma = ','
        csvr.Comment = '#'
        for {
            row, err := csvr.Read()
            if err != nil {
                if err == io.EOF {
                    err = nil
                }
                break
            }
            //fmt.Println(len(row))
            //fmt.Println(row)
            //for _, x := range row {
            //    fmt.Printf("=> %s\n", x)
            //}
            count++
            one   = append(one,   row[0])
            two   = append(two,   row[1])
            three = append(three, row[2])
        }
    }

    fmt.Println(count)
    for i := 0; i < count; i++ {
        fmt.Printf("[%d] =%s,%s,%s\n", i, one[i], two[i], three[i])
    }
}


