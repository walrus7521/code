#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    int n, number=77;
    string line;
    map<string, string> dict;
    cin >> n;
    cin.ignore();  //ignores an end of line character 
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        istringstream iss(line);
        string name, number;
        iss >> name;
        iss >> number;
        dict[name] = number;
    }
    string query;
    while (getline(cin, query)) {
        if (query == "") break;
        string num = dict[query];
        if (num.size() > 0) {
            cout << query << "=" << num << endl;
        } else {
            cout << "Not found" << endl;
        }
    }

    return 0;
}

