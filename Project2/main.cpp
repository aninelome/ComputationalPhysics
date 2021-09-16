// Main program

#include "functions.hpp"


int main(){ 
    // Problem 3 En main-fil til hvert prob!

    mat A6 = make_A(6);
    vec eigval;
    mat eigvec;
    solve_eig_prob(A6, &eigval, &eigvec);
    eigval.print();
    eigvec.print();

   return 0;
}
