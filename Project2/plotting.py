import os
import numpy as np
import matplotlib.pyplot as plt

def plot_eigenvectors(filename1, filename2):
    x = []
    eig_vec1 = []
    eig_vec2 = []
    eig_vec3 = []

    x2 = []
    eig_vec1_analytic = []
    eig_vec2_analytic = []
    eig_vec3_analytic = []

    infile1 = open(filename1, "r")

    for line in infile1:
        numbers = line.split()
        x.append(float(numbers[0]))
        eig_vec1.append(float(numbers[1]))
        eig_vec2.append(float(numbers[2]))
        eig_vec3.append(float(numbers[3]))


    infile1.close()

    infile2 = open(filename2, "r")

    for line in infile2:
        numbers = line.split()
        x2.append(float(numbers[0]))
        eig_vec1_analytic.append(float(numbers[1]))
        eig_vec2_analytic.append(float(numbers[2]))
        eig_vec3_analytic.append(float(numbers[3]))


    infile2.close()

    fontsize = 10
    ticksize = 10
    plt.title("One-dimensional buckling beam affected by a force at \n the endpoint x = 1")
    plt.xlabel("x")
    plt.ylabel("v")
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)
    plt.plot(x,eig_vec1, label="Eigenvector1")
    plt.plot(x,eig_vec2, label="Eigenvector2")
    plt.plot(x,eig_vec3, label="Eigenvector3")

    plt.plot(x2,eig_vec1_analytic, label="Eigenvector1_analytic", linestyle= "--")
    plt.plot(x2,eig_vec2_analytic, label="Eigenvector2_analytic", linestyle= "--")
    plt.plot(x2,eig_vec3_analytic, label="Eigenvector3_analytic", linestyle= "--")

    plt.legend()

    plt.show()
    return

plot_eigenvectors("eigvecs_and_x_values_n10.txt", "analytical_eigvecs_n10.txt")
plot_eigenvectors("eigvecs_and_x_values_n100.txt", "analytical_eigvecs_n100.txt")
