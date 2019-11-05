package main

import (
    "fmt"
    "net/http"
    "github.com/gorilla/mux"
)

// https://gowebexamples.com/routes-using-gorilla-mux/
// https://www.sohamkamani.com/blog/2017/09/13/how-to-build-a-web-application-in-golang/
// http://127.0.0.1/api?species="bird"&type=42&age=34.5
// https://stackoverflow.com/questions/38032635/pass-multiple-parameters-to-rest-api-spring/38032778

func Handler (w http.ResponseWriter, r *http.Request) {
    err := r.ParseForm()
    if err != nil {
        fmt.Println(err)
    }

    species :=  r.Form.Get("species")
    stype :=  r.Form.Get("type")
    age :=  r.Form.Get("age")
    //z := r.FormValue("species")
    //a := r.FormValue("type")
    fmt.Println("species: ", species)
    fmt.Println("type   : ", stype)
    fmt.Println("age    : ", age)
    //vars := mux.Vars(r)
    //for v := range(vars) {
    //    fmt.Println("vars: ", v)
    //}
    fmt.Fprintf(w, "You've requested the species: %s type %s age %s\n", species, stype, age)
    fmt.Fprintf(w, "now go home\n")
}

func main() {
    r := mux.NewRouter()
    r.HandleFunc("/api", Handler)
    http.ListenAndServe(":80", r)

    //fs := http.FileServer(http.Dir("static"))
    //http.Handle("/static/", http.StripPrefix("/static/", fs))
    //http.Handle("/", fs)

    //http.ListenAndServe(":80", nil)
}

