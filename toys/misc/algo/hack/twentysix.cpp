#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int Da, Ma, Ya;
    int De, Me, Ye;
    int fine = 0;

    cin >> Da >> Ma >> Ya;
    cin >> De >> Me >> Ye;

    if (Ya < Ye) {
        cout << fine << endl;
        return 0;
    }

    // on or before
    if ((Ya <= Ye) &&
        (Ma <= Me) &&
        (Da <= De)) {
        fine = 0;
        cout << fine << endl;
        return 0;
    }

    if (Ya <= Ye) {
        if (Ma <= Me) {
            if (Da > De) {
                fine = (Da - De) * 15;
            }
        } else  {
            fine = 500 * (Ma - Me);
        }
    } else {
        fine = 10000;
    }
    cout << fine << endl;

    return 0;
}


