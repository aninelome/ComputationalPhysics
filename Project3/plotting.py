import os
import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
from mpl_toolkits import mplot3d

fontsize = 10
ticksize = 10



def analytic_f(x0=1, y0=0, z0=1, v0=0.1, total_time=100, dt=0.01):
    n = int(total_time/dt)
    t = np.linspace(0, total_time, n)
    omega_0 = 2  #abs(q)*B0/m;
    omega_z = 1   #sqrt((2*abs(q)*V0)/(m*d*d));
    omega_m = (omega_0-np.sqrt(omega_0*omega_0-2*omega_z*omega_z)/2)
    omega_p = (omega_0+np.sqrt(omega_0*omega_0-2*omega_z*omega_z)/2)
    A_p = (v0+omega_m*x0/(omega_m - omega_p))
    A_m = -(x0*omega_p+v0/(omega_m - omega_p))
    x = A_p*np.cos(omega_p*t) - A_m*np.cos(omega_m*t)
    y = -(A_p*np.sin(omega_p*t) + A_m*np.sin(omega_m*t))
    return x, y



def main():
    r = pa.cube()
    v = pa.cube()
    t = pa.mat()

    r.load("position.bin")
    v.load("velocity.bin")
    t.load("time.bin")

    r = np.array(r)
    v = np.array(v)
    t = np.array(t)

    # Analytic
    x, y = analytic_f()
    #plt.plot(x, y)
    #plt.legend()
    #plt.show()

    # Sigle particle motion:
    x1, y1, z1 = r[:, 0, 0], r[:, 1, 0], r[:, 2, 0]
    v_x1, v_y1, v_z1 = v[:, 0, 0], v[:, 1, 0], v[:, 2, 0]
    #plt.plot(t, z1, label="Single particle movement, z1 against t")
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()


    # Two particles:
    #1: Motion in the xy-plane with and without particle interactions
    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #plt.plot(x1[0], y1[0], label="Two particles, x1 against y1, with particle interaction")
    # Without particle interaction???
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()


    #2: Phase space plots (with and without interactions!!)
    # x against v_x
    #plt.plot(x[:,0], v_x[:,0],"go--", label="x against v_x, particle1") # Particle 1
    #plt.plot(x[:,1], v_x[:,1], "bo", label="x against v_x, particle2") # Particle 2
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    # y against v_y
    #plt.plot(y[:,0], v_y[:,0],"go--", label="y against v_y, particle1") # Particle 1
    #plt.plot(y[:,1], v_y[:,1], "bo", label="y against v_y, particle2") # Particle 2
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    # z against v_z
    #plt.plot(z[:,0], v_z[:,0],"go--", label="z against v_z, particle1") # Particle 1
    #plt.plot(z[:,1], v_z[:,1], "bo", label="z against v_z, particle2") # Particle 2
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    #3: 3D plot of the trajectory of two particles with and without interactions
    #fig = plt.figure()
    #ax = plt.axes(projection='3d')
    #ax.plot()
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    #4: Graph showing the size of the relative error for five different values for dt

    #plt.plot()
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    #5: Computation estimating the error convergence rate for forward Euler and RK4
    #delta_max = np.max(np.abs(?))
    #sum = 0
    #for k in range(2,6):
    #    sum += (np.log10(delta_max[k]/delta_max[k-1]))/(np.log10(dt[k]/dt[k-1])
    #    r_err = (1/4)*sum

if __name__ == '__main__':
    main()
