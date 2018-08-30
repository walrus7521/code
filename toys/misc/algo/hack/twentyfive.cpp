#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool isPrime2(int number) {
    for (int i = 2; i < number; i++) {
        if (number % i == 0 && i != number) return false;
    }
    return true;
}

bool isPrime(int n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i*i <= n; i += 6) {
        if (n%i == 0 || n%(i+2) == 0) {
           return false;
        }
    }
    return true;
}

int main() {
    int T,data;
    cin>>T;
    while(T-->0){
        cin>>data;
        if (isPrime(data)) {
            cout << "Prime" << endl;
        } else {
            cout << "Not prime" << endl;
        }
    }	
    
    return 0;
}

