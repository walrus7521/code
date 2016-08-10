#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
    }
    for(int i = 0; i < n; i++){
        cin >> y[i];
    }

    if (x == y) {
        cout << "x and y are equal" << endl;
    } else {
        cout << "x and y are not equal" << endl;
    }

    show(x);
    show(y);

    //std::sort (x.begin(), x.end());
    //std::sort (y.begin(), y.end());

    if (x == y) {
        cout << 0 << endl;
        return 0;
    }

    int first = -1;
    int second = -1;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (x[i] != y[i]) {
            count++;
            if (first == -1) {
                first = i;
            } else
            if (second == -1) {
                second = i;
            }
        }
    }
    cout << "there were: " << count << " mismatches" << endl;
    if (count > 2) {
        cout << -1 << endl;
        return 0;
    }
    cout << "mismatches: " << first << " " << second << endl;

    // apply the mismatch indexes

    for (int i = 0; i < n; ++i) {
        if (x[i] < y[i]) {
            x[i]++;
        } else
        if (x[i] > y[i]) {
            x[i]--;
        }
    }

    if (x == y) {
        cout << "x and y are equal" << endl;
    } else {
        cout << "x and y are not equal" << endl;
    }

    show(x);
    show(y);
     
    return 0;
}


