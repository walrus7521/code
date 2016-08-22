#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void angry(int n, int k, vector<int> a)
{
    int count = 0;
    for(int i = 0; i < n; i++) {
        if (a[i] <= 0) {
            count++;
        }
    }
    //cout << "count: " << count << " , k: " << k << endl;
    if (count < k) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

void jamit()
{
    int n, k;
    n = 7;
    k = 5;
    vector<int> a1 = {0,0,-1,-3,2,4};
    angry(n, k, a1);    

    n = 5;
    k = 3;
    vector<int> a2 = {-1,0,-1,1,2};
    angry(n, k, a2); 

    n = 9;
    k = 4;
    vector<int> a3 = {-2,0,-1,1,2,4,7,9,11};
    angry(n, k, a3);

    n = 6;
    k = 3;
    vector<int> a4 = {-3,-3,-2,-1,1,2};
    angry(n, k, a4);

    n = 9;
    k = 3;
    vector<int> a5 = {-1,0,1,2,4,5,7,9,11};
    angry(n, k, a5);
    return;

    n = 5;
    k = 2;
    vector<int> a6 = {0,-1,2,1,4};
    angry(n, k, a6);

    n = 5;
    k = 2;
    vector<int> a7 = {0,-1,2,1,4};
    angry(n, k, a7);

}

int main(){
    jamit();
    return 0;
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        //cout << "test case: " << a0 << endl;
        int n; // students in class
        int k; // cancelation threshold
        int count = 0;
        cin >> n >> k;
        //cout << "n students: " << n << "thresh: " << k << endl;
        vector<int> a(n);
        // vector contains arrival times
        for(int a_i = 0; a_i < n; a_i++){
           cin >> a[a_i];
        }
        angry(n, k, a);
    }
    return 0;
}

