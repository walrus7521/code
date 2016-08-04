#include <iostream>

using namespace std;  

/*
 * Given a base-10 integer, n, convert it to binary (base-2). Then find and print the 
 * base-10 integer denoting the maximum number of consecutive 1's in n's binary 
 * representation.
 *
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*
    *
    * Prosen Ghosh
    * American International University - Bangladesh (AIUB)
    *
*/
void to_bin() {

    int T,n;
    cin >> T;
    for(int t = 0; t < T; t++){
        cin >> n;
        int ar[33], j = 0;
        while(n != 0){
            ar[j++] = n % 2;
            n /= 2;
        }
        for(int k = j-1; k >= 0; k--)cout << ar[k];
        cout << endl;
    }
}

int main(){  
    int n, count = 0, max = 0;
    cin >> n;  
    while (n) {
        if (n & 1) {
            count++;
            if (count > max) {
                max = count;
            }
        } else {
            count = 0;
        }
        //cout << hex << n << dec << " : " << count << endl;
        n >>= 1;
    }
    cout << max << endl;
    return 0;
}  

