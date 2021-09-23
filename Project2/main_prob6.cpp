// Main program for problem 6

#include "functions.hpp"

int main(){
  int N = [10, 50, 100];
  double n = N+1;
  double h = 1/n;
  double a = -1/(h*h);
  double d = 2/(h*h);
  mat A = make_tridiagonal(N, a, d);
  mat R = make_tridiagonal(N, 0, 1);
  int k;
  int l;
  double maxA6 = max_offdiag_symmetric(A, &k, &l);
  vec eigenvalues(N);
  mat eigenvectors(N,N);
  int maxiter, iterations;
  maxiter = 1000000;
  bool converged;
  double tol = 1e-10;
  jacobi_eigensolver(A, R, tol, eigenvalues, eigenvectors, maxiter, 0, converged, k,l);
  cout << "Eigenvalues" << endl;
  eigenvalues.print();
  cout << "Eigenvectors" << endl;
  eigenvectors.print();
  return 0;
}
