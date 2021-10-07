import os
import numpy as np
import matplotlib.pyplot as plt

fontsize = 10
ticksize = 10

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

def plot_a_against_b(dict, a, b, label):
    a = dict[a]
    b = dict[b]
    plt.plot(a, b, label = label)
    plt.xlabel(f"{a}", size=12)
    plt.ylabel(f"{b}", size=12)
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)




def main():
    RK4 = read_data("single_particle_movement_RK4.txt")
    plot_z_against_t(RK4, z, t, f"Sigle particle movement, {z} against {t}")
    plt.show()








if __name__ == '__main__':
    main()
