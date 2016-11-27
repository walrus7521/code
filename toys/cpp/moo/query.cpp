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
    WordQuery(const string &s) : query_word(s){}
    // concrete class WordQuery defines all inherited pure virtuals
    QueryResult eval(const TextQuery &t) const
        { return t.query(query_word); }
    string rep() const { return query_word; }
    string query_word;
};

// interface class
class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const string &s) : q(new WordQuery(s)) {}
    QueryResult eval(const TextQuery &t) const
    { return q->eval(t); }
    string rep() const { return q->rep(); }
private:
    Query(shared_ptr<Query_base> query) : q(query) {}
    shared_ptr<Query_base> q;
};


class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q){}
    string rep() const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery&) const;
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
        lhs(l), rhs(r), opSym(s) {}
    string rep() const { return "(" + lhs.rep() + " "
                                    + opSym + " "
                                    + rhs.rep() + ")"; }
    Query lhs, rhs;
    string opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery&) const;
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
}
