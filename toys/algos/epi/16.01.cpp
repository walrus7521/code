#include <iostream>
#include <array>
#include <stack>

using std::array;
using std::stack;
using std::cout;
using std::endl;

void Transfer(int n, array<stack<int>, 3>& pegs, int from, int to, int use) {
    if (n > 0) {
        Transfer(n - 1, pegs, from, use, to);
        pegs[to].push(pegs[from].top());
        pegs[from].pop();
        //cout << "Move from peg " << from << " to peg " << to << endl;
        Transfer(n - 1, pegs, use, to, from);
    }
}

void show(array<stack<int>, 3>& pegs) {
    cout << "pegs.size = " << pegs.size() << endl;
    for (int i = 0; i < pegs.size(); ++i) {
        cout << "[" << i << "]" << endl;
        while (!pegs[i].empty()) {
            int val = pegs[i].top();
            cout << "[" << i << "] = " << val << endl;
            pegs[i].pop();
        }
    }
}

void MoveTowerHanoi(int n) {
    array<stack<int>, 3> pegs;
    for (int i = n; i >= 1; --i) {
        pegs[0].push(i);
    } 
    Transfer(n, pegs, 0, 1, 2);
    show(pegs);
}


int main()
{
    MoveTowerHanoi(64);
    return 0;
}
