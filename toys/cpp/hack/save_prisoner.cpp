#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int N; // num prisoners
    int M; // num of sweets
    int S; // start prisoner
    int T; // num cases

    cin >> T;

    for(int i = 0; i < T; ++i){

        cin >> N >> M >> S; 

        int x = (M + S - 1) % N;

        if (x == 0) {
            cout << N << endl;
        } else {
            cout << x << endl;
        }
    }

    return 0;
}
