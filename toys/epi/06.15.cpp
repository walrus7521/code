#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

void show(vector<int>& A) {
    for (int i = 0; i < A.size(); ++i) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }
}

int ZeroOneRandom()
{
    double res = rand() / double(RAND_MAX);
    return (res < 0.50 ? 0 : 1); 
}

int UniformRandom(int a, int b)
{
    int t = b - a + 1, res;
    do {
        res = 0;
        for (int i = 0; (1 << i) < t; ++i) {
            res = res * 2 | ZeroOneRandom();
        }
    } while (res >= t);
    return (a + res);
}

/*
 * Generate non-uniform random numbers
 *
 * Create an array to select from, and use uniform
 * random numbers to select.
 *
 */

vector<int> SelectNonUniform(vector<int> A) {
    vector<int> select;
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        select.push_back(UniformRandom(i, n));
    }
    return select;
}

int main()
{
    srand((unsigned)time(NULL));
    vector<int> A = {22,3,5,4,8,1,34,76,23,98};
    vector<int> R = SelectNonUniform(A);
    show(R);
}
