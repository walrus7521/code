#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Check if a board game is winnable
 *
 * In a particular board game, players have to try to advance
 * through a sequence of positions. Each position has a nonnegative
 * integer associated with it, representing the maximum you can 
 * advance from that position in one move. For example, let
 * A = <3,3,1,0,2,0,1> represent the board game, ie, the i-th
 * entry in A is the maximum we can advance from i. Then the
 * following sequence of advances leads to the last position
 * <1,3,2>. If A = <3,2,0,0,2,0,1> it is not possible to advance
 * past position 3.
 *
 * Write a function which takes an array of n integers, where 
 * A[i] denotes the maximum you can advance from index i, and
 * returns whether it is possible to advance to the last index
 * starting from the beginning of the array.
 *
 */


bool CanReach(const vector<int>& A)
{
    int furthest_reach = 0;
    for (int i = 0; i <= furthest_reach && furthest_reach < A.size() - 1; ++i) {
        cout << "furth   : " << furthest_reach << endl;
        cout << "i       : " << i << endl;
        cout << "A[i]    : " << A[i] << endl;
        cout << "A[i] + i: " << A[i] + i << endl;
        cout << endl;
        furthest_reach = max(furthest_reach, A[i] + i);
    }
    return furthest_reach >= A.size() - 1;
}

int main()
{
    vector<int> A = {2,4,1,1,0,2,3};

    if (CanReach(A)) {
        cout << "yes" << endl;
    } else {
        cout << "no dice" << endl;
    }
}

