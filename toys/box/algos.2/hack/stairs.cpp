#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string stair(i, '#');
        string space(n-i, ' ');
        cout << space+stair << endl;
    }
    return 0;
}

