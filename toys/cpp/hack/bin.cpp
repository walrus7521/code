#include <iostream>

using namespace std;  

/*
 * Given a base-10 integer, n, convert it to binary (base-2). Then find and print the 
 * base-10 integer denoting the maximum number of consecutive 1's in n's binary 
 * representation.
 *
 */

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

