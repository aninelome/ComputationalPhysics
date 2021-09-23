// Main program for problem 6

#include "functions.hpp"

int main(){
  vec N = {10, 50, 100, 1000, 10000};
  for (int i = 0; sizeof(N); i++){
    double n = N(i)+1;
    double h = 1/n;
    double a = -1/(h*h);
    double d = 2/(h*h);
    mat A = make_tridiagonal(N(i), a, d);
    mat R = make_tridiagonal(N(i), 0, 1);
    int k;
    int l;
    double maxA6 = max_offdiag_symmetric(A, &k, &l);
    vec eigenvalues(N(i));
    mat eigenvectors(N(i),N(i));
    int maxiter, iterations;
    maxiter = 1000000;
    bool converged;
    double tol = 1e-10;
    jacobi_eigensolver(A, R, tol, eigenvalues, eigenvectors, maxiter, 0, converged, k,l);
    cout << "Eigenvalues" << endl;
    eigenvalues.print();
    cout << "Eigenvectors" << endl;
    eigenvectors.print();
  }
  return 0;
}
