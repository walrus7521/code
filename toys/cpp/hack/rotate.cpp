#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void rotate_right(vector<int>& A, int k) {
    int i, j, n = A.size();
    for (j = 0; j < k; ++j) {   
        int tmp = A[n-1];
        for (i = n-1; i > 0; --i) {
            A[i] = A[i-1];
        }
        A[0] = tmp;
    }
}

int main() {
    int n, q, k, idx;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    rotate_right(a, k);
    for (int i = 0; i < q; ++i) {
        cin >> idx;
        cout << a[idx] << endl;
    }
    return 0;
}

