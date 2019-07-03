#!/usr/bin/env python3

triggers = ['x', 'y', 'z']
print(triggers)

trigger = {'x': 3, 'y': 4, 'z': 5}
row     = {'x': 3, 'y': 4, 'z': 5}

is_triggered = list(filter(lambda k : (float(row[k]) >= trigger[k]), triggers))

print(len(is_triggered))

if (len(is_triggered)):
    print("triggered")
else:
    print("no trigger")



my_list = [1, 5, 4, 6, 8, 11, 3, 12]

new_list = list(filter(lambda x: (x%2 == 0) , my_list))
# Output: [4, 6, 8, 12]
print(new_list)

new_list2 = list(map(lambda x: (x%2 == 0) , my_list))
# Output: [False, False, True, True, True, False, False, True]
print(new_list2)

