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

RED="#f50"
YELLOW="#fb0"
BLUE="#05f"

class rect:
    def __init__(self, x, y, width, height, color):
        self.x      = x
        self.y      = y
        self.width  = width
        self.height = height
        self.color  = color
        self.draw()

    def draw(self):
        x2 = self.x + self.width
        y2 = self.y + self.height 
        canvas.create_rectangle(self.x, self.y, x2, y2,outline=self.color)

a = rect(40, 40, 100, 210, RED)
b = rect(20, 20, 220, 220, GREEN)
#c = rect(20,140,110,110, BLUE)
#d = rect(110,20,120,120, RED)
#e = rect(70,100,80,80, RED)
 
tk.mainloop()

