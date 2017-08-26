
#if 0
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; } 
#define compexch(A, B) if (less(B, A)) exch(A, B)
void bubble(Item a[], int l, int r)
{ 
    int i, j;
    for (i = l; i < r; i++)
        for (j = r; j > i; j--)
            compexch(a[j-1], a[j]);
}
#endif

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

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}

int bubble(vector<int>& a)
{
    int n = a.size();
    int numberOfSwaps = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                numberOfSwaps++;
            }
        }
        if (numberOfSwaps == 0) {
            break;
        }
    }
    return numberOfSwaps;
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int a_i = 0;a_i < n;a_i++){
       cin >> a[a_i];
    }
    show(a);
    int nswaps = bubble(a);
    show(a);
    cout << "Array is sorted in " << nswaps << " swaps." << endl;
    cout << "First Element: " << a[0] << endl;
    cout << "Last Element: " << a[a.size()-1] << endl;
    return 0;
}


