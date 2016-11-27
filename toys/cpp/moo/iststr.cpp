#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class QueryResult {
friend class TextQuery;
};

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

int main()
{
    ifstream input("data");
    TextQuery tq(input);
    tq.show();
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

