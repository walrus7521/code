#!/usr/bin/python2.7

import numpy as np
import matplotlib.pyplot as plt

# physical constants
g = 9.8; L = 2; mu = 0.1 #0.001

# initial conditions
theta0      = np.pi / 3 # 60 degrees
omega0      = 0 # No initial angular velocity
tau         = 0.01 # some time step
total_t     = 10 #seconds
nsteps      = int(total_t / tau)
irev        = 0 # reversals

# sim data
thetas  = np.empty(nsteps); omegas  = np.empty(nsteps)
times   = np.empty(nsteps); periods = np.empty(nsteps)

time   = 0; period = 0
theta  = theta0; omega  = omega0

# start simulation
for step in np.arange(0, nsteps):
    theta_old = theta
    # Solution to the difeq
    thetas[step] = theta
    omegas[step] = omega
    times[step]  = time

    # step values
    accel  = -mu * omega - (g/L) * np.sin(theta)
    theta += omega * tau
    omega += accel * tau
    time  += tau

    # reversals
    if theta * theta_old < 0:
         if irev == 0:
            period = time
         else:
            periods[irev-1] = 2*(time - period)
            period = time
         irev += 1
            
n_periods = irev - 1
avg_period = np.mean(periods[0:n_periods])
error = np.std(periods[0:n_periods])
print('avg per: ', avg_period, ' error: +/- ', error)

# plots
ax = plt.subplot(111, projection='polar')
#ax.plot(times, thetas, '-', times, omegas, '+')
ax.plot(thetas, omegas)
plt.title('phasors')
plt.show()

plt.plot(times, thetas, '+', times, omegas, 'o')
plt.title('temporal'); plt.xlabel('time')
plt.grid()
plt.show()

