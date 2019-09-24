#!/usr/bin/env python3

from __future__ import print_function
import matplotlib.pyplot as plt
import numpy as np

class Cross_Hair(object):
    def __init__(self, ax, fig, delx, dely):
        self.ax = ax
        self.fig = fig
        self.cross = dict()
        self.delx = delx
        self.dely = dely
        self.color = None
        self.fig.canvas.mpl_connect('key_press_event', self.my_key_press)
        self.rtxt = ax.text(0.7, 0.90, 'red', transform=ax.transAxes)
        self.gtxt = ax.text(0.7, 0.85, 'green', transform=ax.transAxes)
        self.btxt = ax.text(0.7, 0.80, 'blue', transform=ax.transAxes)

    def add(self, x, y, color):
        self.cross[color] = dict()
        self.cross[color]['color'] = color
        self.cross[color]['x'] = x
        self.cross[color]['y'] = y
        self.cross[color]['lx'] = self.ax.axhline(color=color)
        self.cross[color]['ly'] = self.ax.axvline(color=color)

        self.cross[color]['lx'].set_ydata(y) # set and draw the lines
        self.cross[color]['ly'].set_xdata(x)
        self.fig.canvas.draw()
        self.color = color
        # note the last line added is selected

    def select(self, color):
        self.color  = color
        print('select: ', color, self.x, self.y)

    def update_calcs(self):
        print('update calcs')
        self.rtxt.set_text('red:   x=%1.2f, y=%1.2f' % (self.cross['red']['x'], self.cross['red']['y']))
        self.gtxt.set_text('green: x=%1.2f, y=%1.2f' % (self.cross['green']['x'], self.cross['green']['y']))
        self.btxt.set_text('blue:  x=%1.2f, y=%1.2f' % (self.cross['blue']['x'], self.cross['blue']['y']))

    def my_key_press(self, event):
        if (self.color == None):
            return
        if event.key == 'left':
            self.cross[self.color]['x'] -= self.delx
        elif event.key == 'right':
            self.cross[self.color]['x'] += self.delx
        elif event.key == 'up':
            self.cross[self.color]['y'] += self.dely
        elif event.key == 'down':
            self.cross[self.color]['y'] -= self.dely
        elif event.key == 'r':
            self.select('red')
        elif event.key == 'g':
            self.select('green')
        elif event.key == 'b':
            self.select('blue')
#        elif event.key == 'C':
#            self.delta = .1
#        elif event.key == 'F':
#            self.delta = .01
        print('x,y', event.key, self.cross[self.color]['x'], self.cross[self.color]['y'])
        self.cross[self.color]['lx'].set_ydata(self.cross[self.color]['y'])
        self.cross[self.color]['ly'].set_xdata(self.cross[self.color]['x'])
        self.update_calcs()
        self.fig.canvas.draw()

if __name__ == '__main__':
    t = np.arange(0.0, 1.0, 0.01)
    p = np.sin(2*2*np.pi*t)
    q = np.sin(2*3*np.pi*t)
    r = np.sin(2*4*np.pi*t)

    fig2 = plt.figure()
    fig2.suptitle('mouse hover over figure or axes to trigger events')
    ax1 = fig2.add_subplot(111)

    ax1.plot(t, p)
    ax1.plot(t, q)
    ax1.plot(t, r)

    rc = Cross_Hair(ax1, fig2)
    rc.add(1,2,'red')
    rc.add(3,4,'green')
    rc.add(5,6,'blue')
    rc.select('green')

    plt.show()

