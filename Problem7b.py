import os
import numpy as np
import matplotlib.pyplot as plt

# Funksjon som plotter approksimasjoner til u(x)
def plotV(n, filename):

    infile = open(filename, "r")

    x = []
    V_x = []

    for line in infile:
        numbers = line.split()
        x.append(float(numbers[0]))
        V_x.append(float(numbers[1]))

    infile.close()

    plt.title("Comparing exact Poisson equation with approximation for different n values")
    plt.plot(x, V_x, label=f"n = {n}")
    plt.xlabel("x")
    plt.ylabel("U(x)")
    return


path = "./results/"
if not os.path.exists(path):
    os.makedirs(path)

infile = open("prob2_n_1000.txt", "r")

x = []
U_x = []

for line in infile:
    numbers = line.split()
    x.append(float(numbers[0]))
    U_x.append(float(numbers[1]))

infile.close()

plotV(10, "prob7_n_10.txt")
plotV(100, "prob7_n_100.txt")
plotV(1000, "prob7_n_1000.txt")
plt.plot(x, U_x, label="analytic solution")
plt.legend()
plt.savefig(path + "7bplot.pdf")
plt.show()
