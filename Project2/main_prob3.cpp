// Main program for problem 3

#include "functions.hpp"


int main(){
    int N = 6;
    double n = N+1;
    double h = 1/n;
    double a = -1/(h*h);
    double d = 2/(h*h);
    mat A6 = make_tridiagonal(N, a, d);

    vec eigval;
    mat eigvec;
    solve_eig_prob(A6, &eigval, &eigvec);
    eigval.print();
    eigvec.print();

    analytic_eigprob(6, a, d);

    /* Now the both the eigenvalues and eigenvectors computed
    with armadillo and the analytical solutions are printed to terminal,
    so we can compare them and conclude that they are equivalent.
    */
   return 0;
}
