// Main program for problem 5

#include "functions.hpp"

int main(){
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
  bool converged;
  double tol = 1e-10;
  jacobi_eigensolver(A6, R6, tol, eigenvalues, eigenvectors, maxiter, iterations, converged, k,l);
  eigenvalues.print();
  eigenvectors.print();
  return 0;
}
