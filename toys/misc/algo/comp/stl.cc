#include "utils.h"

int main()
{
    vi y;
    y.push_back(42);
    for(auto x : y) printf("%d\n", x);

    msi z { {"dude", 41},
            {"wsup", 42},
            {"dawg", 43}, };
    for(auto x : z) printf("%s : %d\n", x.first.c_str(), (int) x.second);

// <vector>
// reserve, resize, assign, clear, erase, iterators
    vector<int> VI;

// <stack>
//  push, pop, top
    stack<int> SI;

// <queue> => priority_queue
// push, pop, front, back
    queue<int> QI;

// <deque>
// push_front, push_back, pop_front, pop_back
    deque<int> DQI;

// <map>
    map<string, int> MSI;

// <bitset>
// set, reset, [], test
    bitset<40> BS;

// <unordered_map>

// <algorithm> sort, see pg 35
// binary search: lower_bound, upper_bound, binary_search

}

