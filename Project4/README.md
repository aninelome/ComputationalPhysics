Markov Chain Monte Carlo simulation for Ferromagnets using the Ising model
-------------------------------------------------------------------------------------

In this project we make one class, which simulates the ferromagnet modelled as the Ising model using the Metropolis-Hastings algorithm.

Files:

- isingmodel.cpp
- isingmodel.hpp
- main.cpp
- plotting.py
- test.cpp

The file isingmodel.cpp contains the class Ising model, which updates the expectation values for the energy and absolute magnetization per spin as well as the susceptibility and the heat capacity.

In main.cpp we run the Ising model simulation and write the desired results to bins.

In plotting.py we read the bins created in main.cpp and plot the results.

In test.cpp we check the analytical desired values with lattice size 2 against numerical calculations. The file contains early tests that were made to ensure that the code worked while it was being written, and may not compile correctly anymore.

## How to build and run the program
Windows: Build in: g++-10 -o main.exe main.cpp isingmodel.cpp -std=c++11 -fopenmp -larmadillo -O3 Run: ./main.exe

Mac: Build in: g++ src/main.cpp src/isingmodel.cpp -Xpreprocessor -fopenmp -I include -o main.exe -larmadillo -std=c++11 -O3 Run: ./main.exe
