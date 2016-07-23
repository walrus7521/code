#include <iostream>
#include <vector>
#include <algorithm>
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

vector<int> ComputeRandomSubset(int n, int k) {
    vector<int> subset;
    for (int i = 0; i < k; ++i) {
        // disallow dups
        bool valid_entry = false;
        while (!valid_entry) {
            int val = UniformRandom(i, n);
            std::vector<int>::iterator it;
            it = std::find(subset.begin(), subset.end(), val);
            if (it != subset.end()) {
                std::cout << "Element found in subset: " << *it << '\n';
            } else {
                std::cout << "Element not found in subset\n";
                subset.push_back(val);
                valid_entry = true;
            }
        }
    }
    return subset;
}

int main()
{
    srand((unsigned)time(NULL));
    vector<int> A = ComputeRandomSubset(14, 7);
    show(A);
}

