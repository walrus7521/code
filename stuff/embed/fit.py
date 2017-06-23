#!/usr/bin/python

# http://stackoverflow.com/questions/19165259/python-numpy-scipy-curve-fitting

import Tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
import csv # https://docs.python.org/2/library/csv.html

from input import * # input meta-data

def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

air_array = np.array([[0,0]]) # this causes zeroth value to be set to zero - so skip it

for i in range(len(SPEEDS)):
    speed        = SPEEDS[i];
    center_frame = FRAMES[i];
    min_frame    = FRAMES[i]-DELTA_FRAME;
    max_frame    = FRAMES[i]+DELTA_FRAME;   
    air_accum    = 0;
    air_avg      = 0;
    count        = 0;
    csvfile = open(CSV_FILENAME, 'rb')
    csv_rows = csv.reader(csvfile, delimiter=',', quotechar='|')
    if (SKIP_HEADER):
        next(csv_rows) # skip first line header
    for line in csv_rows:       
        curr_frame = int(line[0].strip())
        if ((curr_frame >= min_frame) and (curr_frame <= max_frame)):
            count += 1
            air_accum += float(line[AIRSPEED_INDEX])
        if (curr_frame == max_frame):
            air_avg = air_accum / count;
            tmp = np.array([[int(speed), int(air_avg)]])
            air_array = np.append(air_array, [[int(speed),int(air_avg)]], axis=0)
            break;

# airspeed calculation
x = air_array[1:,0] # start on 1st element not zero-th
y = air_array[1:,1] 

# calculate polynomial
z = np.polyfit(x, y, POLYNOMIAL_DEGREE) # 
f = np.poly1d(z)


# pick 9 speed values
min_value = SPEEDS[0]
max_value = SPEEDS[len(SPEEDS)-1]
print max_value
value_spacing = max_value/(NUM_DATA_POINTS-1)
print value_spacing

# now create the interpolation array
air_linterp_array = np.array([[0.0,0.0,0.0]])
for v in my_range(0, max_value, value_spacing):
    interp = int(np.interp([v], x, y))
    air_linterp_array = np.append(air_linterp_array, [[interp,v,0]], axis=0)
    print "speed: {}, press: {}".format(v, interp)

print air_linterp_array

air_linterp_array.flags.writeable = True

for i in my_range(0, len(air_linterp_array)-1, 1):
    if (i > 0):
        denominator = (float(air_linterp_array[i][0]) - float(air_linterp_array[i-1][0]))
        numerator   = (float(air_linterp_array[i][1]) - float(air_linterp_array[i-1][1]))
        if (denominator > 0):
            slope = numerator / denominator
            air_linterp_array[i,2] = slope
            print "{} slope: {}".format(i,slope)

print air_linterp_array

print "LINTERP_STRUCT airspeed_0_linterp  = {{ {0}, {{".format(NUM_DATA_POINTS);
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[1][0], air_linterp_array[1][1], air_linterp_array[1][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[2][0], air_linterp_array[2][1], air_linterp_array[2][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[3][0], air_linterp_array[3][1], air_linterp_array[3][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[4][0], air_linterp_array[4][1], air_linterp_array[4][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[5][0], air_linterp_array[5][1], air_linterp_array[5][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[6][0], air_linterp_array[6][1], air_linterp_array[6][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[7][0], air_linterp_array[7][1], air_linterp_array[7][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[8][0], air_linterp_array[8][1], air_linterp_array[8][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air_linterp_array[9][0], air_linterp_array[9][1], air_linterp_array[9][2])
print "                                     {{ {0}, {1}, {2:f} }} ".format(0.0, 0.0, 0.0)
print "                                     }};"


#exit()

x_new = np.linspace(x[0], x[-1], 50)
y_new = f(x_new)

plt.plot(x,y,'o', x_new, y_new)
plt.xlim([x[0]-1, x[-1] + 1 ])
plt.show()

exit()

