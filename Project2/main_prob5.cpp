// Main program for problem 5

#include "functions.hpp"

int main(){
  /*Ting som må fikses/ spm:
  - Hvorfor converged = true?
  */
  int N = 6;
  double n = N+2;
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
  maxiter = 10000;
  bool converged;
  double tol = 1e-10;
  jacobi_eigensolver(A6, R6, tol, eigenvalues, eigenvectors, maxiter, 0, converged, k,l);
  cout << "Eigenvalues" << endl;
  eigenvalues.print();
  cout << "Eigenvectors" << endl;
  eigenvectors.print();
  return 0;
}
