// Main program for problem 5

#include "functions.hpp"

int main(){
  /*Ting som må fikses/ spm:
  - Hvorfor converged = true?
  */
  int N = 6;
  double n = N+1;
  double h = 1/n;
  double a = -1/(h*h);
  double d = 2/(h*h);
  mat A6 = make_tridiagonal(N, a, d);
  mat R6 = make_tridiagonal(N, 0, 1);
  int k;
  int l;
  double maxA6 = max_offdiag_symmetric(A6, &k, &l);
  
  vec eigenvalues(N);
  mat eigenvectors(N,N);
  int maxiter, iterations;
  maxiter = 1000;
  bool converged;
  double tol = 1e-20;
  jacobi_eigensolver(A6, R6, tol, eigenvalues, eigenvectors, maxiter, 0, &converged, k,l);
  if (converged){
    cout << "jacobi solver has converged" << endl;
    eigenvalues.print("Eignevlaues = ");
    eigenvectors.print("Eigenvectors = ");
  }
  else {
    cout << "Jacobi solver has not converged!!!!" << endl;
  }

  return 0;
}
