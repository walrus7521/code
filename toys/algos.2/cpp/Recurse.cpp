#include <iostream>
#include <vector>

using namespace std;

#define INVALID (-99)

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

bool isVulnerable(Pos p, Pos attacker)
{
    //printf("checking p(%d,%d) => attacker(%d,%d)\n", p.row, p.col, attacker.row, attacker.col);
    if (!valid(p)) return false;
    if (!valid(attacker)) return false;
    if (p.row == attacker.row) return true;
    if (p.col == attacker.col) return true;
    if (p.row + p.col == attacker.row + attacker.col) return true;
    if (p.col - p.row == attacker.col - attacker.row) return true;
    return false;
}

vector<int> queenList(8); // queenList[col] = row;

void showBoard()
{
    int row, col;
    printf("  0 1 2 3 4 5 6 7\n");
    for (row = 0; row < 8; ++row) {
        printf("%d ", row);
        for (col = 0; col < 8; ++col) {
            if (queenList[col] == row) {
                printf("x ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

bool placeQueen(Pos p)
{
    int row, col;
    for (col = 0; col < 8; ++col) {
        row = queenList[col];
        if (row != INVALID) {
            Pos attacker = {row, col};
            if (isVulnerable(p, attacker)) {
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

    if (isVulnerable(p, att1)) { cout << " att1 boom\n";  }
    if (isVulnerable(p, att2)) { cout << " att2 boom\n";  }
    if (isVulnerable(p, att3)) { cout << " att3 boom\n";  }
    if (isVulnerable(p, att4)) { cout << " att4 boom\n";  }

    int row, col;
    for (col = 0; col < 8; ++col) queenList[col] = INVALID;

    int nQueens = 0;
    for (col = 0; col < 8; ++col) {
        for (row = 0; row < 8; ++row) {
            Pos p = {row, col};
            if (placeQueen(p)) {
                printf("ok to place: (%d,%d)\n", row, col);
                queenList[col] = row;
                nQueens++;
            }
        }
    }
    printf("nQueens: %d\n", nQueens);
    showBoard();
   
}


int main()
{
    test();
}

