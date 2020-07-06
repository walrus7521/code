#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

// integer version
int TO_INDEX(col)
{
    return (round(col-1));
}

const int capacity = 4;
typedef struct item {
    char name[8];
    int wt;
    int value;
} item_t;

const item_t items[] = {
    {.name  = "guitar", .wt    = 1, .value = 1500 },
    {.name  = "stereo", .wt    = 4, .value = 3000 },
    {.name  = "laptop", .wt    = 3, .value = 2000 },
    {.name  = "iphone", .wt    = 1, .value = 2000 },
};

int col_wts[] = {1, 2, 3, 4};
const int num_rows = sizeof(items)/sizeof(items[0]);
int grid[num_rows][capacity];

void show_grid()
{
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < capacity; col++) {
            printf("%04d ", grid[row][col]);
        }
        printf("\n");
    }
}

void show_items()
{
    for (int row = 0; row < num_rows; row++) {
        printf("%s: %d %d\n", items[row].name, items[row].wt, items[row].value);
    }
}

int prev_max(int row, int col) 
{
    if (row >= 1) {
        return grid[row-1][col];
    }
    return 0;
}

void knap()
{
    for (int row = 0; row < num_rows; ++row) {

        int wt_item   = items[row].wt;
        int val_item  = items[row].value;

        printf("%s: %d %d\n", items[row].name, wt_item, val_item);
        printf("=======================\n");
        for (int col = 0; col < capacity; ++col) {

            int col_wt = col_wts[col];
            int old_max_value = prev_max(row, col);
            int max_val = max(old_max_value, val_item);

            if (wt_item < col_wt) {
                int residual_wt = col_wt - wt_item;
                int residual_wt_col = TO_INDEX(residual_wt);
                printf("res: %d col: %d\n", residual_wt, residual_wt_col);
                int new_max_value = val_item + prev_max(row, residual_wt_col);
                if (new_max_value > old_max_value) {
                    grid[row][col] = new_max_value;
                } else {
                    grid[row][col] = old_max_value;
                }
            } else
            if (wt_item == col_wt) {
                grid[row][col] = max_val;
            } else {
                grid[row][col] = old_max_value;
            }
        }
        show_grid();
    }
}

int main()
{
    //show_items();
    knap();
    printf("++++++++++++++++++++++++++\n");
    show_grid();
}

