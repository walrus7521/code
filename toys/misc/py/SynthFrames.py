#!/usr/bin/python

import platform
import time
import sys
import re

# same as synth.cpp, except the c++ is broken

# input csv format:
# frame, yval(pixels), angle(deg)
# 1, 507, 2.55
# 2, 507, 2.55
# 3, 507, 2.55
# 4, 507, 2.55

SAMPLE_SIZE = 256 # // frames
def cal_running_avg_dbl(avg, new_sample):
    global SAMPLE_SIZE
    if (abs(avg) > 0.0):
        avg -= avg / SAMPLE_SIZE
    avg += new_sample / SAMPLE_SIZE
    return avg

g_avg = 0.0
g_err = 0.0;

def denoise(angle):
    global g_avg
    global g_err
    g_avg = cal_running_avg_dbl(g_avg, angle)
    g_err = abs(g_avg-angle)
    # cout << "raw: " << angle << ", avg: " << avg << ", err: " << err << endl;
    return g_avg

def scan_file(num):
    prev_frame = -1
    count = 1
    skip = 0
    nframe = 0
    while (count < num):
        if (skip == 0):
            count = count + 1
            line = sys.stdin.readline()        
            if line:
                line = line.rstrip()
                try:
                    frame,yval,angle = line.split(",")
                    nframe = int(frame)
                except:
                    return
        if (prev_frame == -1):
            prev_frame = nframe
        elif (nframe != prev_frame+1):
            #print "missing frame: " +str(nframe)+ ", prev = " +str(prev_frame)
            if (skip == 0):
                skip = nframe - prev_frame
                nframe = prev_frame+1
                prev_frame = nframe-1
                continue
            else:
                nframe = prev_frame+1
                prev_frame = nframe
                skip = skip - 1

        else:
            #print "non-missing frame: " +str(nframe)+ ", prev = " +str(prev_frame)
            if (skip == 0):
                prev_frame = nframe
            else:
                prev_frame = nframe
                skip = skip - 1
        avg_angle = denoise(float(angle))
        print str(nframe)+ ", " +yval+ ", " +str(avg_angle)
    return


def main():
    nframes = 28782
    scan_file(nframes)

if __name__ == '__main__':
    main()

