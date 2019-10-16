package main

import (
    "fmt"
    "time"
    "math/rand"
    "io/ioutil"
    "net/http"
)

func f(n int) {
    for i := 0; i < 10; i++ {
        fmt.Println(n, ":", i)
        amt := time.Duration(rand.Intn(250))
        time.Sleep(time.Millisecond * amt)
    }
}

func testGoroutines() {
    for i := 0; i < 10; i++ {
        go f(i)
    }
    var input string
    fmt.Scanln(&input)
}

func pinger(c chan<- string) {
    for i := 0; ; i++ {
        c <- "ping"
    }
}

func ponger(c chan<- string) {
    for i := 0; ; i++ {
        c <- "pong"
    }
}

func printer(c <-chan string) {
    for {
        msg := "dude: " + <- c
        fmt.Println(msg)
        time.Sleep(time.Second * 1)
    }
}

func testChannels() {
    var c chan string = make(chan string)
    go pinger(c)
    go ponger(c)
    go printer(c)
    var input string
    fmt.Scanln(&input)
}

func testSelect() {

    c1 := make(chan string)
    c2 := make(chan string)

    go func() {
        for {
            c1 <- "from 1"
            time.Sleep(time.Second * 2)
        }
    }()

    go func() {
        for {
            c2 <- "from 2"
            time.Sleep(time.Second * 3)
        }
    }()

    go func() {
        for {
            select {
            case msg1 := <- c1:
                fmt.Println(msg1)
            case msg2 := <- c2:
                fmt.Println(msg2)
            case <- time.After(time.Second):
                fmt.Println("timeout")
            default:
                fmt.Println("nothing ready")
            }
        }
    }()
    var input string
    fmt.Scanln(&input)
}

func testSelectAsyncBufferedChannels() {

    var capacity = 3
    c1 := make(chan string, capacity)
    c2 := make(chan string)

    go func() {
        for {
            c1 <- "from 1"
            time.Sleep(time.Second * 2)
        }
    }()

    go func() {
        for {
            c2 <- "from 2"
            time.Sleep(time.Second * 3)
        }
    }()

    go func() {
        for {
            select {
            case msg1 := <- c1:
                fmt.Println(msg1)
            case msg2 := <- c2:
                fmt.Println(msg2)
            case <- time.After(time.Second):
                fmt.Println("timeout")
            //default:
            //    fmt.Println("nothing ready")
            }
        }
    }()
    var input string
    fmt.Scanln(&input)
}


type HomePageSize struct {
    URL string
    Size int
}

func testWebScrape() {
    urls := []string{
        "http://www.apple.com",
        "http://www.amazon.com",
        "http://www.google.com",
        "http://www.microsoft.com",
    }

    results := make(chan HomePageSize)

    for _, url := range urls {
        go func(url string) {
            res, err := http.Get(url)
            if err != nil {
                panic(err)
            }
            defer res.Body.Close()
            bs, err := ioutil.ReadAll(res.Body)
            if err != nil {
                panic(err)
            }
            results <- HomePageSize{
                URL: url,
                Size: len(bs),
            }
        }(url) // <- this last parameter is the function call itself
               // on the closure
    }

    var biggest HomePageSize
    for range urls {
        result := <-results
        if result.Size > biggest.Size {
            biggest = result
        }
    }
    fmt.Println("The biggest home page:", biggest.URL)
}


func main() {
    testWebScrape()
    //testSelect()
    //testSelectAsyncBufferedChannels()
    //testGoroutines()
    //testChannels()
}


