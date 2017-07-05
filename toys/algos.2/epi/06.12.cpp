#include <iostream>
#include <vector>

using namespace std;

/*
   Enumerate all primes to n

   A natural number is a prime if it is bigger than 1 and has no
   divisors other than 1 and itself.

   Write a function that takes a single positive integer argument n
   (n >= 2) and return all primes between 1 and n.

 */

bool isPrime(int number) {
    for (int i = 2; i < number; i++) {
        if (number % i == 0 && i != number) return false;
    }
    return true;
}

vector<int> AllPrimes(int n) {
    vector<int> primes;
    if (n < 2) return primes;
    for (int i = 2; i <= n; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main()
{
    int n= 123;
    vector<int> primes = AllPrimes(n);
    for (auto& i : primes) {
        cout << i << endl;
    }
}

