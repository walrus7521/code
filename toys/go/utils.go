// https://golang.org/doc/install
// http://thenewstack.io/make-a-restful-json-api-go/
// http://stackoverflow.com/questions/33164564/golang-parse-post-request
// $ go get github.com/justinas/alice
// $ go get github.com/gorilla/mux
// $ go get github.com/gorilla/context
// $ go get github.com/rs/cors
// $ go get github.com/callum-ramage/jsonconfig
// curl -i -X GET http://localhost:8080/items/godaddy=0xdeadbeef
// http://www.gorillatoolkit.org/
// $ GOPATH=~/src/services/browse/go
// $ go get github.com/gorilla/mux
//
// build process:
// $ go install github.com/walrus7521/utils
// $ $GOPATH/bin/utils 
//
//http://stackoverflow.com/questions/11353679/whats-the-recommended-way-to-connect-to-mysql-from-go


package main

import (
    "fmt"
    htmlTemplate "html/template"
    textTemplate "text/template"
    "log"
    "time"
    "net/http"
    //"github.com/callum-ramage/jsonconfig"
    "github.com/gorilla/context"
    "github.com/gorilla/mux"
    //"github.com/justinas/alice"
    //"github.com/rs/cors"
    //"database/sql"
    _ "github.com/go-sql-driver/mysql"
	"github.com/jmoiron/sqlx"
)

//var config, err = jsonconfig.LoadAbstract("./config.conf", "")

var noticeTextTemplate *textTemplate.Template
var noticeHTMLTemplate *htmlTemplate.Template
var indexHTMLTemplate *htmlTemplate.Template
var headerHTMLTemplate *htmlTemplate.Template
var footerHTMLTemplate *htmlTemplate.Template

func recoverHandler(next http.Handler) http.Handler {
	fn := func(w http.ResponseWriter, r *http.Request) {
		defer func() {
			if err := recover(); err != nil {
				log.Printf("panic: %+v", err)
				http.Error(w, http.StatusText(500), 500)
			}
		}()

		next.ServeHTTP(w, r)
	}

	return http.HandlerFunc(fn)
}

func loggingHandler(next http.Handler) http.Handler {
	fn := func(w http.ResponseWriter, r *http.Request) {
		t1 := time.Now()
		next.ServeHTTP(w, r)
		t2 := time.Now()
		log.Printf("[%s] %q %v\n", r.Method, r.URL.String(), t2.Sub(t1))
	}

	return http.HandlerFunc(fn)
}

func indexHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Welcome!")
}

func extractVars(next http.Handler) http.Handler {
	fn := func(w http.ResponseWriter, r *http.Request) {
		context.Set(r, "vars", mux.Vars(r))
		next.ServeHTTP(w, r)
	}

	return http.HandlerFunc(fn)
}


type router struct {
	*mux.Router
}

func (r *router) Get(path string, handler http.Handler) {
	r.Handle(path, handler).Methods("GET")
}

func (r *router) Post(path string, handler http.Handler) {
	r.Handle(path, handler).Methods("POST")
}

func NewRouter() *router {
	return &router{mux.NewRouter()}
}

var (
	user      string
	pass      string
	prot      string
	addr      string
	dbname    string
	dsn       string
	netAddr   string
	available bool
)

//type store struct {
//    string user
//    string pass
//    string db
//    string host
//}

type License struct {
    Key string
    Date string
    email string
}

func main() {
	//var err error

	//noticeTextTemplate, err = textTemplate.ParseFiles("notice.txt.tmpl")
	//noticeHTMLTemplate = htmlTemplate.Must(htmlTemplate.ParseFiles("notice.html.tmpl", "header.html.tmpl", "footer.html.tmpl"))
	//indexHTMLTemplate = htmlTemplate.Must(htmlTemplate.ParseFiles("index.html.tmpl", "header.html.tmpl", "footer.html.tmpl"))
	//headerHTMLTemplate, err = htmlTemplate.ParseFiles("header.html.tmpl")
	//footerHTMLTemplate, err = htmlTemplate.ParseFiles("footer.html.tmpl")

	//tmpl := make(map[string]*htmlTemplate.Template)
	//tmpl["index.html"] = indexHTMLTemplate
	//tmpl["notice.html"] = noticeHTMLTemplate

	//if err != nil {
	//	log.Fatal(err)
	//}

	//c := cors.New(cors.Options{
	//	AllowedOrigins: []string{"*"},
	//})
    //commonHandlers := alice.New(context.ClearHandler, c.Handler, loggingHandler, recoverHandler, extractVars)

    //var s store
    //s.user=""
    //s.pass=""
    //s.db=""
    //s.host=""

    // driver_test.go:	db, err := sql.Open("mysql", fmt.Sprintf("%s:%s@mydial(%s)/%s?timeout=30s&strict=true", user, pass, addr, dbname))
    //con, err := sql.Open("mysql", s.user+":"+s.pass+"@/"+s.host+"/"s.db)
    if err != nil {
        fmt.Printf("Failed to open database: %s", err)
    }

    rows, err := db.Queryx("SELECT licenseKey, email, company, price FROM License")
    if err != nil {
       fmt.Printf("Failed to query rows")
    }

    license := License{}
    for rows.Next() {
        err := rows.StructScan(&license)
        if err != nil {
            fmt.Printf("error structScan\n")
        }
        fmt.Printf("%#v\n", license)
    }

    defer db.Close()


    router := NewRouter()

    router.Router.PathPrefix("/content/").Handler(http.FileServer(http.Dir("./static/")))

    getLicenses             := http.HandlerFunc(searchLicenses)
    postLicenses            := http.HandlerFunc(putLicense)
    postDailyLicenseCount   := http.HandlerFunc(updateDailyLicenseCount)
    postMonthlyLicenseCount := http.HandlerFunc(updateMonthlyLicenseCount)
    getDailyLicenseCount    := http.HandlerFunc(getDailyLicenseCount)
    getMonthlyLicenseCount  := http.HandlerFunc(getMonthlyLicenseCount)
    getExpiring             := http.HandlerFunc(getExpiring)
    getInvoice              := http.HandlerFunc(getInvoice)
    postTrials              := http.HandlerFunc(createTrial)
    getTrials               := http.HandlerFunc(getTrials)
    postTrial               := http.HandlerFunc(updateTrial)
    getCustomerEmail        := http.HandlerFunc(searchCustomerEmail)
    getCustomerCompany      := http.HandlerFunc(searchCustomerCompany)

    router.Get( "/licenses",                    getLicenses)
    router.Post("/licenses",                    postLicenses)

    router.Post("/licenses/softlayer/daily",    postDailyLicenseCount)
    router.Post("/licenses/softlayer/monthly",  postMonthlyLicenseCount)

    router.Get( "/licenses/dailyCounts",        getDailyLicenseCount)
    router.Get( "/licenses/monthlyCounts",      getMonthlyLicenseCount)

    router.Get( "/licenses/expiration",         getExpiring)

    router.Get( "/licenses/invoice",            getInvoice)
    router.Get( "/trials",                      getTrials)
    router.Post("/trials",                      postTrials)

    router.Post("/trials/:id",                  postTrial)
    router.Get( "/customers/emails",            getCustomerEmail)
    router.Get( "/customers/companies",         getCustomerCompany)


    log.Fatal(http.ListenAndServe(":8080", router))

}

func HomeHandlerGet(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "Home Get!")
}
func HomeHandlerPost(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "Home Post!")
}
func searchLicenses(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "searchLicenses!")
}
func putLicense(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "putLicense!")
}
func updateDailyLicenseCount(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "updateDailyLicenseCount!")
}
func updateMonthlyLicenseCount(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "updateMonthlyLicenseCount!")
}
func getDailyLicenseCount(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "getDailyLicenseCount!")
}
func getMonthlyLicenseCount(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "getMonthlyLicenseCount!")
}
func getExpiring(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "getExpiring!")
}
func getInvoice(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "getInvoice!")
}
func createTrial(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "createTrial!")
}
func getTrials(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "getTrials!")
}
func updateTrial(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "updateTrial!")
}
func searchCustomerEmail(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "searchCustomerEmail!")
}
func searchCustomerCompany(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintln(w, "searchCustomerCompany!")
}


