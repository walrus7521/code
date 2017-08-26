#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

void init_fill_3x3(vector<vector<int> >& a) {
    a.resize(3);
    for(int i = 0; i < 3; i++) a[i].resize(3, 0);
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[1][0] = 4;
    a[1][1] = 5;
    a[1][2] = 6;
    a[2][0] = 7;
    a[2][1] = 8;
    a[2][2] = 9;
}

void init_fill_4x4(vector<vector<int> >& a) {
    a.resize(4);
    for(int i = 0; i < 4; i++) a[i].resize(4, 0);
    a[0][0] = 1;
    a[0][1] = 2;
    a[0][2] = 3;
    a[0][3] = 4;
    a[1][0] = 5;
    a[1][1] = 6;
    a[1][2] = 7;
    a[1][3] = 8;
    a[2][0] = 9;
    a[2][1] = 10;
    a[2][2] = 11;
    a[2][3] = 12;
    a[3][0] = 13;
    a[3][1] = 14;
    a[3][2] = 15;
    a[3][3] = 16;    
}

void show_2d(vector<vector<int> > A) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            printf("%02d ", A[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void rotate_spiral_outer_ring_vec(vector<vector<int> >& a, int n)
{
    queue<int> b;
    int tmp, tmp2, r, c, start=a.size()-n, end=n-1;
    //printf("outer: size=%d, n=%d, start=%d, end=%d\n", size, n, start, end);
    for (c = start; c < end; ++c) { // east
        tmp = a[start][c];
        b.push(tmp);
    }
    for (r = start; r < end; ++r) { // south
        tmp = a[r][end];
        tmp2 = b.front();
        a[r][end] = tmp2;
        b.pop();
        b.push(tmp);
    }
    for (c = end; c > start; --c) { // west
        tmp = a[end][c];
        tmp2 = b.front();
        a[end][c] = tmp2;
        b.pop();
        b.push(tmp);
    }
    for (r = end; r > start; --r) { // north
        tmp = a[r][start];
        tmp2 = b.front();
        a[r][start] = b.front();
        b.pop();
        b.push(tmp);
    }
    for (c = start; c < end; ++c) { // east
        tmp = a[start][c];
        tmp2 = b.front();
        a[start][c] = b.front();
        b.pop();
    }
}

int main()
{
    int n = 4;
    vector<vector<int> > A;
    init_fill_4x4(A);
    show_2d(A);
    for (int i = n; i > n/2; --i) {
        rotate_spiral_outer_ring_vec(A, i);
    }
    show_2d(A);
    cout << endl;
    return 0;
}

