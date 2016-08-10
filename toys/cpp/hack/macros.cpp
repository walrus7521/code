#include <climits>

#define FUNCTION(a,b)
#define toStr(a) #a
#define io(v) \
    cin >> v

#define INF INT_MAX

#define maximum(mx, v) \
    if (v > mx) { \
        mx = v; \
    }

#define minimum(mn, v) \
    if (v < mn) { \
        mn = v; \
    }

#define foreach(list, item) \
    for(int item = 0; item < list.size(); ++item)

#include <iostream>
#include <vector>
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif 

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main(){
	int n; cin >> n;
	vector<int> v(n);
	foreach(v, i) {
		io(v)[i];
	}
	int mn = INF;
	int mx = -INF;
	foreach(v, i) {
		minimum(mn, v[i]);
		maximum(mx, v[i]);
	}
	int ans = mx - mn;
	cout << toStr(Result =) <<' '<< ans;
	return 0;

}
