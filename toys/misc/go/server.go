package main

import (
    "fmt"
    "log"
    "net/http"
    "sync"
    "strings"
    "strconv"
)

var mu sync.Mutex
var count int

func main() {
    http.HandleFunc("/", handler)
    http.HandleFunc("/count", counter)
    log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func coinflip() string {
    return "heads"
}

// handler echos the Path component of the requested URL.
func handler(w http.ResponseWriter, r *http.Request) {
    mu.Lock()
    count++
    mu.Unlock()
    fmt.Fprintf(w, "URL.Path = %q\n", r.URL.Path)
    fmt.Fprintf(w, "%s %s %s\n", r.Method, r.URL, r.Proto)
    for k, v := range r.Header {
        fmt.Fprintf(w, "Header[%q] = %q\n", k, v)
    }
    fmt.Fprintf(w, "Host = %q\n", r.Host)
    fmt.Fprintf(w, "RemoteAddr = %q\n", r.RemoteAddr)
    if err := r.ParseForm(); err != nil {
        log.Print(err)
    }
    for k,v := range r.Form {
        fmt.Fprintf(w, "Form[%q] = %q\n", k, v)
        // http://localhost:8000/?cycles=20
        if (k == "cycles") {
            cycles := strings.Join(v, "")
            ncycles, _ := strconv.Atoi(cycles)
            count = count + ncycles
            switch coinflip() {
                case "heads":
                    count++;
                case "tails":
                    count--;
                default:
                    fmt.Fprintf(w, "yo dawg %d\n", count);
            }
        }
    }
}

func counter(w http.ResponseWriter, r *http.Request) {
    mu.Lock()
    fmt.Fprintf(w, "Dude, you suck, count = %d\n", count)
    mu.Unlock()
}


