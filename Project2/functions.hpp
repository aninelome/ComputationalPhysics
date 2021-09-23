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
mat make_tridiagonal(int , double , double);

// using armadillo to find eigenvalues and eigenvectors
void solve_eig_prob(mat , vec* , mat* );

//Finding eiegnvalues and eigenvectors with the analytical formula
void analytic_eigprob(int , double , double);

// Function making example matrix for problem 4b)
mat mat_make_test_A(int );


/* function that identifies the largest off-diagonal element in the matrix (assume symmetric matrix)
then writes the matrix indices for this element to the two integer references
then returns the value of this matrix element. */
double max_offdiag_symmetric(mat , int* , int* );

//
void jacobi_rotate(mat& ,mat& , int , int , double);

//
void jacobi_eigensolver(mat& ,mat& , double, vec& , mat& , const int, int, bool, int, int);


// Tests:

// Test for max_offdiag_symmetric()
void test_max_offdiag();
