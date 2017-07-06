#include <iostream>

using namespace std;


int main(){
    int n; // guests
    int m; // cookies
    cin >> n >> m;
    if (m < n) {
        cout << n - m << endl;
    } else 
    if (m == n) {
        cout << 0 << endl;
    } else 
    if ((m > n) && (m%n==0)) {
        cout << 0 << endl;
    } else { // m > n 
        int rm = m % n;
        int dv = m / n;
        cout << n - rm << endl;
    }
    
    return 0;
}

