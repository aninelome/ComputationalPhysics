#include "functions.hpp"


mat make_A(int N){
    double n = N + 1;
    double h = 1/n;
    double a = -1/(h*h);
    double d = 2/(h*h);
    mat A = mat(N,N);
    A.fill(0);
    for (int i = 0; i <= N-2; i++){
        A(i,i) = d;
        A(i+1,i) = a;
        A(i,i+1) = a;
    }
    A(N-1,N-1) = d;
return A;
}

void solve_eig_prob(mat A, vec* eigval, mat* eigvec){
    eig_sym((*eigval), (*eigvec), A);
    return;
}