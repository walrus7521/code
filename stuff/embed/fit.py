#!/usr/bin/python

import Tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
import csv # https://docs.python.org/2/library/csv.html

def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

AIRSPEED0 = 4
AIRSPEED1 = 5

speeds = [   0,    10,    20,    25,    30,    35,    40,    45,    50,    55,    60,    65,    70,    75,    80,    85,    90,    95,   100,   105,   110,   115,   120,   125,   130,   135 ]
frames = [8823, 12149, 14408, 15597, 16521, 17183, 18186, 20052, 21449, 23549, 24667, 25581, 26231, 26913, 27566, 28445, 29140, 29798, 30580, 31459, 32487, 33272, 34194, 35206, 35932, 36892 ]

air0_array = np.array([[0,0]])
air1_array = np.array([[0,0]])

for i in range(len(speeds)):
    speed        = speeds[i];
    center_frame = frames[i];
    min_frame    = frames[i]-4;
    max_frame    = frames[i]+4;   
    air0 = 0;
    air1 = 0;
    air0_avg = 0;
    air1_avg = 0;
    count = 0;
    #print speed
    csvfile = open('ADP_Std_All.csv', 'rb')
    csv_file = csv.reader(csvfile, delimiter=',', quotechar='|')
    next(csv_file) # skip first line
    for line in csv_file:       
        #print ', '.join(line)
        #for cell in line:
        #    print cell
        curr_frame = int(line[0].strip())
        #print "frame: {}".format(line[0])
        #if ($curr_frame == $min_frame) ; #print "first frame $min_frame\n";
        if ((curr_frame >= min_frame) and (curr_frame <= max_frame)):
            count = count + 1
            air0 += float(line[AIRSPEED0])
            air1 += float(line[AIRSPEED1])
            #print "$curr_frame, $air0, $air1"; 
        if (curr_frame == max_frame):
            air0_avg = air0 / count;
            air1_avg = air1 / count;
            #print "{0:5d}, {1:3d}, {2:5.0f}, {3:5.0f}".format(center_frame, speed, air0_avg, air1_avg)
            tmp = np.array([[int(speed), int(air0_avg)]])
            air0_array = np.append(air0_array, [[int(speed),int(air0_avg)]], axis=0)
            air1_array = np.append(air1_array, [[int(speed),int(air1_avg)]], axis=0)
            break;

#exit()
#
#with open('ADP_Std_All.csv', 'rb') as csvfile:
#    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
#    for row in spamreader:
#        print ', '.join(row)
#

# Raw data
#  8823,   0,  1891,  1862
# 12149,  10,  1962,  1926
# 14408,  20,  2082,  2049
# 15597,  25,  2239,  2208
# 16521,  30,  2405,  2372
# 17183,  35,  2600,  2565
# 18186,  40,  2806,  2776
# 20052,  45,  3023,  2994
# 21449,  50,  3317,  3285
# 23549,  55,  3597,  3568
# 24667,  60,  3973,  3945
# 25581,  65,  4376,  4349
# 26231,  70,  4827,  4799
# 26913,  75,  5292,  5264
# 27566,  80,  5751,  5723
# 28445,  85,  6292,  6265
# 29140,  90,  6847,  6822
# 29798,  95,  7352,  7327
# 30580, 100,  7891,  7869
# 31459, 105,  8442,  8413
# 32487, 110,  9086,  9058
# 33272, 115,  9742,  9720
# 34194, 120, 10460, 10435
# 35206, 125, 11300, 11276
# 35932, 130, 11951, 11924
# 36892, 135, 12758, 12728
#
# http://stackoverflow.com/questions/19165259/python-numpy-scipy-curve-fitting

#print "dump"
print air0_array

print air1_array

#exit()

# airspeed calculation
x = air0_array[1:,0] # air1_array[1:,0] # start on 1st element not zero-th
y = air0_array[1:,1] # air1_array[1:,1]

# calculate polynomial
z = np.polyfit(x, y, 3)
f = np.poly1d(z)

# pick 9 speed values
min_value = speeds[0]
max_value = speeds[len(speeds)-1]
print max_value
value_spacing = max_value/8
print value_spacing

# ideally we want to print out the LINTERP data structure
#
# LINTERP_STRUCT airspeed_0_linterp  = {9, {{ 2807.0f,  40.0f,  0.0218f},
#                                           { 3300.0f,  50.0f,  0.0175f},
#                                           { 3954.0f,  60.0f,  0.0117f},
#                                           { 4820.0f,  70.0f,  0.0106f},
#                                           { 5730.0f,  80.0f,  0.0088f},
#                                           { 6840.0f,  90.0f,  0.0094f},
#                                           { 7892.0f, 100.0f,  0.0080f},
#                                           { 9085.0f, 110.0f,  0.0079f},
#                                           {10444.0f, 120.0f,  0.0063f},
#                                           {    0.0f,   0.0f,  0.0f} } };
#

air0_linterp_array = np.array([[0.0,0.0,0.0]])
air1_linterp_array = np.array([[0.0,0.0,0.0]])
for v in my_range(0, max_value, value_spacing):
    interp = int(np.interp([v], x, y))
    air0_linterp_array = np.append(air0_linterp_array, [[interp,v,0]], axis=0)
    print "speed: {}, press: {}".format(v, interp)

print air0_linterp_array

air0_linterp_array.flags.writeable = True
air1_linterp_array.flags.writeable = True

for i in my_range(0, len(air0_linterp_array)-1, 1):
    if (i > 0):
        denominator = (float(air0_linterp_array[i][0]) - float(air0_linterp_array[i-1][0]))
        numerator   = (float(air0_linterp_array[i][1]) - float(air0_linterp_array[i-1][1]))
        if (denominator > 0):
            slope = numerator / denominator
            air0_linterp_array[i,2] = slope
            print "{} slope: {}".format(i,slope)

print air0_linterp_array

print "LINTERP_STRUCT airspeed_0_linterp  = {9, {"
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[1][0], air0_linterp_array[1][1], air0_linterp_array[1][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[2][0], air0_linterp_array[2][1], air0_linterp_array[2][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[3][0], air0_linterp_array[3][1], air0_linterp_array[3][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[4][0], air0_linterp_array[4][1], air0_linterp_array[4][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[5][0], air0_linterp_array[5][1], air0_linterp_array[5][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[6][0], air0_linterp_array[6][1], air0_linterp_array[6][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[7][0], air0_linterp_array[7][1], air0_linterp_array[7][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[8][0], air0_linterp_array[8][1], air0_linterp_array[8][2])
print "                                     {{ {0}, {1}, {2:f} }},".format(air0_linterp_array[9][0], air0_linterp_array[9][1], air0_linterp_array[9][2])
print "                                     {{ {0}, {1}, {2:f} }} ".format(0.0, 0.0, 0.0)
print "                                     {} }};"


exit()

print np.interp([71], x, y)

x_new = np.linspace(x[0], x[-1], 50)
y_new = f(x_new)

plt.plot(x,y,'o', x_new, y_new)
plt.xlim([x[0]-1, x[-1] + 1 ])
plt.show()

exit()

