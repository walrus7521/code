#!/usr/bin/python

# https://www.ironalbatross.net/wiki/index.php5?title=Python_Curses#Getting_screen_dimensions
# https://github.com/bitly/data_hacks/blob/master/data_hacks/histogram.py

import curses
import time
import random
import subprocess
import sys

width=0
data=[]
def get_data():
    del data[:]

    command = "cat /sys/kernel/my_mapper/foo"
    p = subprocess.check_output(["cat", "/sys/kernel/my_mapper/foo"])
    p = p.split(":")
    for d in p:
        x,y=d.split(",")
        #print "data: "+x+ " : " +y
        pt = {}
        pt["bin"] = x
        pt["mag"] = y
        data.append(pt)

#    for i in range(0,width-1):
#        bin = i
#        mag = int(random.uniform(1,30))
#        pt = {}
#        pt["bin"]=bin
#        pt["mag"]=mag
#        data.append(pt);
    return data

#data = get_data()
#for pt in data:
#    mag = pt["mag"]
#    bin = pt["bin"]
#    print "bin: "+bin+" mag: "+mag
#sys.exit(0)

stdscr = curses.initscr()
curses.cbreak()
stdscr.keypad(1) 
height,width = stdscr.getmaxyx()
    
try:
    max_iops = 300
    begin_x = 0
    begin_y = 0
    win = curses.newwin(height, width, begin_y, begin_x)
    height,width = win.getmaxyx()

    base_line = height-2
    max_mag = height-10;
    for t in range(1, 100):
        data = get_data()
        for pt in data:
            mag = int(pt["mag"])
            bin = int(pt["bin"])
            mag = (mag * max_mag) / max_iops
            #if mag >= max_mag:
            #    mag = max_mag
            if mag == 0:
                mag = 1
            row = base_line-mag; 
            col = bin; 
            win.vline(row, bin, 'x', mag)

        time.sleep(1)
        win.refresh()
        win.erase()
        height, width = win.getmaxyx()
        base_line = height-2
        max_mag = height-10;
 
finally:
    win.getch()
    curses.nocbreak()
    stdscr.keypad(0)
    curses.echo()
    curses.endwin()
