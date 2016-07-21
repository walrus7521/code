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

vector<int> AllPrimes(int n)
{
    vector<int> primes;
    primes.push_back(2);
    primes.push_back(3);
    return primes;
}

int main()
{
    int n;
    vector<int> primes = AllPrimes(n);
    for (auto& i : primes) {
        cout << i << endl;
    }
}
