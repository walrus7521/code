#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string s) {
    int i = 0;
    vector<string> vs;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i])) {
            ++i;
        }
        int j = i;
        while (j != s.size() && !isspace(s[j])) {
            ++j;
        }
        if (i != j) {
            vs.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return vs;
}

void reverse(string s) {
    vector<string> vs = split(s);
    string rev;
    for (vector<string>::reverse_iterator it = vs.rbegin();
            it != vs.rend(); ++it) {
        cout << *it << endl;
        rev += *it;
        rev += " ";
    }
    cout << "reversed:: " << rev << endl;    
}

int main()
{
    string s = "hello my name is bart\0";
    reverse(s);
}
