#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <limits.h>

using namespace std;

typedef std::pair <int, int> indexPair;

void show(vector<int> A) {
    vector<int>::const_iterator viter;
    cout << "[";
    for (viter = A.begin(); viter != A.end(); ++viter) {
        cout << *viter << ", ";
    }
    cout << "]\n";
}

int dups(vector<int> raw, vector<int> sorted) {
    vector<int> dups;
    vector<indexPair> pairs;
    for (int i = 1; i < sorted.size(); ++i) {
        if (sorted[i-1] == sorted[i]) {
            dups.push_back(sorted[i]);
        }
    }
    for (int i = 0; i < dups.size(); ++i) {
        int first=-1, second=-1;
        int j;
        //cout << "finding: " << dups[i] << endl;
        for (j = 0; j < raw.size(); ++j) {
            if (dups[i] == raw[j]) {
                //cout << "found first: " << raw[j] << " @ " << j << endl;
                first = j;
                break;
            }
        }
        for (++j; j < raw.size(); ++j) {
            if (dups[i] == raw[j]) {
                //cout << "found second: " << raw[j] << " @ " << j << endl;
                second = j;
                break;
            }            
        }
        if (first >= 0 && second >= 0) {
            pairs.push_back( std::make_pair( first, second ) );
        }
    }
    vector<indexPair>::const_iterator piter;
    int dist;
    vector<int> distances;
    for (piter = pairs.begin(); piter != pairs.end(); ++piter) {
        //cout << piter->first << ", " << piter->second << endl;
        dist = abs(piter->first - piter->second);
        //cout << "abs: " << dist << endl;
        distances.push_back(dist);
    }

    int min = INT_MAX;
    bool found = false;
    vector<int>::const_iterator dist_iter;
    for (dist_iter = distances.begin(); dist_iter != distances.end(); ++dist_iter) {
        //cout << *dist_iter << endl;
        if (*dist_iter < min) {
            min = *dist_iter;
            found = true;
        }
    }
    if (!found) {
        min = -1;
    }
    

    return min;
}

int main(){
    int n;
    cin >> n;
    vector<int> A(n);
    for(int i = 0;i < n;i++){
       cin >> A[i];
    }
    //show(A);
    vector<int> B = A;
    std::sort(B.begin(), B.end());
    //show(B);
    int min = dups(A, B);
    cout << min << endl;

    return 0;
}

