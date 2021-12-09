Simulation of a double-slit-in-a-box using the two-dimensional time-dependent Schrödinger equation 
---------------------------------------------------------------------------------------------------

In this project we solved the time dependent Schrödinger equation and simulated the resulting wave function numerically for a single particle through a double-slit.
To solve this numerically, we used the Crank-Nicolson method.
Files:

- functions.cpp
- functions.hpp
- main.cpp
- plotting.py

The file functions.cpp contains functions making matrices A and B required for the Crank-Nicolson approach, and solving the required matrix equations. We also make the potential and the initial wave function in this file.

In main.cpp we run the simluation and save the desired results to bins.

In plotting.py we read the bins created in main.cpp and plot the results.


## How to build and run the program
Windows: Build in: g++-10 -o main.exe main.cpp functions.cpp -std=c++11 -larmadillo -O3 Run: ./main.exe

Mac: Build in: g++ src/main.cpp src/functions.cpp -I include -o main.exe -larmadillo -std=c++11 -O3 Run: ./main.exe
