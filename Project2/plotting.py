import os
import numpy as np
import matplotlib.pyplot as plt

def plot_eigenvectors(filename1, filename2):
    x = []
    vec1 = []
    vec2 = []
    vec3 = []

    x2 = []
    vec1_analytic = []
    vec2_analytic = []
    vec3_analytic = []

    infile1 = open(filename1, "r")

    for line in infile1:
        numbers = line.split()
        x.append(float(numbers[0]))
        vec1.append(float(numbers[1]))
        vec2.append(float(numbers[2]))
        vec3.append(float(numbers[3]))


    infile1.close()

    infile2 = open(filename2, "r")

    for line in infile2:
        numbers = line.split()
        x2.append(float(numbers[0]))
        vec1_analytic.append(float(numbers[1]))
        vec2_analytic.append(float(numbers[2]))
        vec3_analytic.append(float(numbers[3]))


    infile2.close()

    plt.plot(x,vec1, label="vec1")
    plt.plot(x,vec2, label="vec2")
    plt.plot(x,vec3, label="vec3")

    plt.plot(x2,vec1_analytic, label="vec1_analytic")
    plt.plot(x2,vec2_analytic, label="vec2_analytic")
    plt.plot(x2,vec3_analytic, label="vec3_analytic")

    plt.legend()

    plt.show()
    return

plot_eigenvectors("eigvecs_and_x_values_n10.txt", "analytical_eigvecs_n10.txt")

plot_eigenvectors("eigvecs_and_x_values_n100.txt", "analytical_eigvecs_n100.txt")

plot_eigenvectors("eigvecs_and_x_values_n50.txt", "analytical_eigvecs_n50.txt")
