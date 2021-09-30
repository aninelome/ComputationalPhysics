# reads a data file and generates a plot
import os
import numpy as np
import matplotlib.pyplot as plt


infile = open("prob2_n_1000.txt", "r")

x = []
U_x = []

for line in infile:
    numbers = line.split()
    #numbers[0]: x, numbers[1]: U(x)
    x.append(float(numbers[0]))
    U_x.append(float(numbers[1]))

infile.close()
path = "./results/"
if not os.path.exists(path):
    os.makedirs(path)
plt.title("One-dimensional Poisson equation")
plt.plot(x, U_x, label = "Analytic solution")
plt.xlabel("x")
plt.ylabel("U(x)")
plt.legend()
plt.savefig(path+"PoissonPlot.pdf")
plt.show()
