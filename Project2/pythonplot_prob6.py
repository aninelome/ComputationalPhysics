import numpy as np
import matplotlib.pyplot as plt
def plot_prob6(filename):
    N = np.loadtxt("plot_prob6.txt", usecols=0)
    it = np.loadtxt("plot_prob6.txt", usecols=1)
    plt.title("Number of transformations versus dimension of matrix")
    plt.xlabel("N")
    plt.ylabel("Number of iterations")
    plt.loglog(N, it)
    plt.loglog(N, it, "ro")
    plt.show()
return
#Finding the slope of the graph to find the scale between number of transformations and N
s = (np.log10(it[-1]) - np.log10(it[0]))/(np.log10(N[-1]) - np.log10(N[0]))
print(f"Scale = {s}")
