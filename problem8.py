import os
import numpy as np
import matplotlib.pyplot as plt

def hentdata(filename1, filename2): #Henter ut x, u og v fra filer
    x = []
    V_x = []
    U_x = []
    RelativeError = []
    AbsError = []

    infile = open(filename1, "r")

    for line in infile:
        numbers = line.split()
        x.append(float(numbers[0]))
        V_x.append(float(numbers[1]))
        RelativeError.append(float(numbers[2]))
        AbsError.append(float(numbers[2]))


    infile.close()
    infile = open(filename2, "r")

    for line in infile:
        numbers = line.split()
        U_x.append(float(numbers[1]))

    infile.close()

    X = np.array(x)
    U = np.array(U_x)
    V = np.array(V_x)

    return X, U, V, RelativeError, AbsError

#Lager lister med filnavnene vi skal hente ut data fra
filename1 = ["prob7_n_10.txt", "prob7_n_100.txt", "prob7_n_1000.txt", "prob7_n_10000.txt", "prob7_n_100000.txt", "prob7_n_1000000.txt", "prob7_n_10000000.txt"]
filename2 = ["prob2_n_10.txt", "prob2_n_100.txt", "prob2_n_1000.txt", "prob2_n_10000.txt", "prob2_n_100000.txt", "prob2_n_1000000.txt", "prob2_n_10000000.txt"]


n_list = [10**i for i in range(1,8)]
"""
def Delta_i(U,V): #returnerer absolutt feil
    delta = np.log10(np.abs(U-V))
    return delta

def epsilon_i(U,V): #returnerer relativ feil
    epsilon = np.log10(np.abs((U-V)/U))
    return epsilon



#Regner ut og plotter absolutt feil for ulike n

for i in range (3):
    x, u, v, rel_error, abs_error = hentdata(filename1[i], filename2[i])
    x = x[1:-1]
    u = u[1:-1]
    v = v[1:-1]
    abs_error = abs_error[1:-1]
    plt.plot(x, abs_error, label = f"n = {n_list[i]}")


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
    x, u, v, rel_error, abs_error = hentdata(filename1[i], filename2[i])
    x = x[1:-1]
    u = u[1:-1]
    v = v[1:-1]
    rel_error = rel_error[1:-1]
    plt.plot(x, rel_error, label = f"n = {n_list[i]}")

#Fullfører plott med relativ feil
plt.legend()
plt.title("Relative error for different n")
plt.xlabel("x")
plt.ylabel("$\epsilon_i$")
plt.savefig(path+"epsilon_i.pdf")
plt.show()
"""

#Vil regne ut maksimum relativ feil for alle valg av n, opp til n = 10^7
epsilon_max = np.zeros(7)
for i in range(7):
    x, u, v, rel_error, abs_error = hentdata(filename1[i], filename2[i])
    x = x[1:-1]
    u = u[1:-1]
    v = v[1:-1]
    rel_error = rel_error[1:-1]
    epsilon_max[i] = np.max(rel_error)

#print(epsilon_max)

print(np.log10(np.array(n_list)))
print(np.log10(epsilon_max))
plt.plot(np.log10(np.array(n_list)), epsilon_max)
plt.scatter(np.log10(np.array(n_list)), epsilon_max, label="data")
plt.show()


    #with open("max_rel_error.txt", "w") as file:
        #file.write(f"{10**i}, {max(epsilon)}")


    #plt.plot(10**(i), max(epsilon))
#file.close()
#plt.show()
