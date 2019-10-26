#!/usr/bin/python2.7

# pendul - Program to compute the time evolution of a simple
#          pendulum using using the Euler or Verlet method.

# Set up configuration options and special features
import numpy as np
import matplotlib.pyplot as plt

#* Select the numerical method to use: Euler or Verlet
NumericalMethod = int(input('Choose a numerical method (1: Euler; 2: Verlet): '))

#* Set initial position theta0 and velocity omega = 0 of the pedulum.
theta0 = float(input('Enter initial angle (in degrees): '))
theta = theta0 * np.pi / 180    # convert angle to radians
omega = 0.0                     # set initial velocity

#* Set the physical constants and other variables
g_over_L = 1.0                  # The constant g/L
time = 0.0                      # Initial time
irev = 0                        # used to count number of reversals
tau = float(input('Enter time step: '))

#* Take one backward step and start the Verlet (Eqn 2.60)
accel = -g_over_L * np.sin(theta)   # Gravitational acceleration
theta_old = theta - omega*tau + 0.5*accel*tau**2

#* Loop over desired number of steps with given time step and numerical method.
nstep = int(input('Enter number of time steps: '))
t_plot = np.empty(nstep)
th_plot = np.empty(nstep)
period = np.empty(nstep)
for istep in range(nstep):
    #* Record angle and time for plotting
    t_plot[istep] = time
    th_plot[istep] = theta * 180 / np.pi    # convert angle to degrees
    time = time + tau

    #* Compute new position and velocity using Euler or Verlet.
    accel = -g_over_L * np.sin(theta)       # Gravitational acceleration
    if NumericalMethod == 1:                # Euler
        theta_old = theta                   # save previous angle
        theta = theta + tau * omega         # Euler method
        omega = omega + tau * accel
    else:
        theta_new = 2*theta - theta_old + tau**2 * accel
        theta_old = theta                   # Verlet method
        theta = theta_new

    #* Test if the pendulum has passed through theta=0, if so, use time as period estimate.
    if theta*theta_old < 0:                 # test position for sign change
        print('Turning point at time t = ', time)
        if irev == 0:                       # first change
            time_old = time                 # just record the time
        else:
            period[irev-1] = 2*(time - time_old)
            time_old = time
        irev = irev + 1

#* Estimate period of oscilation, including error bar.
nPeriod = irev - 1                          # number times period was measured
AvePeriod = np.mean(period[0:nPeriod])
ErrorBar = np.std(period[0:nPeriod]) / np.sqrt(nPeriod)
print('Average period = ', AvePeriod, ' +/- ', ErrorBar)

#* Graph the oscillations as theta vs time.
plt.plot(t_plot, th_plot, '+')
plt.xlabel('Time')
plt.ylabel(r'$\theta$ (degrees)')
plt.show()


