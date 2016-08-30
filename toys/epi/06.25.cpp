#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void show_board(vector<vector<int> > A) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<pair<int, int> > find_rooks(vector<vector<int> > A) {
    vector<pair<int, int> > ret;
    for (int r = 0; r < A.size(); ++r) {
        for (int c = 0; c < A[r].size(); ++c) {
            if (0 == A[r][c]) {
                ret.push_back(make_pair(r,c));
            }
        }
    }
    return ret;
 }

void init_attack(vector<vector<int> >& A) {
    A.push_back({ 1,0, 1,1, 1,1, 1,1 });
    A.push_back({ 1,1, 1,1, 1,1, 1,1 });
    A.push_back({ 1,1, 1,1, 1,1, 1,1 });
    A.push_back({ 1,1, 1,1, 1,0, 1,1 });
    A.push_back({ 1,1, 1,0, 1,1, 1,1 });
    A.push_back({ 1,1, 1,1, 1,1, 1,1 });
    A.push_back({ 0,1, 1,1, 1,0, 1,1 });
    A.push_back({ 1,1, 1,1, 1,1, 1,1 });
}

int main()
{
    vector<vector<int> > A;
    init_attack(A);
    show_board(A);
    vector<pair<int, int> > vp = find_rooks(A);
    for (int i = 0; i < vp.size(); ++i) {
        cout << vp[i].first << " " << vp[i].second << endl;
    }
    return 0;
}

