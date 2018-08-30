#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int i = 4;
    double d = 4.0;
    string s = "HackerRank ";

    int j;
    double e;
    string t;
    
    cin >> j;
    cin >> e;
    cin.ignore();  //ignores an end of line character 
    getline(cin, t);

    cout << i+j << endl;
    cout << fixed << setprecision(1) << d+e << endl;
    cout << s + t << endl;

    return 0;
}

