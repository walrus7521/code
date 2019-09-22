#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt

# https://matplotlib.org/3.1.1/gallery/event_handling/keypress_demo.html
# https://matplotlib.org/2.0.1/examples/pylab_examples/cursor_demo.html

CrossHair_Select = 'g'
CrossHairAxis_Select = 'h'
X_Axis = 2
Y_Axis = 3

def press(event):
    global CrossHair_Select, CrossHairAxis_Select
    global X_Axis, Y_Axis
    #print('press', event.key)
    if event.key == 'r':
        print('cross red')
        CrossHair_Select = 'r'
    if event.key == 'g':
        print('cross green')
        CrossHair_Select = 'g'
    if event.key == 'b':
        print('cross blue')
        CrossHair_Select = 'b'
    if event.key == 'h':
        print('axis h')
        CrossHairAxis_Select = 'h'
    if event.key == 'v':
        print('axis v')
        CrossHairAxis_Select = 'v'
    if event.key == '?':
        print('selected: ', CrossHair_Select, CrossHairAxis_Select)
    if event.key == 'left':
        print('go left')
        X_Axis += 1
    if event.key == 'right':
        print('go right')
        X_Axis -= 1
    if event.key == 'up':
        print('go up')
        Y_Axis += 1
    if event.key == 'down':
        print('go down')
        Y_Axis -= 1
    print("axes: ", X_Axis, Y_Axis)

    ax.set_ydata(Y_Axis)
    ax.set_xdata(X_Axis)
     
#cross_hair(X_Axis, Y_Axis, plt, color='red') 
    fig.canvas.draw()
    sys.stdout.flush()
    return
    if event.key == 'x':
        visible = xl.get_visible()
        xl.set_visible(not visible)
        fig.canvas.draw()

def cross_hair(x, y, ax=None, **kwargs):
    if ax is None:
        ax = plt.gca()
    horiz = ax.axhline(y, **kwargs)
    vert = ax.axvline(x, **kwargs)
    return horiz, vert


# Fixing random state for reproducibility
np.random.seed(19680801)


fig, ax = plt.subplots()

fig.canvas.mpl_connect('key_press_event', press)

ax.plot(np.random.rand(12), np.random.rand(12), 'go')
xl = ax.set_xlabel('easy come, easy go')
ax.set_title('Press a key')
cross_hair(X_Axis, Y_Axis, plt, color='green') 
plt.show()

