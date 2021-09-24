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

    vec lambda;
    mat v;
    analytic_eigprob(6, a, d, &lambda, &v);

    cout << "\n" << endl;
    cout << "Eigenvalues computed with Armadillo`s arma::eig_sym:" << endl;
    eigval.print();
    cout << "\n" << endl;

    cout << "Eigenvalues computed analytically" << endl;
    lambda.print();
    cout << "\n" << endl;

    cout << "Eigenvectors computed with Armadillo`s arma::eig_sym:" << endl;
    eigvec.print();
    cout << "\n" << endl;

    cout << "Eigenvectors computed analytically" << endl;
    v.print();
    cout << "\n" << endl;

    /* Now the both the eigenvalues and eigenvectors computed
    with armadillo and the analytical solutions are printed to terminal,
    so we can compare them and conclude that they are equivalent.
    */
   return 0;
}
