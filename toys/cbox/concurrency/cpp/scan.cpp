#include "perlish.hpp"

vector<string> lines;

void line_regexes()
{
    regex integers {R"(\d+)*(\w+)"};
    regex floats {R"(\d+\.\d+)*(\w+)"};
    int lineno = 0;
    for (string line; getline(cin, line);) {
        ++lineno;
        smatch matches;
        if (regex_search(line, matches, floats)) {
            for (auto m : matches) {
                string::size_type sz;
                //int num = stoi(m, nullptr, 10);
                //cout << m << ":" << num << endl;
                float fnum = stof(m, &sz);
                cout << m << ":" << fnum << endl;
            }
        }
    }

}

void line_scanner()
{
    string line;
    vector<string> tokens;
    while (getline(cin, line)) {
        lines.push_back(line);
        tokens = split(line, ",");
        for (auto x : tokens) {
            //cout << x << endl;
        }
    }
    
    // dump lines
    cout << "dump lines:\n";
    for (auto l : lines) {
        cout << l << endl;
    }
}

int main()
{
    //line_regexes();
    line_scanner();
}

