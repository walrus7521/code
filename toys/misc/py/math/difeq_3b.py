#!/usr/bin/python2.7

import numpy as np
import matplotlib.pyplot as plt

# physical constants
g = 9.8; L = 2; mu = 0.0 #0.001

# initial conditions
theta0      = np.pi / 3 # 60 degrees
omega0      = 0 # No initial angular velocity
tau         = 0.01 # some time step
total_t     = 10 #seconds
nsteps      = int(total_t / tau)

def pendulum():
    # sim data
    thetas = np.empty(nsteps)
    omegas = np.empty(nsteps)
    times  = np.empty(nsteps)

    t = 0
    theta = theta0
    omega = omega0
    # start simulation
    for step in np.arange(0, nsteps):
        theta_old = theta
        # Solution to the difeq
        thetas[step] = theta
        omegas[step] = omega
        times[step]  = t

        # step values
        accel  = -mu * omega - (g/L) * np.sin(theta)
        theta += omega * tau
        omega += accel * tau
        t     += tau

        if theta * theta_old < 0:
            print('reversal')

        theta_old = theta

    # plots
    ax = plt.subplot(111, projection='polar')
    ax.plot(times, thetas, '-', times, omegas, '+')
    plt.title('phasors')
    plt.show()

    plt.plot(times, thetas, '+', times, omegas, 'o')
    plt.title('temporal')
    plt.xlabel('time')
    plt.show()

pendulum()

