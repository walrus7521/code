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
    int cost = 0;

    cin >> Da >> Ma >> Ya;
    cin >> De >> Me >> Ye;

    if (Ya == Ye) {
        if (Ma == Me) {
            if (Da == De) {
                cost = 0;
            } else
            if (Da > De) {
                cost = (Da - De) * 15;
            } else {
                cost = 0;
            }
        } else
        if (Ma > Me) {
        } else {
        }
    } else
    if (Ya > Ye) {
    } else {
        cost = 0;
    }
    cout << cost << endl;

    return 0;
}


