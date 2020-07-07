#include <cstdio>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

bool all_diff(int m, int n)
{
    int numerator = m;
    int denominator = n;
    set<int> num;
    set<int> den;
    vector<int> intersection;

    for (int i = 0; i < 5; i++) {
        num.insert(m % 10);            
        m /= 10;
        den.insert(n % 10);            
        n /= 10;
    }
    
    // if both sets have 5 items
    if (num.size() < 5 || den.size() < 5) {
        return false;
    }

    set_intersection(num.begin(), num.end(), den.begin(), den.end(), 
            std::inserter(intersection, intersection.begin()));
    // if sets are unique return true
    if (!intersection.size()) {
        return true;
    }
    return false;    
}

int main()
{
    int N;
    int numerator, denominator, fghij, x;
    bool found;

    set<int> num;
    set<int> den;
    vector<pair<int, int>> answer;
    vector<int> intersection;

    for (N = 2; N <= 79; N++) {
        found = false;
        for (int denominator = 98765; denominator >= 1234; denominator--) {

            fghij = denominator;
            x = fghij * N;
            numerator = x;

            if (x > 98765 || x < 1234) {
                continue;
            }

            // if sets are unique, add to answer
            if (all_diff(numerator, denominator)) {
                printf("%05d / %05d = %d\n", numerator, denominator, N);
                answer.push_back(make_pair(numerator, denominator));
                found = true;
            }
        }
        if (!found) {
            printf("no solutions for %d\n", N);
        }

    }

//    for (auto it = answer.begin() ; it != answer.end(); ++it) {
//        printf("%05d, %05d\n", it->first, it->second);
//    }
}

