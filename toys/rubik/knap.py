#!/usr/bin/env python3

capacity = 4 # lbs
items = [
     # name,  wt, value
    ('guitar', 1,  1500),
    ('stereo', 4,  3000),
    ('laptop', 3,  2000),
    ('iphone', 1,  2000),
#   ('mp3',    1,  1000),
    ]
# capacity columns independent of column index
col_wts = [1, 2, 3, 4]
# capacity columns, itmes rows
grid = [ [0 for col in range( capacity )] for row in range( len(items) ) ] 

def show_grid():
    for row in range(len(items)):
        for col in range(capacity):
            print(grid[row][col], end=' ')
        print('')

def old_max(row, col):
    if row >= 1:
        print("cmax: ", row, col, grid[row-1][col])
        return grid[row-1][col]
    return 0

def lighter_max(row, col):
    if row >= 1:
        print("lmax: ", row, col, grid[row-1][col])
        return grid[row-1][col]
    return 0

for row in range(len(items)):

    name      = items[row][0]
    wt_item   = items[row][1]
    val_item  = items[row][2]

    for col in range(capacity):
        col_wt = col_wts[col]

        old_max_value = old_max(row, col)
        max_val = max(old_max_value, val_item)

        print("=======================")
        print(name, ': ', row, col, val_item)
        if wt_item < col_wt:
            residual_wt = col_wt - wt_item
            residual_wt_col = round(residual_wt - 1)
            print('res: ', residual_wt, 'col: ', residual_wt_col)
            new_max_value = val_item + lighter_max(row, residual_wt_col)
            if new_max_value > old_max_value:
                grid[row][col] = new_max_value
            else:
                grid[row][col] = old_max_value
        elif wt_item == col_wt:
            grid[row][col] = max_val
        else: # wt_item > col_wt
            grid[row][col] = old_max_value
        show_grid()

print("++++++++++++++++++++++++")
show_grid()

