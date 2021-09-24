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

    cout << "Eigenvalues computed with Armadillo`s arma::eig_sym:" << endl;
    eigval.print();

    cout << "Eigenvectors computed with Armadillo`s arma::eig_sym:" << endl;
    eigvec.print();


    vec lambda = vec(N);
    mat v = mat(N,N);
    analytic_eigprob(6, a, d, &lambda, &v);

    cout << "Eigenvalues computed analytically" << endl;
    lambda.print();

    cout << "Eigenvectors computed analytically" << endl;
    v.print();

    /* Now the both the eigenvalues and eigenvectors computed
    with armadillo and the analytical solutions are printed to terminal,
    so we can compare them and conclude that they are equivalent.
    */
   return 0;
}
