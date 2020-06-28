#!/usr/bin/env python3

capacity = 4 # lbs
items = [
    ('stereo', 4,  3000),
    ('laptop', 3,  2000),
    ('guitar', 1,  1500)
    ]

# capacity columns, itmes rows
grid = [ [0 for x in range( capacity )] for y in range( len(items) ) ] 

for i in range(len(items)):
    item   = items[i][0]
    weight = items[i][1]
    value  = items[i][2]
    print(item, weight, value)



