// http://thenewstack.io/make-a-restful-json-api-go/

// http://localhost:8080/dude

package main

import (
    "fmt"
    "html"
    "log"
    "net/http"
)

func main() {
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "Sup Hello, %q", html.EscapeString(r.URL.Path))
        fmt.Printf("Hello, %q\n", html.EscapeString(r.URL.Path))
    })

    log.Fatal(http.ListenAndServe(":8080", nil))

}
