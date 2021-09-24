#include <iostream> // input and output
#include <fstream>
#include <math.h>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;
// Functions in functions.cpp:


/* Function that creates a N*N (first arg) tridiagonal matrix
with sub- and superdiagonal elements a (second arg),
and maindiagonal elements d (third arg) */
mat make_tridiagonal(int N, double a, double d);


// Using armadillo to find eigenvalues and eigenvectors
void solve_eig_prob(mat A, vec* eigval, mat* eigvec);


//Finding eiegnvalues and eigenvectors with the analytical formula
void analytic_eigprob(int N, double a, double d, vec* lambda, mat* v);


// Function making example matrix for problem 4b)
mat mat_make_test_A(int N);


/* Function that identifies the largest off-diagonal element in the matrix (assume symmetric matrix)
then writes the matrix indices for this element to the two integer references
then returns the value of this matrix element. */
double max_offdiag_symmetric(mat A, int* k, int* l);


// Function that implements one rotation in the Jacobi rotation method.
void jacobi_rotate(mat& A, mat& R, int k, int l, double tol);


/* Function that uses jacobi_rotate to solve an eigenvalue problem with the Jacobi
rotation method. The function checks that all the nondiagonal elements of the matrix 
is less than a tolerance you give as an input. It also stops when the number of
iterations gets bigger than the variable maxiter which you give as an inputargument.*/
int jacobi_eigensolver(mat& A, mat& R, double tol, vec& eigenvalues, mat& eigenvectors,
const int maxiter, int iterations, bool *converged, int k, int l);


// Tests in testing.cpp:

// Test for max_offdiag_symmetric()
void test_max_offdiag();
