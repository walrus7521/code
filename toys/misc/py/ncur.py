#!/usr/bin/env python3

# https://docs.python.org/2/howto/curses.html

import curses
import time

def main(stdscr):
    curses.curs_set(0)
    h, w = stdscr.getmaxyx()
    text = "Hello, world"
    x = w//2 - len(text)//2
    y = h // 2
    stdscr.addstr(y, x, text, curses.A_REVERSE)
    stdscr.refresh()
    time.sleep(3)


curses.wrapper(main)
