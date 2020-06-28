#!/usr/bin/env python3

capacity = 4 # lbs
items = [
    ('stereo', 4,  3000),
    ('laptop', 3,  2000),
    ('guitar', 1,  1500)
    ]

# capacity columns, itmes rows
grid = [ [0 for x in range( capacity )] for y in range( len(items) ) ] 

for row in range(len(items)):
    item   = items[row][0]
    weight = items[row][1]
    value  = items[row][2]
    print(item, weight, value)

    for col in range(capacity):
        wt = col+1
        for item in range(len(items)):
            if wt <= items[item][1]:
                grid[row][col].append(items[item])



