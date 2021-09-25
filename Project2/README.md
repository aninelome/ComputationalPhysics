Implementation of the Jacobi rotation method
--------------------------------------------

In this project we implement the Jacobi rotation method and use it to find 
the eigenvalues and eigenvectors of a symmetric, tridiagonal matrix A. We also 
compare the solutions with solutions found by armadillo and an analytical formula.

Files:
- functions.cpp
- functions.hpp
- main_prob3.cpp
- main_prob4.cpp
- main_prob5.cpp
- main_prob6.cpp
- main_prob7.cpp
- plotting.py
- testing.cpp


The file functions.cpp contains all the functions we ues in all the main-files.

Our header file is named functions.hpp. This is where we declare all our 
functions and include all the libraries we need.

In main_prob3.cpp we find the eigenvalues and eigenvectors of A by using armadillo
and the analytical forumla. 

In main_prob4.cpp we identify the largest off-diagonal element in a test-matrix. 

In main_prob5.cpp we implement the Jacobi rotation method and find the eigenvalues
and eigenvectors of A. 

In main_prob6.cpp we estimate the number of required transformations scale with 
the matrix size N for the code when solving Ax = b.

In main_prob7.cpp we use our Jacobi code for a discretization of x with n steps, 
and write the eigenvectors corresponding to the three lowest eigenvalues to a file. 

In plotting.py we read the files created in main_prob6.cpp and main_prob7.cpp and plot 
the eigenvectors. 

In testing.cpp we test that a function from functions.cpp works as intended. 



How to build and run the main-functions
----------------------------------------

Build in: g++ functions.cpp functions.hpp main_probN.cpp -o main.exe -larmadillo
Run: ./main.exe
