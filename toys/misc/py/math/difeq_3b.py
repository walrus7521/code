#!/usr/bin/python2.7

import numpy as np
import matplotlib.pyplot as plt


# physical constants
g = 9.8
L = 2
mu = 0.1

# initial conditions
THETA_0 = np.pi / 3 # 60 degrees
THETA_DOT_0 = 0 # No initial angular velocity

# definition of ODE
def get_theta_double_dot(theta, theta_dot):
    return -mu * theta_dot - (g / L) * np.sin(theta)


# Solution to the difeq
def theta(t):
    data = dict()
    # initial changing values
    theta = THETA_0
    theta_dot = THETA_DOT_0
    delta_t = 0.01 # some time step
    for time in np.arange(0, t, delta_t):
        theta_double_dot = get_theta_double_dot(
                theta, theta_dot
                )
        theta += theta_dot * delta_t
        theta_dot += theta_double_dot * delta_t
    data['th'] = theta
    data['td'] = theta_dot
    return data

# start simulation
time = 0
delta_t = 0.01
total_t = 10
nsteps = int(total_t / delta_t)

thetas = np.empty(nsteps)
theta_dots = np.empty(nsteps)
times  = np.empty(nsteps)

for step in np.arange(0, nsteps):
    data = theta(step * delta_t)
    thetas[step] = data['th']
    theta_dots[step] = data['td']
    times[step] = step * delta_t

plt.plot(thetas, theta_dots)
plt.show()

