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


def plot_a_against_b(a, b, label):
    plt.plot(a, b, label = label)
    #plt.xlabel(f"{a}", size=12)
    #plt.ylabel(f"{b}", size=12)
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)
    plt.axis("equal")


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

    # Sigle particle motion:
    x1, y1, z1 = r[:, 0, 0], r[:, 1, 0], r[:, 2, 0]
    print(r.size)
    print(x1.size)
    print(y1.size)
    print(t)

    print(t.size)

    v_x1, v_y1, v_z1 = v[:, 0, 0], v[:, 1, 0], v[:, 2, 0]


    plot_a_against_b(t, z1, "Sigle particle movement, z1 against t")
    plt.show()

    plot_a_against_b(x1, y1, "Sigle particle movement, z1 against t")

    plt.show()



if __name__ == '__main__':
    main()
