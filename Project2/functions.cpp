#include "functions.hpp"

using namespace std;
using namespace arma;

mat make_A(int N){                 // Function to make A
    double n = N + 1;
    double h = 1/n;
    double a = -1/(h*h);
    double d = 2/(h*h);
    mat A = mat(N,N);               // Making A
    for (int i = 0; i <= N-2; i++){ // Filling A
        A(i,i) = d;
        A(i+1,i) = a;
        A(i,i+1) = a;
    }
    A(N-1,N-1) = d;
return A;
}

void solve_eig_prob(mat A, vec* eigval, mat* eigvec){ // using armadillo to find eigenvalues and eigenvectors
    eig_sym((*eigval), (*eigvec), A);
    return;
}

void analytic_eigprob(int N){  //Finding eiegnvalues and eigenvectors with the analytical formula
    double n = N + 1;
    double h = 1/n;
    double a = -1/(h*h);
    double d = 2/(h*h);
    vec lambda = vec(N);
    mat v = mat(N,N);
    for (int i = 0; i <= N-1; i++) {
        lambda(i) = d + 2*a*cos(((i+1)*M_PI)/(N+1));
        for (int k = 0; k <= N-1; k++) {
            v(k,i) = sin(((k+1)*(i+1)*M_PI)/(N+1));
        }
    }

    v = normalise(v, 2, 0);
    lambda.print();
    v.print();
    
return;
}