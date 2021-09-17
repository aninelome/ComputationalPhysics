// Main program for problem 5

#include "functions.hpp"

int main(){
  // int N = 6;
  int N = 4;
  double n = N+1;
  double h = 1/n;
  double a = -1/(h*h);
  double d = 2/(h*h);
  // cout << "a=" << a << endl;
  // mat A6 = make_tridiagonal(N, a, d);
  // cout << "A6= " << A6 << endl;
  // mat R6 = make_tridiagonal(N, 0, 1);
  mat A4 = mat_make_test_A(4);
  mat R4 = make_tridiagonal(4, 0, 1);
  cout << "R4 = " << R4 << endl;
  int k;
  int l;
  double maxA4 = max_offdiag_symmetric(A4, &k, &l);
  // double maxA6 = max_offdiag_symmetric(A6, &k, &l);

  vec eigenvalues(N);
  mat eigenvectors(N,N);
  int maxiter, iterations;
  bool converged;
  double tol = 1e-10;
  // jacobi_eigensolver(A6, R6, tol, eigenvalues, eigenvectors, maxiter, iterations, converged, k,l);
  jacobi_eigensolver(A4, R4, tol, eigenvalues, eigenvectors, maxiter, iterations, converged, k,l);
  cout << "Eigenvalues" << endl;
  eigenvalues.print();
  cout << "Eigenvectors" << endl;
  eigenvectors.print();
  return 0;
}
