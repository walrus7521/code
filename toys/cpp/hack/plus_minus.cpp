#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;


int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int arr_i = 0;arr_i < n;arr_i++){
       cin >> arr[arr_i];
    }
    int pos=0, neg=0, zero=0;
    for(int i = 0; i < n; i++){
        if (arr[i] > 0) {
            pos++;
        } else
        if (arr[i] < 0) {
            neg++;
        } else
        if (arr[i] == 0) {
            zero++;
        }
    }
    double pos_frac, neg_frac, zero_frac;
    pos_frac  = ((double) 1.0 * pos) / ((double) 1.0 * n);
    neg_frac  = ((double) 1.0 * neg) / ((double) 1.0 * n);
    zero_frac = ((double) 1.0 * zero) / ((double) 1.0 * n);

    cout << setiosflags(ios::fixed) << std::setprecision(6) << pos_frac << endl;
    cout << setiosflags(ios::fixed) << std::setprecision(6) << neg_frac << endl;
    cout << setiosflags(ios::fixed) << std::setprecision(6) << zero_frac << endl;

    return 0;
}

