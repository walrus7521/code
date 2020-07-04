#include "utils.h"

using namespace std;

/*
__float_bins__ = False

capacity = 4 # lbs

items = [
     # name,  wt, value
    ('guitar', 1,  1500),
    ('stereo', 4,  3000),
    ('laptop', 3,  2000),
    ('iphone', 1,  2000),
    ]

# capacity columns independent of column index
col_wts = [1, 2, 3, 4]

*/

typedef struct items {
    int capacity;
    bool is_float;
    vector<tuple<string, int, int>> item;
    vector<int> col_wts;
} items_t;

items_t items;
vector<vector<int>> grid; // = [ [0 for col in range( capacity )] for row in range( len(items) ) ] 


void read_cfg()
{
    items.is_float = false;

    items.capacity = 4;

    items.item.resize(items.capacity);
    items.item[0] = make_tuple(string("guitar"), 1, 1500);
    items.item[1] = make_tuple(string("stereo"), 4, 3000);
    items.item[2] = make_tuple(string("laptop"), 3, 2000);
    items.item[3] = make_tuple(string("iphone"), 1, 2000);

    items.col_wts.resize(4);
    items.col_wts[0] = 1;
    items.col_wts[1] = 2;
    items.col_wts[2] = 3;
    items.col_wts[3] = 4;

    grid.resize(items.capacity);
    for (int i = 0; i < items.capacity; ++i) {
        grid[i].resize(items.item.size());
    }
}

int old_max(int row, int col) 
{
    if (row >= 1) {
        return grid[row-1][col];
    }
    return 0;
}

int lighter_max(int row, int col)
{
    if (row >= 1) {
        return grid[row-1][col];
    }
    return 0;
}

void knap()
{
    for (int row = 0; row < items.item.size(); ++row) {
        for (int col = 0; col < items.capacity; ++col) {
            int col_wt = items.col_wts[col];
        }
    }
}

int main()
{
    read_cfg();
}

