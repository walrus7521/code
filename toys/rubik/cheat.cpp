#include <bits/stdc++.h>

using namespace std;

/* compiler switches
 *  -Wextra
 *  -fsanitize=undefined,address
 *  -D_GLIBCXX_DEBUG
 *  -std=c++11
 */

const int N = 1000;
int A[N];

int main()
{
    vector<int> vi;
    vi.push_back(5);
    for (int i = 0; i < vi.size(); i++) {
        printf("vi[%d] = %d\n", i, vi[i]);
    }

    set<int> S; 
    S.insert(5); // sets maintain sorted-ness
    if (S.count(2)) { // see if element is in the set
        S.erase(2);
    }
    for (int j : S) {
        printf("S => %d\n", j);
    }

    map<string, int> M; // uses RB tree
    if (M.count("KEY") == 0) {
        M["KEY"] = 1;
    } else {
        printf("M: %d\n", M["KEY"]);
    }

    // unordered structs use hashing for amortized constant time
    unordered_set<int> US;
    unordered_map<string, int> UM;

    stack<int> St;
    queue<int> Q;
    St.push(1); // pushes to top
    Q.push(2); // pushes to back
    Q.push(3); // pushes to back
    printf("stack top: %d, queue front: %d\n",
            St.top(), Q.front());
    St.pop(); Q.pop(); // removes elements

    priority_queue<int> pQ; // sorted, top element with highest priority
    pQ.push(3);
    pQ.push(7);
    pQ.push(1);
    printf("pq: %d\n", pQ.top());
    pQ.pop();

    // pairs and tuples
    pair<int, bool> P;
    tuple<int, string, int> T;

    P = make_pair(1, true);
    T = make_tuple(0, "fun", 42);
    printf("pair 1: %d, pair 2: %d\n",
            P.first, P. second);
    printf("tuple 1: %d, tuple 2: %s, tuple 3: %d\n",
            get<0>(T), get<1>(T).c_str(), get<2>(T));

    // sorting
    sort(vi.begin(), vi.end()); // vector
    sort(A, A+N); // array

}
