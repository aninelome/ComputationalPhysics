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


How to build and run the main-functions
----------------------------------------

Build in linux: g++ functions.cpp functions.hpp main_probN.cpp -o main.exe -larmadillo
Build in IOS: 
Run: ./main.exe
