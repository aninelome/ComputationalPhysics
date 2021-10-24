The Penning Trap
--------------------------------------------

In this project we make two classes, one for creating a particle and one for creating the Penning trap. We evaluate the movement of one or more particles inside the Penning trap, using both the Euler-method and the RK4-method in order to find the movement of the particle(s) when they are affected by an electric field and a magnetic field (and the force from the other particle(s)). 

Files:
- main.cpp
- particle.cpp
- particle.hpp
- penningtrap.cpp
- penningtrap.hpp
- plotting.py
- error.py
- testing.cpp


The file particle.cpp contains a class that stores the charge, mass, position and velocity of a single particle, and allows you to print these variables. 

The file penningtrap.cpp contains a class that stores the particle information given in particle.cpp, in addition to the magnetic field strength, the applied potential, and the characteristic dimension. This class evaluates the electric and magnetic fields, as well as the force due to the interaction among particles, and simulates the movement of one or more particles using either an RK4-method or Euler-method. 

There are two header files, particle.hpp and functions.hpp. In these, all the functions are decleared and the needed libraries are imported. 

In main.cpp we run the simulation and write the results to a file. 

In plotting.py we read the files created in main.cpp and plot the motion of one or more particles. 

In error.py we find the error between our numerical simulation and the analytical solution, and plot this. 

testing.cpp contains early tests that were made to ensure that the code worked while it was being written, and may not compile correctly anymore. 



How to build and run the main-functions
----------------------------------------
Windows: 
Build in: g++ src/particle.cpp src/penningtrap.cpp main.cpp -I include -o main.exe -larmadillo -Ofast
Run: ./main.exe

Mac: 
Build in: g++ src/particle.cpp src/penningtrap.cpp main.cpp -I include -o main.exe -larmadillo -Ofast -std=c++11
Run: ./main.exe
