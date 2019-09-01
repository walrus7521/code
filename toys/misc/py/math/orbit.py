#!/usr/bin/python2.7

# orbit - Program to compute the trajectory of a comet
#         using various numerical methods.

# Set up configuration options and special features
import numpy as np
import matplotlib.pyplot as plt

from rk4 import rk4

def gravrk(s, t, GM):
    """ Returns right-hand side of Kepler ODE;
        used by RK routines
        Inputs
          s   = State vector [r(1) r(2) v(1) v(2)]
          t   = Time (not used)
          GM  = Parameter G*M (gravitational const * solar mass)
        Outputs
          deriv = Derivatives [dr(1)/dt dr(2)/dt dv(1)/dt dv(2)/dt]
    """
    #* Compute acceleration
    r = np.array([s[0], s[1]]) # unravel the vector s into position and velocity
    v = np.array([s[2], s[3]])
    accel = -GM*r/np.linalg.norm(r)**3 # Gravitational acceleration

    #* Return derivatives 
    deriv = np.array([v[0], v[1], accel[0], accel[1]])
    return deriv

#* Set initial position velocity of the comet.
r0 = float(input('Enter initial radial distance (AU): '))
v0 = float(input('Enter initial tangential velocity (AU/yr): '))
r = np.array([r0, 0])
v = np.array([0, v0])
state = np.array([ r[0], r[1], v[0], v[1] ]) # used by R-K routines

#* Set the physical constants and other variables
GM = 4 * np.pi**2           # Grav. const. * Mass of Sun (au^3/yr^2)
mass = 1.0                  # mass of comet
adaptErr = 1.0e-3           # Error parameter used by adaptive RK
time = 0.0

#* Loop over desired number of steps with given time step and numerical method.
nStep = int(input('Enter number of steps: '))
tau = float(input('Enter time step (yr): '))
NumericalMethod = int(input('Choose method: 1) Euler; 2) Euler-Cromer; 3) RungeKutta; 4) Adaptive R-K: '))
rplot = np.empty(nStep)
thplot = np.empty(nStep)
tplot = np.empty(nStep)
kinetic = np.empty(nStep)
potential = np.empty(nStep)

for istep in range(nStep):
    #* Record position and energy for plotting
    rplot[istep] = np.linalg.norm(r)                # record position for polar plot
    thplot[istep] = np.arctan2(r[1], r[0])
    tplot[istep] = time
    kinetic[istep] = 0.5*mass*np.linalg.norm(v)**2  # record energies
    potential[istep] = - GM*mass/np.linalg.norm(r)

    #* Calculate new position and velocity using:
    if NumericalMethod == 1:    #* Euler method (3.11, 3.12)
        accel = -GM*r/np.linalg.norm(r)**3
        r = r + tau*v # Euler step
        v = v + tau*accel
        time = time + tau
    elif NumericalMethod == 2:  #* Euler-Cromer (3.13, 3.14)
        accel = -GM*r/np.linalg.norm(r)**3
        v = v + tau*accel
        r = r + tau*v # Euler-Cromer step
        time = time + tau
    elif NumericalMethod == 3:  #* 4th order Runga-Kutta (3.28, 3.29)
        state = rk4(state, time, tau, gravrk, GM)
        r = np.array([state[0], state[1]]) # unravel the vector s into position and velocity
        v = np.array([state[2], state[3]])
        time = time + tau
    else:                       #* Adaptive Runga-Kutta
        pass

    #* Test if the pendulum has passed through theta=0, if so, use time as period estimate.

#* Graph the trajectory of the comet.
ax = plt.subplot(111, projection='polar') # use polar plot
ax.plot(thplot, rplot, '+')
ax.set_title('Distance (AU)')
ax.grid(True)
plt.show()

#* Graph the energy of the comet versus time.
totalE = kinetic + potential # Total energy
plt.plot(tplot, kinetic, '-.',tplot,potential,'--',tplot,totalE,'-')
plt.legend(['Kinetic', 'Potential', 'Total'])
plt.xlabel('Time (yr)')
plt.ylabel(r'Energy ($m AU^2/yr^2$)')
plt.show()


