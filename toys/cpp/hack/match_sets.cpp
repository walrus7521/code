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

int test()
{
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
    if (first == -1 || second == -1) {
        cout << -1 << endl;
        return 0;
    }

    // test if decrement first and increment second will solve it
    // if not, print -1
    if ((x[first] < y[first]) || (x[second] > y[second])) {
        cout << "bail here 1" << endl;
        cout << -1 << endl;
        return 0;
    }

    int max_iter = x[first] - y[first];
    cout << "iter: " << max_iter << endl;
    // apply the mismatch indexes
    //
    count = 0;
    for (int i = 0; i < max_iter; ++i) {
        x[first]--;
        x[second]++;
    }

    if (x == y) {
        cout << max_iter << endl;
    } else {
        cout << "bail here 2" << endl;
        cout << -1 << endl;
        return 0;
    }

    show(x);
    show(y);

    return 0;

}

int main() {
    //test();
    //return 0;

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
    if (count > 2) {
        cout << -1 << endl;
        return 0;
    }
    if (first == -1 || second == -1) {
        cout << -1 << endl;
        return 0;
    }

    // test if decrement first and increment second will solve it
    // if not, print -1
    if ((x[first] < y[first]) || (x[second] > y[second])) {
        cout << -1 << endl;
        return 0;
    }

    int max_iter = x[first] - y[first];
    // apply the mismatch indexes
    //
    count = 0;
    for (int i = 0; i < max_iter; ++i) {
        x[first]--;
        x[second]++;
    }

    if (x == y) {
        cout << max_iter << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;

}


