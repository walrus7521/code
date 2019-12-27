package main;

import (
    "encoding/csv"
    "fmt"
    "os"
    "io"
)

func get_csv() {
    var one   []string
    var two   []string
    var three []string
    var count int = 0

    csvr := csv.NewReader(os.Stdin)
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
        fmt.Printf("[%d] =%s,%s,%s\n", count, row[0], row[1], row[3])
    }

}

func main() {
    go get_csv()
}
