#include <iostream>
#include <vector>

using namespace std;

#define INVALID (-99)

template <typename T>
using matrix = vector<vector<T>>;

void showChess(matrix<bool> board)
{
    int row, col;
    printf("      0 1 2 3 4 5 6 7\n\n");
    for (row = 0; row < board.size(); ++row) {
        printf("%d     ", row);
        for (col = 0; col < 8; ++col) {
            printf("%d ", (int) board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

struct Pos {
    int row;
    int col;
};

bool valid(Pos p)
{
    if (p.row >= 0 && p.row <= 7 &&
        p.col >=0 && p.col <= 7) {
        return true;
    }
    return false;
}

bool safeLocation2(Pos p, Pos attacker)
{
    //printf("checking p(%d,%d) => attacker(%d,%d)\n", p.row, p.col, attacker.row, attacker.col);
    if (!valid(p)) return true;
    if (!valid(attacker)) return true;
    if (p.row == attacker.row) return false;
    if (p.col == attacker.col) return false;
    if (p.row + p.col == attacker.row + attacker.col) return false;
    if (p.col - p.row == attacker.col - attacker.row) return false;
    return true;
}

//vector<int> queenList(8); // queenList[col] = row;

void showBoard(const vector<int>& queenList)
{
    int row, col;
    printf("  0 1 2 3 4 5 6 7\n");
    for (row = 0; row < 8; ++row) {
        printf("%d ", row);
        for (col = 0; col < 8; ++col) {
            if (queenList[col] == row) {
                printf("Q ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
}

bool safeLocation(int row, int col, const vector<int>& queenList)
{
    int qRow, qCol;
    for (qCol = 0; qCol < col; ++qCol) {
        qRow = queenList[qCol];
        if (qRow == row) return false;
        else if (qCol == col) return false;
        else if ((qCol-qRow == col-row) || (qCol+qRow == col+row)) return false;
    }
    return true;
    return true;
}

bool placeQueens(vector<int>& queenList, int col)
{
    int row;
    bool foundLocation;

    if (col == 8) {// halting condition
        foundLocation = true;
    } else {
        foundLocation = false; // start at row 0
        row = 0;
        while (row < 8 && !foundLocation) {
            // check whether cell (row,col) is safe; if so,
            // assign row to queenList and call placeQueens()
            // for the next col; otherwise, go to the next row
            if (safeLocation(row, col, queenList) == true) {
                queenList[col] = row;
                
                // recursive step. try to place queens in col+1 --> 7
                // !!!! ***** calling for next column
                foundLocation = placeQueens(queenList, col+1);
            }
            // current row fails, try next row
            row++;
        } // end while
    }
    return foundLocation;
}

bool placeQueen(Pos p, vector<int>& queenList)
{
    int row, col;
    for (col = 0; col < 8; ++col) {
        row = queenList[col];
        if (row != INVALID) {
            Pos attacker = {row, col};
            if (!safeLocation2(p, attacker)) {
                return false;
            }
        }
    }
    return true;
}

void test()
{
    Pos p = {4,2};
    Pos att1 = {2,0};
    Pos att2 = {1,5};
    Pos att3 = {4,6};
    Pos att4 = {7,2};

    if (!safeLocation2(p, att1)) { cout << " att1 boom\n";  }
    if (!safeLocation2(p, att2)) { cout << " att2 boom\n";  }
    if (!safeLocation2(p, att3)) { cout << " att3 boom\n";  }
    if (!safeLocation2(p, att4)) { cout << " att4 boom\n";  }

    vector<int> queenList(8);
    int row, col;
    for (col = 0; col < 8; ++col) queenList[col] = INVALID;

    int nQueens = 0;
    for (col = 0; col < 8; ++col) {
        for (row = 0; row < 8; ++row) {
            Pos p = {row, col};
            if (placeQueen(p, queenList)) {
                printf("ok to place: (%d,%d)\n", row, col);
                queenList[col] = row;
                nQueens++;
            }
        }
    }
    printf("nQueens: %d\n", nQueens);
    showBoard(queenList);

    matrix<bool> board;
    board.resize(8);
    for (row = 0; row < 8; ++row) board[row].resize(8);

    for (col = 0; col < 8; ++col) {
        for (row = 0; row < 8; ++row) {
            board[row][col] = false;
        }
    }
    showChess(board);
   
}

bool queens(vector<int>& queenList, int row)
{
    // place first queen at (row,0)
    queenList[0] = row;
    // locate remaining queens in columns 1 through 7
    if (placeQueens(queenList, 1)) {
        return true;
    }
    return false;
}

void do_queens()
{
    vector<int> queenList(8);
    int row, col;
    for (col = 0; col < 8; ++col) queenList[col] = INVALID;
    for (row = 0; row < 8; ++row) queens(queenList, row);
    showBoard(queenList);
}

int main()
{
    do_queens();
    test();
}

