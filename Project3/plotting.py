import os
import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa

fontsize = 10
ticksize = 10

"""
Function reading from file

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
"""

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


    # Single particle motion:
    x1, y1, z1 = r[:, 0, 0], r[:, 1, 0], r[:, 2, 0]
    v_x1, v_y1, v_z1 = v[:, 0, 0], v[:, 1, 0], v[:, 2, 0]

    # Two particles
    x, y, z = r[:, 0, :], r[:, 1, :], r[:, 2, :]
    v_x, v_y, v_z = v[:, 0, :], v[:, 1, :], v[:, 2, :]
    #print(x1)
    #print(v_x.shape)
    #print(x)
    #plot_a_against_b(t, z1, "Single particle movement, z1 against t")
    #plt.show()

    #plot_a_against_b(x1, y1, "Single particle movement, z1 against t")
    #plt.show()

    plt.plot(x[:,0], y[:,0], color = "r")
    plt.plot(x[:,1], y[:,1], color = "g")
    #plt.legend()
    plt.show()

    #plot_a_against_b(y, v_y, "Single particle movement, z1 against t")
    #plt.show()

    #plot_a_against_b(z, v_z, "Single particle movement, z1 against t")
    #plt.show()



if __name__ == '__main__':
    main()
