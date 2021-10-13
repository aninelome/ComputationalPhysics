import os
import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
from mpl_toolkits import mplot3d

fontsize = 10
ticksize = 10



def analytic_f(x0=2, y0=0, z0=2, v0=0.1, total_time=100, dt=0.01):
    q = 1
    m = 40.078
    B0 = 96.5
    V0 = 9.65e8
    d = 1e4
    n = int(total_time/dt)
    t = np.linspace(0, total_time, n)
    omega_0 = q*B0/m;
    omega_z = np.sqrt((2*q*V0)/(m*d*d));
    omega_m = (omega_0-np.sqrt(omega_0*omega_0-2*omega_z*omega_z)/2)
    omega_p = (omega_0+np.sqrt(omega_0*omega_0-2*omega_z*omega_z)/2)
    A_p = (v0+omega_m*x0/(omega_m - omega_p))
    A_m = -(x0*omega_p+v0/(omega_m - omega_p))
    x = A_p*np.cos(omega_p*t) - A_m*np.cos(omega_m*t)
    y = -(A_p*np.sin(omega_p*t) + A_m*np.sin(omega_m*t))
    z = z0*np.cos(omega_z*t)
    return x, y, z, t



def main():

    r = pa.cube()
    v = pa.cube()
    t = pa.mat()

    r_without = pa.cube()
    v_without = pa.cube()




    r.load(f"position_with_interaction__.bin")
    v.load(f"velocity_with_interaction__.bin")


    r_without.load(f"position_without_interaction__.bin")
    v_without.load(f"velocity_without_interaction__.bin")

    t.load("time__.bin")

    r = np.array(r)
    v = np.array(v)
    t = np.array(t)

    r_without = np.array(r_without)
    v_without = np.array(v_without)

    r_list = [r, r_without]
    v_list = [v, v_without]

    # Analytic
    x_analytic, y_analytic, z_analytic, _ = analytic_f()
    plt.plot(x_analytic, y_analytic)
    plt.legend()
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)
    plt.title("Analytic solution")
    plt.show()

    # Single particle motion:
    #x1, y1, z1 = r[:, 0, 0], r[:, 1, 0], r[:, 2, 0]
    #v_x1, v_y1, v_z1 = v[:, 0, 0], v[:, 1, 0], v[:, 2, 0]
    #plt.plot(t, z1, label="Single particle movement, z1 against t")
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()


    # Two particles:
    #1: Motion in the xy-plane with and without particle interactions
    #count = 0
    #for r, v in zip(r_list, v_list):
    #    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    #    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #    if count == 0:
    #        for i in range(2):
    #            plt.plot(x[:,i], y[:,i], label=f"Particle {i}")
    #        plt.title("Two particles with interaction")
    #        plt.xlabel("x")
    #        plt.ylabel("y")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()

    #    if count == 1:
    #        for i in range(2):
    #            plt.plot(x[:,i], y[:,i], label=f"Particle {i}")
    #        plt.title("Two particles without interaction")
    #        plt.xlabel("x")
    #        plt.ylabel("y")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()
    #    count += 1


    #2: Phase space plots with and without interactions
    # x against v_x
    #plt.plot(x[:,0], v_x[:,0],"g", label=f"x against v_x, particle1, {interaction_label}") # Particle 1
    #plt.plot(x[:,1], v_x[:,1], "b", label=f"x against v_x, particle2, {interaction_label}") # Particle 2
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    # y against v_y
    #plt.plot(y[:,0], v_y[:,0],"g", label=f"y against v_y, particle1, {interaction_label}") # Particle 1
    #plt.plot(y[:,1], v_y[:,1], "b", label=f"y against v_y, particle2, {interaction_label}") # Particle 2
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    # z against v_z
    #plt.plot(z[:,0], v_z[:,0],"g", label=f"z against v_z, particle1, {interaction_label}") # Particle 1
    #plt.plot(z[:,1], v_z[:,1], "b", label=f"z against v_z, particle2, {interaction_label}") # Particle 2
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()

    #3: 3D plot of the trajectory of two particles with and without interactions
    #fig = plt.figure()
    #ax = plt.axes(projection='3d')
    #ax.plot3D(x[:,0], y[:,0], z[:,0], "g", label=f"particle1, {interaction_label}")
    #ax.plot3D(x[:,1], y[:,1], z[:,1], "b", label=f"particle2, {interaction_label}")
    #ax.set_xlabel('x')
    #ax.set_ylabel('y')
    #ax.set_zlabel('z')
    #ax.set_title(f'Two particles {interaction_label}')
    #ax.legend()
    #plt.show()


if __name__ == '__main__':
    main()
