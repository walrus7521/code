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
    return 0;
}

