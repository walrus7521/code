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
};

class NotQuery : public Query_base {
};

class BinaryQuery : public Query_base {
};

class AndQuery : public BinaryQuery {
};

class OrQuery : public Query_base {
};

// interface class
class Query {

private:
    Query_base *qb;
};

int main()
{
}
