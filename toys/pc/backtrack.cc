#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

#define MAXCANDIDATES 12
bool finished = false;

void process_solution(const vector<int>& a, int k) {
    int i;
    cout << "{";
    for (i = 1; i <= k; ++i) if (a[i] == true) cout << " " << i ;
    cout << " }\n";
}

int is_a_solution(const vector<int> a, int k, int n) {
    return (k == n);
}

void construct_candidates(vector<int> a, int k, 
        int n, vector<int>& c, int& ncandidates) {
    c[0] = true;
    c[1] = false;
    ncandidates = 2;
}

void show(vector<int> c) {
    for (vector<int>::const_iterator i = c.begin(); i != c.end(); ++i) {
        cout << *i ;
    }
    cout << endl;
}

void backtrack(vector<int> a, int k, int input) {
    vector<int> c(MAXCANDIDATES);
    int ncandidates;
    int i;
    if (is_a_solution(a, k, input)) {
        process_solution(a, k);
    } else {
        ++k;
        construct_candidates(a, k, input, c, ncandidates);
        for (i = 0; i < ncandidates; ++i) {
            a[k] = c[i];
            backtrack(a, k, input);
            if (finished) return;
        }
    }
}

void generate_subsets(int n) {
    vector<int> a(MAXCANDIDATES);
    backtrack(a, 0, n);
}

int main()
{
    generate_subsets(3);
    return 0;
}

