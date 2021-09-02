# reads a data file and generates a plot

import numpy as np 
import matplotlib.pyplot as plt 

x = np.arange(0, 5, 0.1)
y = np.sin(x)
plt.plot(x, y)
plt.show()


infile = open("exact_solution.txt", "r")

x = []
U_x = []

for line in infile: 
    numbers = line.split()
    #numbers[0]: x, numbers[1]: U(x)
    x.append(numbers[0])
    U_x.append(numbers[1])

plt.title("Poisson??")
plt.plot(x, U_x)
plt.show()

infile.close()