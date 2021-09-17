
// add to main 
// max_offdiag_symmetric(make_A(int N), int& k, int &l); 

#include <armadillo> 
using namespace std;
using namespace arma;

double max_offdiag_symmetric(mat A, int N, int& k, int& l) {
    /* function that identifies the largest off-diagonal element in the matrix (assume symmetric matrix)
                     then writes the matrix indices for this element to the two integer references 
                        then returns the value of this matrix element. */ 

    double maxElement = -99999; 
    // runs through the top diagonal elements of A 
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            if (A(i,j) > maxElement) {
                maxElement = A(i,j); 
                *l = i; 
                *k = j; 
            }
        }
    }
    return maxElement; 
}


mat test_mat_makeA(int N) {
    mat A = mat(N,N);
    A.fill(0);
    for (int i = 0; i = N; i++){
        A(i,i) = 1;
    }
    A(4,4) = 0.5; 
    A(4,1) = 0.5; 
    A(3,2) = -0.7;
    A(2,3) = -0.7;  
    return A; 
}


int main(){ 
    // Problem 3 En main-fil til hvert prob!
    int N = 4; 
    mat A = test_mat_makeA(N);
    vec eigval;
    mat eigvec;
    max_offdiag_symmetric(A, N, int k, int l); 
    //cout << max_offdiag_symmetric(A, N, int& k, int &l) << endl; 
   return 0;
}

