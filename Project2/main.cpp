// Main program

#include <iostream> // input and output 
#include <fstream>  
#include <math.h>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

mat make_A(int);
void solve_eig_prob(mat, vec*, mat*);
void make_A_test(int N);

int main(){ 
    // Problem 3 
    vec eigval;
    mat eigvec;

    mat A6;
    A6 = make_A(6);
   solve_eig_prob(A6, &eigval, &eigvec);
   eigval.print();
   eigvec.print();


   // Problem 4

   // Problem 5

   // Problem 6

   // Problem 7 


   // Testing
   make_A_test(6);

   return 0;
}

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

//Testing

void make_A_test(int N){
    mat A = make_A(N);
    cout<<A<<endl;
    return;
}
