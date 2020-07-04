#!/usr/bin/env python3

import camping as data

#max_rows = len(data.items)
capacity = data.capacity
items = data.items
col_wts = data.col_wts

if data.__float__:
    def TO_INDEX(x):
        return (round(x))
else:
    def TO_INDEX(x):
        return (round(x-1))

# capacity columns, itmes rows
grid = [ [0 for col in range( data.capacity )] for row in range( len(data.items) ) ] 

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
            residual_wt_col = TO_INDEX(residual_wt)
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

