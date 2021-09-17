
// add to main
// max_offdiag_symmetric(make_A(int N), int& k, int &l);

#include <armadillo>
using namespace std;
using namespace arma;

double max_offdiag_symmetric(mat A, int* k, int* l) {
    /* function that identifies the largest off-diagonal element in the matrix (assume symmetric matrix)
                     then writes the matrix indices for this element to the two integer references
                        then returns the value of this matrix element. */
    int N = A.n_rows;
    double maxElement = 0.0;
    // runs through the top diagonal elements of A
    for (int j = 0; j <= N-2; j++) {
        for (int i = j+1; i <= N-1; i++) {
            if (abs(A(i,j)) > maxElement) {
                maxElement = abs(A(i,j));
                (*l) = i;
                (*k) = j;
            }
        }
    }
    return maxElement;
}



mat mat_make_test_A(int N) {
    mat A = mat(N,N);
    A.fill(0);
    for (int i = 0; i < N; i++){
        A(i,i) = 1;
    }
    A(0,3) = 0.5;
    A(3,0) = 0.5;
    A(1,2) = -0.7;
    A(2,1) = -0.7;
    return A;
}

void test_max_offdiag(double max_element){
  double fasit = 0.7;
  if (abs(fasit - max_element) <= pow(10,-8)){
    cout << "Our function works!"<< endl;
  }

}

int main(){
    // Problem 3 En main-fil til hvert prob!
    int N = 4;
    mat A = mat_make_test_A(N);
    vec eigval;
    mat eigvec;
    int k;
    int l;
    double max_elem = max_offdiag_symmetric(A, &k, &l);
    test_max_offdiag(max_elem);
   return 0;
}
