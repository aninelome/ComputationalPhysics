#include <iostream>
#include <armadillo>
#include <valarray>

using namespace arma;
using namespace std;

int index(i) {
    return i%L; 
}

int index(j) {
    return j%L; 
}

int spinmat(i,j) {
    return mat(index(i), index(j)); 
}

double E(mat A, double J, int L) {
    // Func. that returns the total energy of the system 
    double sum = 0; 
    for (int j=0; j=L-1; j++) {
        for (int i=0; i=L-1; i++) {
            sum += A(i,j)*A(i+1,j) + A(i,j)*A(i,j+1); 
        }
    }
    return -J*sum; 
}

int main() {
    // test matrix 
    int L = 2; 
    mat A(L, L); 
    A.fill(1); 
    A(0,1) = -1; 
    cout << A << endl; 
    mat B(L+1,L+1); 


    //B.fill(A)
    B(slice(0,L-1,1++), slice(0,L-1,1++)) = A;
    //B(0:-1,0:-1) = A; 

    B(L,L) = 0; 

    E(B, 2, L); 
    cout << E << endl; 
    return 0; 
}









/* 
double M(int L) {
    // Func. that returns the total magnetization of the system 
    // given by the sum over all the spins in the system 
    double sum = 0; 
    int N = L**2; 
    for (i=0; i=N-1; i++) {
        sum += A(i); 
    }
    return sum 
}


double eps(mat A, double J, int L, int N) {
    // function that returns energy per spin 
    eps = E(mat A, double J, int L)/N; 
    mean_eps = integrate eps(s) * probability(s) ds; 
    return eps, mean_eps; 
}

double m(int L) {
    // function that returns magnetization per spin 
    m = M(L)/N; 
    mean_m = ;
    return m, mean_m; 
}

double Cv() {
    return 1/(kB*T**2) * ()
}
*/