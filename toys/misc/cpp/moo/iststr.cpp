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

    shared_ptr<vector<string>> get_file() { return file; }
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};

#if 0
class TextQuery {
public:
    TextQuery() {}
    TextQuery(ifstream& in) {
        string line, word;
        int lineno = 0;
        cout << "okay let's get the data\n";
        while (getline(in, line)) {
            file.push_back(line);
            istringstream words(line);
            while (words >> word) {
                map_strs[word].insert(lineno);
            }
            ++lineno;
        }
        
    }

    ostream& print(ostream& out, const set<int> &qs) {
        for (set<int>::iterator si = qs.begin(); 
                si != qs.end(); ++si) {
                cout << *si << ", ";
        }
        return out;
    }

    set<int>& query(string s) {
        auto& qs = map_strs[s];
        return qs;
    }

    void show() {
       for (auto& x : map_strs) {
            cout << x.first << " : ";
            for (set<int>::iterator vi = x.second.begin(); 
                        vi != x.second.end(); ++vi) {
                cout << *vi << ", ";
            }
            cout << endl;
        }
    }

private:
    vector<string> file;
    map<string, set<int>> map_strs;
};
#endif

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
            QueryResult qr = QueryResult(sought, nodata, file);
            return qr;
        } else {
            QueryResult qr = QueryResult(sought, loc->second, file);
            return qr;
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
    shared_ptr<vector<string>> file; // input file
    // map of each word to the set of the lines in which the word appears
    map<string, shared_ptr<set<line_no>>> wm;
};



int main()
{
    ifstream input("story");
    TextQuery tq(input);
    tq.show_all();
    tq.show2();
    cin.clear();
    cin.sync();
    while (true) {
        cout << "Enter word to search: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        cout << "you entered: " << s << endl;
        tq.print(cout, tq.query(s)) << endl;
    }
   return 0;
}

