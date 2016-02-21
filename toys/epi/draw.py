#!/usr/bin/python

# https://opentechschool.github.io/python-beginners/en/simple_drawing.html

#import turtle
#turtle.shape("turtle")
#turtle.forward(25)
#turtle.exitonclick()


from Tkinter import *

tk = Tk() 
canvas = Canvas( tk, width = 400, height = 400) 
canvas.pack() 
def random_rectangle( width, height): 
    x1 = 4 
    y1 = 4 
    x2 = x1 + width
    y2 = y1 + height 
    canvas.create_rectangle( x1, y1, x2, y2)


random_rectangle(21, 22)
