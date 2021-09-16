// Main program

#include "functions.hpp"

// mat make_A(int);
// void solve_eig_prob(mat, vec*, mat*);
// void make_A_test(int N);

int main(){ 
    // Problem 3 En main-fil til hvert prob!

    mat A6 = make_A(6);
    cout<<A6<<endl;
    vec eigval;
    mat eigvec;
    solve_eig_prob(A6, &eigval, &eigvec);
    eigval.print();
    eigvec.print();

   return 0;
}
