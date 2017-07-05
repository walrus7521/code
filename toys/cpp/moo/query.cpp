#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <memory>

using namespace std;

// utilities
string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr > 1) ? word + ending : word;
}

class QueryResult {
friend class TextQuery;
friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(string s, 
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f) :
        sought(s), lines(p), file(f) {}

    auto begin() { 
        cout << "begin()" << endl;
        return lines->begin(); 
    }
    auto end() {
        cout << "end()" << endl;
        return lines->end();
    }
    shared_ptr<vector<string>> get_file() { 
        return file; 
    }

private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};


class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;

    TextQuery(ifstream& is) :
        file(new vector<string>)
    {
        string text;
        while (getline(is, text)) {
            file->push_back(text);
            int n = file->size()-1;
            istringstream line(text);
            string word;
            while (line >> word) {
                // if word is not already in wm, add it
                auto &lines = wm[word];
                if (!lines) {
                    lines.reset(new set<line_no>);
                }
                lines->insert(n);
            }
        }
    }

    QueryResult query(string sought) const { 
        static shared_ptr<set<line_no>> nodata(new set<line_no>);
        auto loc = wm.find(sought);
        if (loc == wm.end()) {
            return QueryResult(sought, nodata, file);
        } else {
            return QueryResult(sought, loc->second, file);
        }
    }

    ostream& print(ostream& os, const QueryResult &qr) {
        os << qr.sought << " occurs " << qr.lines->size() << " "
           << make_plural(qr.lines->size(), "time", "s") << endl;
        // print out each line in which the word appeared
        for (auto num: *qr.lines) {
            os << "\t(line " << num+1 << ") "
               << *(qr.file->begin() + num) << endl;
        }
        return os; 
    }

    void show2() {
        string first = wm.begin()->first;
        cout << "start iter at: " << first << endl;
        auto loc = wm.find(first);
        if (loc != wm.end()) {
            QueryResult qr = QueryResult(first, loc->second, file);
            for (auto& x : qr) {
                cout << "qr: " << x+1 << endl;
            }
        }
    }

    void show_all() {
       for (auto& x : wm) {
            cout << x.first << " : ";
            for (auto vi = x.second->begin(); 
                      vi != x.second->end(); ++vi) {
                cout << *vi << ", ";
            }
            cout << endl;
       }
    }




private:
    std::shared_ptr<std::vector<std::string>> file; // input file
    // map of each word to the set of the lines in which the word appears
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no; // used in the eval functions
    virtual ~Query_base() = default;
private:
    // eval returns the QueryResult that matches this Query
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep is a string representation of the query
    virtual std::string rep() const = 0;
};


class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const string &s) : query_word(s){
        cout << "WordQuery const" << endl;
    }
    // concrete class WordQuery defines all inherited pure virtuals
    QueryResult eval(const TextQuery &t) const { 
        cout << "WordQuery eval" << endl;
        return t.query(query_word); 
    }
    string rep() const { return query_word; }
    string query_word;
};

// interface class
class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const string &s) : q(new WordQuery(s)) {
        cout << "Query const" << endl;
    }
    QueryResult eval(const TextQuery &t) const
    { 
        cout << "Query eval" << endl;
        return q->eval(t); 
    }
    string rep() const { return q->rep(); }
private:
    Query(shared_ptr<Query_base> query) : q(query) {}
    shared_ptr<Query_base> q;
};


class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q){
        cout << "NotQuery const" << endl;
    }
    string rep() const { return "~(" + query.rep() + ")"; }
    // returns the lines not in its operands result set
    QueryResult eval(const TextQuery& text) const {
        cout << "NotQuery eval" << endl;
        // virtual call to eval through the Query operand
        auto result = query.eval(text);
        // start out with empty result set
        auto ret_lines = make_shared<set<line_no>>();
        // iterate through lines on which operand appears
        auto beg = result.begin(), end = result.end();
        // for each line, if result is not in the line
        // add that line to ret_lines
        auto sz = result.get_file()->size();
        for (size_t n = 0; n != sz; ++n) {
            // if we haven't processed all the lines in result
            // check whether this line is present
            if (beg == end || *beg != n) {
                ret_lines->insert(n);
            } else
            if (beg != end) {
                ++beg;
            }
        }
        return QueryResult(rep(), ret_lines, result.get_file());
    }
    Query query;
};
inline Query operator~(const Query &operand)
{
    return shared_ptr<Query_base>(new NotQuery(operand));
}

// abstract base class
class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, string s) :
        lhs(l), rhs(r), opSym(s) {
            cout << "BinaryQuery const" << endl;
        }
    string rep() const { return "(" + lhs.rep() + " "
                                    + opSym + " "
                                    + rhs.rep() + ")"; }
    Query lhs, rhs;
    string opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "&") {
            cout << "AndQuery const" << endl;
        }
    QueryResult eval(const TextQuery& text) const {
        cout << "AndQuery eval" << endl;
        // virtual calls through Query operands to get 
        // results for sets
        auto left = lhs.eval(text), right = rhs.eval(text);
        // set to hold the intersection of left and right
        auto ret_lines = make_shared<set<line_no>>();
        // writes intersection of two ranges to a destination
        // iterator, dest iter in this call adds elements to ret
        set_intersection(left.begin(), left.end(),
                         right.begin(), right.end(),
                         inserter(*ret_lines, ret_lines->begin()));
        return QueryResult(rep(), ret_lines, left.get_file());
    }
};
inline Query operator&(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "|") {
            cout << "OrQuery const" << endl;
        }
    // returns the union of its operands' result sets
    QueryResult eval(const TextQuery& text) const {
        cout << "OrQuery eval" << endl;
        // virtual calls through the Query members, lhs and rhs
        // the calls to eval return the QueryResult for each operand
        auto right = rhs.eval(text), left = lhs.eval(text);

        // copy the line numbers from left operand into result set
        auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
        // insert lines from right operand
        ret_lines->insert(right.begin(), right.end());
        // return new QueryResult of union of lhs and rhs
        return QueryResult(rep(), ret_lines, left.get_file());
    }
};
inline Query operator|(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

ostream& operator<<(ostream &os, const Query &query)
{
    // Query::rep makes a virtual call through its Query_base
    // pointer to rep()
    return os << query.rep();
}

int main()
{
    ifstream input("story");
    TextQuery tq(input);
    //tq.show_all();
    //tq.show2();
    cin.clear();
    cin.sync();
#if 0
    while (true) {
        cout << "Enter word to search: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        cout << "you entered: " << s << endl;
        tq.print(cout, tq.query(s)) << endl;
    }
#endif
    string w1 = "fiery";
    Query qw1(w1);
    string w2 = "bird";
    Query qw2(w2);
    //cout << qw1.rep() << endl;
    //QueryResult qr1 = qw1.eval(tq);
    //tq.print(cout, qr1);

#if 0
    Query qor = qw1 | qw2;
    cout << qor.rep() << endl;
    QueryResult qr2 = qor.eval(tq);
    tq.print(cout, qr2);
#endif

    Query qand = qw1 & qw2;
    cout << qand.rep() << endl;
    QueryResult qr3 = qand.eval(tq);
    tq.print(cout, qr3);

}
