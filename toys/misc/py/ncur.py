#!/usr/bin/python

# https://docs.python.org/2/howto/curses.html

import curses
stdscr = curses.initscr()
curses.noecho()
curses.cbreak()
stdscr.keypad(1)

while 1:
    stdscr.addstr(0, 0, "Current mode: Typing mode",
              curses.A_REVERSE)
    stdscr.refresh()


curses.nocbreak(); stdscr.keypad(0); curses.echo()
curses.endwin()


