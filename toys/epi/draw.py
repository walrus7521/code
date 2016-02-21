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

def random_rectangle( x1, y1, width, height): 
    x2 = x1 + width
    y2 = y1 + height 
    canvas.create_rectangle( x1, y1, x2, y2)

def main():    
    random_rectangle(4, 4, 21, 22)
    tk.mainloop()

if __name__ == '__main__':
    main()

