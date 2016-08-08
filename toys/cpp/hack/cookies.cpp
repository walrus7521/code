#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


int main(){
    int n; // guests
    int m; // cookies
    cin >> n >> m;
    if (m < n) {
        cout << n - m << endl;
    } else 
    if (m == n) {
        cout << 0 << endl;
    } else {
        int extra = m / n;
        cout << "extra: " << extra << endl;
        //extra++;
        extra *= (m - n) * n;
        cout << "more: " << extra << endl;
    }
    
    return 0;
}

