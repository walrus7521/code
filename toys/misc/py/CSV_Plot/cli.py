from __future__ import print_function
import matplotlib.pyplot as plt
import numpy as np
import key_curs

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

rc = key_curs.Cross_Hair(ax1, fig2, 0.1, 0.1)
rc.add(.1,-.8,'red')
rc.add(.3,-.4,'green')
rc.add(.5, .3,'blue')
#rc.select('red')
#rc.select('green')
#rc.select('blue')

plt.show()

