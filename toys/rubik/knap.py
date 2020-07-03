#!/usr/bin/env python3

capacity = 4 # lbs
items = [
     # name,  wt, value
    ('guitar', 1,  1500),
    ('stereo', 4,  3000),
    ('laptop', 3,  2000),
#   ('iphone', 1,  2000),
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

def curr_max(row, col):
    if row >= 1:
        print("cmax: ", row, col, grid[row-1][col])
        return grid[row-1][col]
    return 0

def prev_max(row, col):
    if row >= 1:
        print("pmax: ", row, col, grid[row-1][col])
        return grid[row][col]
    return 0

for row in range(len(items)):
    name_item = items[row][0]
    wt_item   = items[row][1]
    val_item  = items[row][2]
#   print(item, wt_item, val_item)
    for col in range(capacity):
        col_wt = col_wts[col]
        curr_max_value = curr_max(row, col)
        pmax_value = prev_max(row, col)
        new_max_value = 0
        print("===========================")
        print(row, col, val_item)
        show_grid()
        if wt_item < col_wt:
            rem_wt = col_wt - wt_item
#           new_max_value = val_item + prev_max(row-1, rem_wt)
            new_max_value = val_item + prev_max(row, rem_wt)
            if new_max_value > pmax_value:
                grid[row][col] = new_max_value
                print("here1: ", grid[row][col])
            else:
                grid[row][col] = curr_value
                print("here2: ", grid[row][col])
        elif wt_item == col_wt:
            if val_item >= curr_max_value:
                grid[row][col] = val_item
                print("here3: ", grid[row][col])
            else:
                grid[row][col] = curr_max_value
                print("here4: ", grid[row][col])
        else: # wt_item > col_wt
            grid[row][col] = curr_max_value #val_item
            print("here5: ", grid[row][col])

print("++++++++++++++++++++++++")
show_grid()

