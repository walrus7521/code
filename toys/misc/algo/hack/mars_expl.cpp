#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <limits.h>

using namespace std;

int main(){
    string S;

    cin >> S;

    int num_msgs = S.size()/3;

    int altered = 0;
    for (int i = 0; i < num_msgs; i++) {
        int base = 3 * i;
        if (S[base] != 'S') {
            altered++;
        }
        if (S[base+1] != 'O') {
            altered++;
        }
        if (S[base+2] != 'S') {
            altered++;
        }
    }

    cout << altered << endl;
    return 0;
}

