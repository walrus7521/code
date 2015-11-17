#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

vector<string> split(string line)
{
    vector<string> vs;
    return vs;
}

int main()
{
    int longest = 0, shortest = 99999;
    string word;
    string::size_type sz;
    map<string, int> ms;
    while (cin >> word) {
        sz = word.size();
        if (sz > longest) longest = sz;
        if (sz < shortest) shortest = sz;
        ms[word]++;
    }
    for (map<string,int>::const_iterator i = ms.begin(); i != ms.end(); ++i) {
        cout << i->first << " " << i->second << endl;
    }
    cout << "longest " << longest << ", shortest : " << shortest << endl;

    return 0;
}
