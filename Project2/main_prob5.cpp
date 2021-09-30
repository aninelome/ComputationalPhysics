// Main program for problem 5

#include "functions.hpp"

int main(){
  int N = 6; //Dimension of matrix
  double n = N+1;
  double h = 1/n; //step size
  double a = -1/(h*h); //Elements in upper and lower diagonal
  double d = 2/(h*h); //Elements in diagonal
  mat A6 = make_tridiagonal(N, a, d); //makes a 6x6 tridiagonal matrix
  mat R6 = make_tridiagonal(N, 0, 1); // 6x6 identity matrix
  int k; //element indices of the largest off diagonal matrix elements
  int l; //element indices of the largest off diagonal matrix elements
  double maxA6 = max_offdiag_symmetric(A6, &k, &l);
  vec eigenvalues(N); //declear vector for eigenvalues
  mat eigenvectors(N,N);//declear matrix for eigenvectors 
  int maxiter, iterations;
  maxiter = 1000; //Maximum of iterations
  bool converged; //Declare the variable "converged" which is set to either True or False
  double tol = 1e-20; //Tolerance
  jacobi_eigensolver(A6, R6, tol, eigenvalues, eigenvectors, maxiter, 0, &converged, k,l);
  if (converged){    //If Jacobi solver has converged we print the eigenvalues and eigenvectors
    cout << "jacobi solver has converged" << endl;
    eigenvalues.print("Eignevlaues = ");
    eigenvectors.print("Eigenvectors = ");
  }
  else { //If jacobi solver didn't converge, we don't print the eigenvalues or eigenvectors
    cout << "Jacobi solver has not converged!!!!" << endl; //Print this error message instead
  }

  return 0;
}
