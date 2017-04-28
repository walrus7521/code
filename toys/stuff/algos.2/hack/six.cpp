#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int T;
	string S;
    cin >> T;
    if (T >= 1 && T <= 10) {
        for(int i=0; i < T; i++) {
        	cin >> S;
            int N = S.length();
            if (N >= 2 && N <= 10000) {
                for(int j=0; j < N; j++) {
                    if (j % 2 == 0) {
                        cout << S[j];
                    }
                }
                cout << " ";
                for(int j=0; j < N; j++) {
                    if (j % 2 != 0) {
                        cout << S[j];
                    }
                }
                cout << endl;
            }
        }
    }

    return 0;
}

