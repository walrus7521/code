#!/usr/bin/env python3

capacity = 4 # lbs
items = [
    # name,                 days, priority
    ('westminster abbey',   0.5,    7),
    ('globe theater',       0.5,    6),
    ('national gallery',    1,      9),
    ('british museum',      2,      9),
    ('st. pauls cathedral', 0.5,    8),
    ]
# capacity columns independent of column index
col_wts = [0.5, 1, 1.5, 2] # day bins
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

    wt_item   = items[row][1]
    val_item  = items[row][2]

    for col in range(capacity):
        col_wt = col_wts[col]

        old_max_value = old_max(row, col)
        max_val = max(old_max_value, val_item)

        print(row, col, val_item)
        show_grid()
        if wt_item < col_wt:
            residual_wt = col_wt - wt_item
            residual_wt_col = int(residual_wt - 1)
            new_max_value = val_item + lighter_max(row, residual_wt_col)
            if new_max_value > old_max_value:
                grid[row][col] = new_max_value
            else:
                grid[row][col] = old_max_value
        elif wt_item == col_wt:
            grid[row][col] = max_val
        else: # wt_item > col_wt
            grid[row][col] = old_max_value

print("++++++++++++++++++++++++")
show_grid()

