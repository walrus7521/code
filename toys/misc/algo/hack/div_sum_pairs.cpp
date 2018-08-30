#include <vector>
#include <iostream>

using namespace std;


int main(){
    int n;
    int k;

    cin >> n >> k;

    vector<int> a(n);

    for (int a_i = 0; a_i < n; a_i++) {
       cin >> a[a_i];
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; ++j) {
            int sum = a[i] + a[j];
            if (sum % k == 0) {
                count++;
                //cout << "(" << i << "," << j << ")" << endl;
            }
        }
    }
    cout << count << endl;


    return 0;
}

