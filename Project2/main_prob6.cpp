// Main program for problem 6

#include "functions.hpp"

int main(){
  //Writing N and number of iterations to a txt file
  ofstream file;
  file.open("plot_prob6.txt", ios::out); //opens file in out/write mode
  arma::vec N = vec(4);
  N(0) = 10; N(1) = 50; N(2) = 100; N(3) = 250;
//Run through our functions and print the number of iterations for each value of N in jacobi_eigensolver function in functions.cpp
  for (int i = 0; i < N.size(); i++){
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
    int maxiter;
    maxiter = 1000000;
    bool converged;
    double tol = 1e-10;
    int iterations = jacobi_eigensolver(A, R, tol, eigenvalues, eigenvectors, maxiter, 0, converged, k,l);
    file << setw(25) << setprecision(3) << N(i);
    file <<fixed<< setw(25) << setprecision(8) << iterations << endl;
  }
  file.close();
  return 0;

}
