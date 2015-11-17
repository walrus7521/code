#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;

        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;

        if (i != j) {
            ret.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return ret;
}

void show(const vector<string> w)
{
    vector<string>::const_iterator vs = w.begin();
    while (vs != w.end()) {
        cout << *vs << endl;
        ++vs;
    }
}

int main()
{
    vector<string> words;
    string s;
    while (getline(cin, s)) {
        words = split(s);
        show(words);
    }

    return 0;
}
