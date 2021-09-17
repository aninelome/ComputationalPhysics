#include "functions.hpp"

/*
void make_tridagonal_test(int N){

    mat A = make_tridiagonal(N);
    cout<<A<<endl;
    return;
}
*/

void test_max_offdiag(){
  int N = 4;
  mat A = mat_make_test_A(N);
  int k, l;
  double max_elem = max_offdiag_symmetric(A, &k, &l);
  double fasit = 0.7;

  if (abs(fasit - max_elem) <= pow(10,-8)){
    cout << "Our function works!"<< endl;
  }
  else {
    cout << "Max_offdiag does not work!!! max_elem = " << max_elem << endl;
  }
  return;
}
