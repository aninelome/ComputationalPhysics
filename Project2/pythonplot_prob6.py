import numpy as np
import matplotlib.pyplot as plt

def plot_N_it(filename):
    N = np.loadtxt("plot_prob6.txt", usecols=0)
    it = np.loadtxt("plot_prob6.txt", usecols=1)
    plt.title("Problem 6")
    plt.xlabel("N")
    plt.ylabel("Number of iterations")
    plt.loglog(N, it)
    plt.loglog(N, it, "ro")
    plt.show()
    #Finding the slope of the graph to find the transformation scale
    k = (np.log10(it[-1]) - np.log10(it[0]))/(np.log10(N[-1]) - np.log10(N[0]))
    print(k)
    return
plot_N_it("plot_prob6.txt")
