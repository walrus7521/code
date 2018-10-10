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
    vi first;
    vi second;
    vi third;
    vi fourth;

    first.assign (7,100);             // 7 ints with a value of 100

    std::vector<int>::iterator it;
    it=first.begin()+1;

    second.assign (it,first.end()-1); // the 5 central values of first

    int myints[] = {1776,7,4};
    third.assign (myints,myints+3);   // assigning from array.

    fourth.resize(5);
    fourth.resize(8,100);
    fourth.resize(12);
    
    std::cout << "Size of first: " << int (first.size()) << '\n';
    std::cout << "Size of second: " << int (second.size()) << '\n';
    std::cout << "Size of third: " << int (third.size()) << '\n';
    std::cout << "Size of fourth: " << int (fourth.size()) << '\n';

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

