#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string s) {
    int i = 0, j;
    vector<string> vs;
    while (true) {
        while (!isalpha(s[i])) {
            i++;
        }
        j = i;
        while (isalpha(s[j])) {
            j++;
        }
        vs.push_back(s.substr(i, j));
    }
    return vs;
}

void reverse(string s) {
}

int main()
{
    string s = "hello, my name is bart";
    vector<string> vs = split(s);
    for (vector<string>::const_iterator it = vs.begin();
            it != vs.end(); ++it) {
        cout << *it << endl;
    }
}
