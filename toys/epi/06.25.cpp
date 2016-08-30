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

vector<pair<int, int> > find_rooks(vector<vector<int> >& A) {
    vector<pair<int, int> > ret;
    for (int r = 0; r < A.size(); ++r) {
        for (int c = 0; c < A[r].size(); ++c) {
            if (0 == A[r][c]) {
                ret.push_back(make_pair(r,c));
                A[r][1] = 0;
                A[1][c] = 0;
            }
        }
    }
    return ret;
 }

void zero_attackable(vector<vector<int> >& A) {
    // process row/col zero last
    for (int r = 1; r < A.size(); ++r) {
        if (A[r][1] == 0) {
            for (int i = 1; i < A.size(); ++i) {
                A[r][i] = 0;
            }
        }
    }
    for (int c = 1; c < A.size(); ++c) {
        if (A[1][c] == 0) {
            for (int i = 1; i < A.size(); ++i) {
                A[i][c] = 0;
            }
        }
    }
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
    find_rooks(A);
    show_board(A);
    zero_attackable(A);
    show_board(A);
    //for (int i = 0; i < vp.size(); ++i) {
    //    cout << vp[i].first << " " << vp[i].second << endl;
    //}
    return 0;
}

