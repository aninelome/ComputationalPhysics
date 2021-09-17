// Main program for problem 5

#include "functions.hpp"

int main(){
  /*Ting som må fikses/ spm:
  - FÅR FEIL I ITERASJON NUMMER 4!!!!!!!!
  - Skal programmet exite når vi når maxiter?
  - Hvorfor converged = true?
  */
  int N = 6;
  double n = N+1;
  double h = 1/n;
  double a = -1/(h*h);
  double d = 2/(h*h);
  cout << "a=" << a << endl;
  mat A6 = make_tridiagonal(N, a, d);
  cout << "A6= " << A6 << endl;
  mat R6 = make_tridiagonal(N, 0, 1);
  int k;
  int l;
  double maxA6 = max_offdiag_symmetric(A6, &k, &l);

  vec eigenvalues(N);
  mat eigenvectors(N,N);
  int maxiter, iterations;
  maxiter = 100;
  bool converged;
  double tol = 1e-10;
  jacobi_eigensolver(A6, R6, tol, eigenvalues, eigenvectors, maxiter, 0, converged, k,l);
  cout << "Eigenvalues" << endl;
  eigenvalues.print();
  cout << "Eigenvectors" << endl;
  eigenvectors.print();
  return 0;
}
