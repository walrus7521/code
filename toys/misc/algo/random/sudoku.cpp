#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>

// kinds of recursion: linear, tail, binary, nested, and mutual.
// linear: makes single call per function to itself
//      e.g. factorial, sqrt using Newton method

// tail: when recursive call is the last statement of the function,
//       often the return statement.  Should be replaced by iterative.
//      e.g. gcd

// binary: makes 2 or more calls to self per call
//      e.g. math combinations: choose

// exponential: exponential calls relative to size of data set, f(n) => a^n calls.
//      e.g. permutation of data set: print_permutations

// nested: one argument to function is the function itself
//      e.g. ackerman's function

// mutual: function A calls B, which calls C, which calls A
//      e.g. even_or_odd 

// restart at: http://www.sparknotes.com/cs/recursion/whatisrecursion/problems_1.html
// Problem : What category would the following function fit into? How many function 
//           calls will there be in total if the function is called with func(10)?

// catalog:
//  fib
//  fac
//  num_sums
//  sqrt
//  gcd
//  choose
//  permutations
//  ackerman
//  even/odd
//  mystery
//  tree node
//  pow
//  reverse string
//  zip arrays
//  find max
//  string match
//  sum nums
//  sort

using namespace std;

#define swap(a,b) { \
    int tmp = a; \
    tmp = a; \
    a = b; \
    b = tmp; \
}

void show_sudoku(int g[9][9], int idx)
{
    int i, j;
    for (i = 0; i < 9; i++) {
        printf("%d %d %d | %d %d %d | %d %d %d\n", 
                g[i][0], g[i][1], g[i][2], g[i][3], 
                g[i][4], g[i][5], g[i][6], g[i][7], g[i][8]);
    }
}

void show_sudoku_col(int g[9][9], int col)
{
    int i;
    for (i = 0; i < 9; i++) {
        printf("%d\n", g[i][col]); 
    }
}

bool is_avail_row(int g[9][9], int row, int val)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (val == g[row][i]) return false;
    }
    return true;
}

bool is_avail_col(int g[9][9], int col, int val)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (val == g[i][col]) return false;
    }
    return true;
}

// iterative
void sudoku_i(int grid[9][9])
{
    // march across row
    // for each cell in the row, if it is filled, move on
    //    if it is empty, get mask of all numbers taken on row and col
    //                    get mask of all number in group
    //    invert the mask and pick an available number
    // move to next row
}

bool is_available_group(int g[9][9], int group, int val)
{
    int r, c, r_end, c_end;
    switch (group) {
        case 1:
            r = 0;
            c = 0;
            break;
        case 2:
            r = 0;
            c = 3;
            break;
        case 3:
            r = 0;
            c = 6;
            break;
        case 4:
            r = 3;
            c = 0;
            break;
        case 5:
            r = 3;
            c = 3;
            break;
        case 6:
            r = 3;
            c = 6;
            break;
        case 7:
            r = 6;
            c = 0;
            break;
        case 8:
            r = 6;
            c = 3;
            break;
        case 9:
            r = 6;
            c = 6;
            break;
    }
    r_end = r + 3;
    c_end = c + 3;
    for (int i = r; i < r_end; i++) {
        for (int j = c; j < c_end; j++) {
            if (g[i][j] == val) return true;
        }
    }
    return false;
}

int get_group(int row, int col)
{
#if 0
    int i, j, g = 0;
    printf("--------------------------------------------"
           "--------------------------------------------\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("(%d, %d) - ", i, j);
            if ((j+1) % 3 == 0) printf(" | ");
        }
        printf("\n");
        if ((i+1) % 3 == 0) {
            printf("--------------------------------------------"
                   "--------------------------------------------\n");
        }
    }
#endif
    int group_row = row / 3;
    int group_col = col / 3;
    int group = (3 * group_row) + group_col + 1;
    return group;
}


void test_sudoku()
{
    // sudoku
    int grid[9][9] = 
    {
      //    I         II       III
      // 1  2  3   4  5  6   7  8  9
        {5, 3, 0,  0, 7, 0,  0, 0, 0},
      //10 11 12   13 14 15  16 17 18
        {6, 0, 0,  1, 9, 5,  0, 0, 0},
     // 19 20 21   22 23 24  25 26 27
        {0, 9, 8,  0, 0, 0,  0, 6, 0},

      //   IV          V        VI
     // 28 29 30   31 32 33  34 35 36
        {8, 0, 0,  0, 6, 0,  0, 0, 3},
     // 37 38 39   40 41 42  43 44 45
        {4, 0, 0,  8, 0, 3,  0, 0, 1},
     // 46 47 48   49 50 51  52 53 54
        {7, 0, 0,  0, 2, 0,  0, 0, 6},

      //   VII       VIII       IX
     // 55 56 57   58 59 60  61 62 63
        {0, 6, 0,  0, 0, 0,  2, 8, 0},
     // 64 65 66   67 68 69  70 71 72
        {0, 0, 0,  4, 1, 9,  0, 0, 5},
     // 73 74 75   76 77 78  79 80 81
        {0, 0, 0,  0, 8, 0,  0, 7, 9},
    };
    show_sudoku(grid, 1);

    //int r = 0, c = 4;
    //for (r = 0; r < 9; r++) {
    //    for (c = 0; c < 9; c++) {
    //        cout << "group(" << r << "," << c << ") => " << get_group(r,c) << endl;
    //    }
    //}

    //cout << "show sudoku by col" << endl;
    //for (int c = 0; c < 1; c++) {
    //    show_sudoku_col(grid, c);
    //}
}

int main()
{
    test_sudoku();
}

