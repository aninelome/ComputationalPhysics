import os
import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
from mpl_toolkits import mplot3d

fontsize = 10
ticksize = 10


# Function computing the position analytically
def analytic_f(x0=2, y0=0, z0=2, v0=0.1, total_time=100, dt=0.01):
    q = 1
    m = 40.078
    B0 = 96.5
    V0 = 9.65e8
    d = 1e4
    n = int(total_time/dt)
    t = np.linspace(0, total_time, n)
    omega_0 = q*B0/m
    omega_z = np.sqrt((2*q*V0)/(m*d*d))
    omega_m = (omega_0-np.sqrt(omega_0*omega_0-2*omega_z*omega_z)/2)
    omega_p = (omega_0+np.sqrt(omega_0*omega_0-2*omega_z*omega_z)/2)
    A_p = (v0+omega_m*x0/(omega_m - omega_p))
    A_m = -(x0*omega_p+v0/(omega_m - omega_p))
    x = A_p*np.cos(omega_p*t) - A_m*np.cos(omega_m*t)
    y = -(A_p*np.sin(omega_p*t) + A_m*np.sin(omega_m*t))
    z = z0*np.cos(omega_z*t)
    return x, y, z, t




def main():
    ## Get the position, velocity and time vectors from penningtrap.cpp,
    ## both in the case with interactions and without
    #r = pa.cube()
    #v = pa.cube()
    #t = pa.mat()

    #r_without = pa.cube()
    #v_without = pa.cube()

    #r.load(f"position_with_interaction__.bin")
    #v.load(f"velocity_with_interaction__.bin")

    #r_without.load(f"position_without_interaction__.bin")
    #v_without.load(f"velocity_without_interaction__.bin")

    #t.load("time__.bin")

    #r = np.array(r)
    #v = np.array(v)
    #t = np.array(t)

    #r_without = np.array(r_without)
    #v_without = np.array(v_without)

    #r_list = [r, r_without]
    #v_list = [v, v_without]



    ##Analytic
    #x_analytic, y_analytic, z_analytic, t_ = analytic_f()
    #plt.plot(x_analytic, y_analytic)
    #plt.legend()
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.xlabel("x")
    #plt.ylabel("y")
    #plt.title("Analytic solution")
    #plt.show()

    #plt.plot(t_, z_analytic)
    #plt.legend()
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.xlabel("t")
    #plt.ylabel("z")
    #plt.title("Analytic solution")
    #plt.show()



    ## Single particle motion:
    #x1, y1, z1 = r[:, 0, 0], r[:, 1, 0], r[:, 2, 0]
    #v_x1, v_y1, v_z1 = v[:, 0, 0], v[:, 1, 0], v[:, 2, 0]
    #plt.plot(x1, y1)
    #plt.show()
    #plt.plot(t, z1, label="Single particle movement, z1 against t")
    #plt.xticks(size=ticksize)
    #plt.yticks(size=ticksize)
    #plt.legend()
    #plt.show()


    ## Two particles:

    ##1: Motion in the xy-plane with and without particle interactions
    #count = 0
    #for r, v in zip(r_list, v_list):
    #    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    #    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #    if count == 0:
    #        for i in range(2):
    #           plt.plot(x[:,i], y[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles with interaction")
    #        plt.xlabel("x")
    #        plt.ylabel("y")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()

    #    if count == 1:
    #        for i in range(2):
    #           plt.plot(x[:,i], y[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles without interaction")
    #        plt.xlabel("x")
    #        plt.ylabel("y")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()
    #    count += 1


    ##2: Phase space plots with and without interaction
    ##x against v_x
    #count = 0
    #for r, v in zip(r_list, v_list):
    #    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    #    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #    if count == 0:
    #        for i in range(2):
    #           plt.plot(x[:,i], v_x[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles with interaction")
    #        plt.xlabel("x")
    #        plt.ylabel("v_x")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()

    #    if count == 1:
    #        for i in range(2):
    #           plt.plot(x[:,i], v_x[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles without interaction")
    #        plt.xlabel("x")
    #        plt.ylabel("v_x")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()
    #    count += 1

    ##y against v_y
    #count = 0
    #for r, v in zip(r_list, v_list):
    #    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    #    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #    if count == 0:
    #        for i in range(2):
    #           plt.plot(y[:,i], v_y[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles with interaction")
    #        plt.xlabel("y")
    #        plt.ylabel("v_y")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()

    #    if count == 1:
    #        for i in range(2):
    #           plt.plot(y[:,i], v_y[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles without interaction")
    #        plt.xlabel("y")
    #        plt.ylabel("v_y")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()
    #    count += 1

    ##z against v_z
    #count = 0
    #for r, v in zip(r_list, v_list):
    #    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    #    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #    if count == 0:
    #        for i in range(2):
    #           plt.plot(z[:,i], v_z[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles with interaction")
    #        plt.xlabel("z")
    #        plt.ylabel("v_z")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()

    #    if count == 1:
    #        for i in range(2):
    #           plt.plot(z[:,i], v_z[:,i], label=f"Particle {i+1}")
    #        plt.title("Two particles without interaction")
    #        plt.xlabel("z")
    #        plt.ylabel("v_z")
    #        plt.xticks(size=ticksize)
    #        plt.yticks(size=ticksize)
    #        plt.legend()
    #        plt.show()
    #    count += 1



    ##3: 3D plot of the trajectory of two particles with and without interactions
    #count = 0
    #for r, v in zip(r_list, v_list):
    #    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    #    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #    if count == 0:
    #        fig = plt.figure()
    #        ax = plt.axes(projection='3d')
    #        ax.plot3D(x[:,0], y[:,0], z[:,0], "g", label="Particle 1")
    #        ax.plot3D(x[:,1], y[:,1], z[:,1], "b", label="Particle 2")
    #        ax.set_xlabel('x')
    #        ax.set_ylabel('y')
    #        ax.set_zlabel('z')
    #        ax.set_title(f'Two particles with interactions')
    #        ax.legend()
    #        plt.show()

    #    if count == 1:
    #        fig = plt.figure()
    #        ax = plt.axes(projection='3d')
    #        ax.plot3D(x[:,0], y[:,0], z[:,0], "g", label="Particle 1")
    #        ax.plot3D(x[:,1], y[:,1], z[:,1], "b", label="Particle 2")
    #        ax.set_xlabel('x')
    #        ax.set_ylabel('y')
    #        ax.set_zlabel('z')
    #        ax.set_title(f'Two particles without interactions')
    #        ax.legend()
    #        plt.show()
    #    count += 1



    # Want to plot a graph that shows the fraction of particles that are still trapped after
    # 500 microseconds as a function of the applied angular frequency omega_v
    # Read number of remaining particles from file:

    """
    Function reading from file
    """
    def read_data(filename):
        with open(filename, "r") as infile:
            keys = infile.readline().split()
            d = {key: [] for key in keys}
            lines = infile.readlines()
            for line in lines:
                vals = line.split()
                for i in range(len(keys)):
                    d[keys[i]].append(float(vals[i]))
        return d

    #dictionary containing omega_v values and number of remaining perticles in the trap when amplitude = 0.1
    f_list = ["0.100000", "0.400000", "0.700000"]
    for f in f_list:
        d = read_data(f"remaining_particles_f:{f}.txt")
        print(d)
        plt.plot(d["omega_v"], d["N"], label=f"f={f}")

    plt.title("Remaining particles in trap for different amplitudes f")
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)
    plt.xlabel(f"$\ omega_v [MHz]$")
    plt.ylabel("N")
    plt.legend()
    plt.show()



if __name__ == '__main__':
    main()
