#include <iostream> // input and output
#include <fstream>
#include <math.h>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

// Function that creates a N*N (first arg) tridiagonal matrix
// with sub- and superdiagonal elements a (second arg),
// and maindiagonal elements d (third arg)
mat make_tridiagonal(int N, double a, double d);

// using armadillo to find eigenvalues and eigenvectors
void solve_eig_prob(mat A, vec* eigval, mat* eigvec);

//Finding eiegnvalues and eigenvectors with the analytical formula
void analytic_eigprob(int N, double a, double d, vec* lambda, mat* v);

// Function making example matrix for problem 4b)
mat mat_make_test_A(int N);


/* function that identifies the largest off-diagonal element in the matrix (assume symmetric matrix)
then writes the matrix indices for this element to the two integer references
then returns the value of this matrix element. */
double max_offdiag_symmetric(mat A, int* k, int* l);

//
void jacobi_rotate(mat& A, mat& R, int k, int l, double tol);

//
int jacobi_eigensolver(mat& A, mat& R, double tol, vec& eigenvalues, mat& eigenvectors,
const int maxiter, int iterations, bool converged, int k, int l);


// Tests:

// Test for max_offdiag_symmetric()
void test_max_offdiag();
