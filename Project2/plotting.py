import os
import numpy as np
import matplotlib.pyplot as plt

fontsize = 10
ticksize = 10

"""
Plotting number of transformations versus dimension of matrix
"""
def plot_prob6(filename):
    N = np.loadtxt("plot_prob6.txt", usecols=0)
    it = np.loadtxt("plot_prob6.txt", usecols=1)
    plt.title("Number of transformations versus dimension of matrix")
    plt.xlabel("N", size=12)
    plt.ylabel("Number of iterations", size=12)
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)
    plt.loglog(N, it)
    plt.loglog(N, it, "ro")
    plt.show()
    # Finding the slope of the graph to find the scale between number of transformations and N
    s = (np.log10(it[-1]) - np.log10(it[0])) / (np.log10(N[-1]) - np.log10(N[0]))
    print(f"Scale = {s}")
    return

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


"""
Function plotting the three eigenvectors corresponding to
the three lowest eigenvalues, and of the corresponding analytical
eigenvectors, plotted against corresponding positions x"""
def plot_eigenvectors2(filename1, filename2):
    eigvecs = {}
    eigvecs["approx"] = read_data(filename1)
    eigvecs["analytic"] = read_data(filename2)


    plt.title(
        "One-dimensional buckling beam affected by a force at \n the endpoint x = 1"
    )
    plt.xlabel("$x$", size=12)
    plt.ylabel("$v$", size=12)
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)

    keys = list(eigvecs["approx"].keys())
    x = eigvecs["approx"]["x"]
    for i in range(1, len(keys)):
        plt.plot(x, eigvecs["approx"][keys[i]], label=keys[i])

    keys = list(eigvecs["analytic"].keys())
    x = eigvecs["analytic"]["x"]
    for i in range(1, len(keys)):
        plt.plot(
            x, eigvecs["analytic"][keys[i]], label="analytic " + keys[i], linestyle="--"
        )

    plt.legend()
    plt.show()
    return


def main():
    # Problem 6
    plot_prob6("plot_prob6.txt")

    # Problem 7
    plot_eigenvectors2("eigvecs_and_x_values_n10.txt", "analytical_eigvecs_n10.txt")
    plot_eigenvectors2("eigvecs_and_x_values_n100.txt", "analytical_eigvecs_n100.txt")
    return


if __name__ == "__main__":
    main()
