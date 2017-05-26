#!/usr/bin/python

# https://www.ironalbatross.net/wiki/index.php5?title=Python_Curses#Getting_screen_dimensions
# https://github.com/bitly/data_hacks/blob/master/data_hacks/histogram.py
# http://blog.skeltonnetworks.com/tag/python-curses/

import curses
import time
import random

width=0
data=[]
def get_data():
    del data[:]
    for i in range(0,width-1):
        bin = i
        mag = int(random.uniform(1,300))
        pt = {}
        pt["bin"]=bin
        pt["mag"]=mag
        data.append(pt);
    return data

def draw_axes(win,h,w):
    #win.vline(0,0,'.',100)
    #win.hline(h-1,1,'~',w)
    win.addstr(1,1,"  <--- 300 iops max --->")
    win.border(0)

stdscr = curses.initscr()
curses.cbreak()
stdscr.keypad(1) 
#curses.start_color()
#curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLUE)
#curses.color_pair(1)
#stdscr.addstr(0,0, "RED ALERT!", curses.color_pair(1))
#stdscr.getch()

try:
    max_iops = 300
    begin_x = 0
    begin_y = 0
    height,width = stdscr.getmaxyx()
    win = curses.newwin(height, width, begin_y, begin_x)
    height,width = win.getmaxyx()

    draw_axes(win,height,width)
    #win.getch()

    base_line = height-1
    max_mag = height-10;
    for t in range(1, 100):
        data = get_data()
        for pt in data:
            mag = pt["mag"]
            bin = pt["bin"]
            if mag >= max_iops:
                mag = max_iops
            mag = (mag * max_mag) / max_iops
            #if mag >= max_mag:
            #    mag = max_mag
            if mag == 0:
                mag = 1
            row = base_line-mag; 
            col = bin; 
            win.vline(row, bin, 'x', mag)
            draw_axes(win,height,width)

        time.sleep(0.25)
        win.refresh()
        win.erase()
        height, width = win.getmaxyx()
        base_line = height-1
        max_mag = height-10
 
finally:
    win.getch()
    curses.nocbreak()
    stdscr.keypad(0)
    curses.echo()
    curses.endwin()
