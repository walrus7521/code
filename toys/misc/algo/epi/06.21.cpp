#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void show_sudoku(vector<vector<int> > A) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void init_sudoku(vector<vector<int> >& A) {
    A.push_back({ 5,3,0, 0,7,0, 0,0,0 });
    A.push_back({ 6,0,0, 1,9,5, 0,0,0 });
    A.push_back({ 0,9,8, 0,0,0, 0,6,0 });

    A.push_back({ 8,0,0, 0,6,0, 0,0,3 });
    A.push_back({ 4,0,0, 8,0,3, 0,0,1 });
    A.push_back({ 7,0,0, 0,2,0, 0,0,6 });
    
    A.push_back({ 0,6,0, 0,0,0, 2,8,0 });
    A.push_back({ 0,0,0, 4,1,9, 0,0,5 });
    A.push_back({ 0,0,0, 0,8,0, 0,7,9 });
}

bool has_duplicate(vector<int> A) {
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] == 0) continue;
        for (int j = i+1; j < A.size(); ++j) {
            if (A[i] == A[j]) {
                cout << "dup" << endl;
                return true;
            }
        }
    }
    return false;
}

bool has_dup_row(vector<vector<int> > A) {
    vector<int> vi;
    for (int r = 0; r < 9; ++r) {
        vi.clear();
        for (int c = 0; c < 9; ++c) {
            vi.push_back(A[r][c]);
        }
        if (has_duplicate(vi)) return true;
    }
    return false;
}

bool has_dup_col(vector<vector<int> > A) {
    vector<int> vi;
    for (int c = 0; c < 9; ++c) {
        vi.clear();
        for (int r = 0; r < 9; ++r) {
            vi.push_back(A[r][c]);
        }
        if (has_duplicate(vi)) return true;
    }
    return false;
}

bool has_dup_blk(vector<vector<int> > A) {
    vector<int> vi;
    int row_offset = 0, col_offset = 0;

// column 0
    row_offset = 0, col_offset = 0;
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;

    row_offset = 3, col_offset = 0;
    vi.clear();
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;
 
    row_offset = 6, col_offset = 0;
    vi.clear();
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;
 
// column 3
    row_offset = 0, col_offset = 3;
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;

    row_offset = 3, col_offset = 3;
    vi.clear();
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;
 
    row_offset = 6, col_offset = 3;
    vi.clear();
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;
 
// column 6
    row_offset = 0, col_offset = 6;
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;

    row_offset = 3, col_offset = 6;
    vi.clear();
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;
 
    row_offset = 6, col_offset = 6;
    vi.clear();
    for (int i = row_offset; i < row_offset+3; ++i) {
        for (int j = col_offset; j < col_offset+3; ++j) {
            vi.push_back(A[i][j]);
        }
    }
    if (has_duplicate(vi)) return true;
 
    return false;
}

int main()
{
    vector<vector<int> > A;
    init_sudoku(A);
    show_sudoku(A);
    if ((has_dup_col(A)) || (has_dup_row(A)) || (has_dup_blk(A))) {
        cout << "bad sudoku" << endl;
    } else {
        cout << "valid sudoku" << endl;
    }
    return 0;
}

