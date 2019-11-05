package main

import (
    "fmt"
    "io"
    "encoding/csv"
    //"bytes"
    "bufio"
    //"strings"
    "os"
)

func getdata() {
    scanner := bufio.NewScanner(os.Stdin)
    for scanner.Scan() {
        fmt.Println(scanner.Text())
    }

}

func get_userInput(input chan<- string) {
    for {
        var u string
        _,err := fmt.Scanf("%s", &u)
        if err != nil {
            panic(err)
        }
        input <- u
    }
}

func get_stream(input, errors chan<- string) {
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
            errors <- "eof"
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
        buf := fmt.Sprintf("[%d] =%s,%s,%s", count, row[0], row[1], row[3])
        if len(buf) == 0 {
            errors <- "no more data"
        } else {
            input <- buf
        }
    }
}

func main() {
    //getdata()
    userInput := make(chan string)
    errors := make(chan string)

    defer func() {
        close(userInput)
        close(errors)
        fmt.Println("i'm out!")
    }()

    //go get_userInput(userInput)
    go get_stream(userInput, errors)
    for {
        select {
        case e := <-errors:
            fmt.Println(e)
            return
        case x := <-userInput:
            fmt.Printf("dude %s\n", x)
            break
        }
    }
}

