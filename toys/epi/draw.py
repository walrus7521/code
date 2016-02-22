#!/usr/bin/python

# https://opentechschool.github.io/python-beginners/en/simple_drawing.html

#import turtle
#turtle.shape("turtle")
#turtle.forward(25)
#turtle.exitonclick()

import getopt
import argparse
from Tkinter import *
tk = Tk() 
canvas = Canvas( tk, width = 400, height = 400) 
canvas.pack() 

def MIN(a,b):
    if (a < b):
        return a
    else:
        return b

def MAX(a,b):
    if (a > b):
        return a
    else:
        return b
    
RED="#f50"
YELLOW="#fb0"
BLUE="#05f"
GREEN="#adff2f"

class rect:
    def __init__(self, x, y, width, height, color):
        self.x      = x
        self.y      = y
        self.width  = width
        self.height = height
        self.color  = color
        #self.draw()

    def draw(self, fill):
        x2 = self.x + self.width
        y2 = self.y + self.height 
        canvas.create_rectangle(self.x, self.y, x2, y2, outline=self.color, fill=fill)

def intersect(R, S):
    return ((R.x <= S.x + S.width)  and (R.x + R.width >= S.x) and
            (R.y <= S.y + S.height) and (R.y + R.height >= S.y))

def overlap(R, S, fill):
    x1 = MAX(R.x, S.x);
    x2 = MIN(R.x+R.width, S.x+S.width);
    y1 = MAX(R.y, S.y);
    y2 = MIN(R.y+R.height, S.y+S.height);
    r = rect(x1, y1, x2-x1, y2-y1, GREEN)
#r = rect(x1, y1, x2-x1, y2-y1, GREEN, fill="blue")
    r.draw("blue")


a = rect(40, 40, 100, 210, RED)
#b = rect(12,12,20,40, BLUE) 
b = rect(20, 20, 220, 220, BLUE)
#e = rect(70,100,80,80, RED)
#print "rect a and b intersect: %d" % (intersect(a,b))
a.draw("")
b.draw("")
if (intersect(a,b)):
    overlap(a,b, "blue")
#overlap(a, b)
#c = rect(20,140,110,110, BLUE)
#d = rect(110,20,120,120, RED)
#e = rect(70,100,80,80, RED)
tk.mainloop()

