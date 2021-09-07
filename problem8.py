import os
import numpy as np
import matplotlib.pyplot as plt

def hentdata(filename1, filename2):
    x = []
    V_x = []
    U_x = []

    infile = open(filename1, "r")

    for line in infile:
        numbers = line.split()
        x.append(float(numbers[0]))
        V_x.append(float(numbers[1]))

    infile.close()
    infile = open(filename2, "r")

    for line in infile:
        numbers = line.split()
        U_x.append(float(numbers[1]))

    infile.close()

    X = np.array(x)
    U = np.array(U_x)
    V = np.array(V_x)
    delta = np.log10(np.abs(U-V))
    epsiloni = np.log10(np.abs((U-V)/U))

    plt.plot(X, delta, label = f"n = {n}")
    plt.plot(X, epsiloni, label = f"n = {n}")
    return

path = "./results/"
if not os.path.exists(path):
    os.makedirs(path)

plt.legend()
plt.title("Absolute error for different n")
plt.xlabel("x")
plt.ylabel("$\Delta_i$")
plt.savefig("delta_i.pdf")
plt.show()
hentdata("prob7_n_10.txt", "prob2_n_10.txt")
hentdata("prob7_n_100.txt", "prob2_n_100.txt")
hentdata("prob7_n_1000.txt", "prob2_n_1000.txt")
