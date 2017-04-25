#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// You always need at most one cut. The sticks can be used to form a polygon as long as 
// there's no stick that's as long as all the others put together. If originally there 
// is such a stick, just cut it in half.

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int a_i = 0;a_i < n;a_i++){
        cin >> a[a_i];
    }
    int max_idx = 0;
    int max_len = 0;
    int sum = 0;
    for(int i = 0; i < n; ++i){
        sum += a[i];
        if (a[i] > max_len) {
            max_len = a[i];
            max_idx = i;
        }
    }
    sum -= a[max_idx];
    //cout << "max: " << a[max_idx] << " sum: " << sum << endl;
    int cuts = 0;
    if (max_len >= sum) {
        cuts++;
    }
    cout << cuts << endl;

    return 0;
}

