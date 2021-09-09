import os
import numpy as np
import matplotlib.pyplot as plt

def hentdata(filename1, filename2): #Henter ut x, u og v fra filer
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

    return X, U, V


def Delta_i(U,V): #returnerer absolutt feil
    delta = np.log10(np.abs(U-V))
    return delta

def epsilon_i(U,V): #returnerer relativ feil
    epsilon = np.log10(np.abs((U-V)/U))
    return epsilon

#Lager lister med filnavnene vi skal hente ut data fra
filename1 = ["prob7_n_10.txt", "prob7_n_100.txt", "prob7_n_1000.txt"]
filename2 = ["prob2_n_10.txt", "prob2_n_100.txt", "prob2_n_1000.txt"]
n_list = [10,100,1000]

#Regner ut og plotter absolutt feil for ulike n
for i in range (3):
    x, u, v = hentdata(filename1[i], filename2[i])
    delta = Delta_i(u,v)
    plt.plot(x, delta, label = f"n = {n_list[i]}")

#Lager mappe til bildene
path = "./results/"
if not os.path.exists(path):
    os.makedirs(path)

#Fullfører plott med absolutt error
plt.legend()
plt.title("Absolute error for different n")
plt.xlabel("x")
plt.ylabel("$\Delta_i$")
plt.savefig(path+"delta_i.pdf")
plt.show()

#Regner ut og plotter absolutt feil for ulike n
for i in range (3):
    x, u, v = hentdata(filename1[i], filename2[i])
    epsilon = epsilon_i(u,v)
    plt.plot(x, epsilon, label = f"n = {n_list[i]}")

#Fullfører plott med relativ feil
plt.legend()
plt.title("Relative error for different n")
plt.xlabel("x")
plt.ylabel("$\epsilon_i$")
plt.savefig(path+"epsilon_i.pdf")
plt.show()
