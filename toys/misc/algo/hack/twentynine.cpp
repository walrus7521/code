#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int T,N,K;
    int max;
    int val;
    cin>>T;
    while(T-->0){
        cin>>N>>K;
        max = 0;
        for (int A = 1; A <= N; ++A) {
            for (int B = A+1; B <= N; ++B) {
                val = A & B;
                if (val > max && val < K) {
                    max = val;
                }
            }
        }
        cout << max << endl;
    }	
    
    return 0;
}

