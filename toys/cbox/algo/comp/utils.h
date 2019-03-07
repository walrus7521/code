#ifndef _UTILS_H_
#define _UTILS_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <bitset>
#include <unordered_map>
#include <string>
#include <tuple>

#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll; 
typedef pair<int, int> ii; 
typedef pair<pair<int, int>,int> iii; 
typedef vector<ii> vii;
typedef vector<int> vi;
typedef map<string,int> msi;

const int INF = 0x3f3f3f3f;

/*
 *
 * Setting up values in array:
 * initialize DP memoization table with -1
 *  memset(memo, -1, sizeof memo); 
 *
 * to clear array of integers
 *  memset(arr, 0, sizeof arr); 
 *
 * Use a vector to create a dynamic array 
 * and initialize it in one statement.
 * Creates a vector of size N and values as 0.
 *  vector<int> v(N, 0); 
 *  OR vi v(N, 0);  *
 *
 *
 * to simplify: if (a) ans = b; else ans = c;
 *  ans = a ? b : c; 
 *
 * to simplify: ans = ans + val; and its variants
 *  ans += val; 
 *
 * index++; if (index >= n) index = 0;
 *  index = (index + 1) % n; 
 *
 * index--; if (index < 0) index = n - 1;
 *  index = (index + n - 1) % n; 
 *
 * for rounding to nearest integer
 *  int ans = (int)((double)d + 0.5); 
 *
 * min/max shortcut to update max/min
 *  ans = min(ans, new_computation); 
 *
 * To return true if a value matches a given number, else return false
 *  if (val == given_no) return true; 
 *  else return false;
 *   
 *  return (val == given_no) 
 * 
 *
 */


class UnionFind {                                              // OOP style
private:
    vi p, rank, setSize;                       // remember: vi is vector<int>
    int numSets;
public:
    UnionFind(int N) {
        setSize.assign(N, 1); 
        numSets = N; 
        rank.assign(N, 0);
        p.assign(N, 0); 
        for (int i = 0; i < N; i++) p[i] = i; 
    }
    int findSet(int i) { 
        return (p[i] == i) ? i : (p[i] = findSet(p[i])); 
    }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) { 
        if (!isSameSet(i, j)) { 
            numSets--; 
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y]) { 
                p[y] = x; setSize[x] += setSize[y]; 
            }
            else { 
                p[x] = y; 
                setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++; 
            }
        } 
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

class SegmentTree { // similar to binary heap
private:
    vi st, A;
    int n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }
    void build(int p, int L, int R) {
        if (L == R) st[p] = L;
        else {
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] <= A[p2]) ? p1 : p2;
        }
    }
    int rmq(int p, int L, int R, int i, int j) {
        if (i > R || j < L) return -1; // current seg outside range
        if (L >= i && R <= j) return st[p]; // in range
        // compute min position L and R
        int p1 = rmq(left(p), L, (L+R)/2, i, j);
        int p2 = rmq(right(p), (L+R)/2+1, R, i, j);
        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        return (A[p1] <= A[p2]) ? p1 : p2;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int) A.size();
        st.assign(4*n, 0);
        build(1, 0, n-1);
    }
    int rmq(int i, int j) { return rmq(1, 0, n-1, i, j); } // overload
};

#define LSOne(s) (s & (-s))

class FenwickTree {
private:
    vi ft;
public:
    FenwickTree(int n) { ft.assign(n+1, 0); } // init n+1 zeros
    int rsq(int b) {
        int sum = 0;
        for (; b; b -= LSOne(b)) sum += ft[b];
        return sum;
    }
    int rsq(int a, int b) {
        return rsq(b) - (a == 1 ? 0 : rsq(a-1));
    }
    void adjust(int k, int v) {
        for (; k < (int) ft.size(); k += LSOne(k)) ft[k] += v;
    }
};

#endif // _UTILS_H_

