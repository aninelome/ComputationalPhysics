// Main program for problem 5

#include "functions.hpp"

int main(){
  int N = 6;
  double n = N+1;
  double h = 1/n;
  double a = -1/(h*h);
  double d = 2/(h*h);
  mat A6 = make_tridiagonal(N, a, d);
  mat R6 = make_tridiagonal(N, 0, 1);
  int k;
  int l;
  double maxA6 = max_offdiag_symmentric(A6, &k, &l)

  return 0;
}
