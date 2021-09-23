#include "functions.hpp"

using namespace std;
using namespace arma;

mat make_tridiagonal(int N, double a, double d){
    mat A = mat(N,N);
    A.fill(0);           // Making A
    for (int i = 0; i <= N-2; i++){ // Filling A
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


void analytic_eigprob(int N, double a, double d){
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


double max_offdiag_symmetric(mat A, int* k, int* l) {
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


void jacobi_rotate(mat& A, mat& R, int k, int l, double tol){
  int N = A.n_rows;
  double tau;
  double t;
  double c;
  double s;

  if (A(k,l) != 0.){
    tau = (A(l,l) - A(k,k))/ (2*A(k,l));
    if (tau >= 0.){
      t = 1./(tau + sqrt(1.+tau*tau));
    }else{
      t = -1./(-tau + sqrt(1.+tau*tau));
    }
    c = 1./sqrt(1.+t*t);
    s = c*t;

  }
  else{
    c = 1.;
    s = 0.;
  }

  double temp_Akk = A(k,k);
  double temp_All = A(l,l);
  double temp_Akl = A(k,l);
  A(k,k) = temp_Akk*c*c - 2*temp_Akl*c*s + temp_All*s*s;
  A(l,l) = temp_All*c*c + 2*temp_Akl*c*s + temp_Akk*s*s;
  A(k,l) = 0.0;
  A(l,k) = 0.0;
  for (int i = 0; i < N; i++){
    if (i != l && i != k){
      double temp_Aik = A(i,k);
      double temp_Ail = A(i,l);
      A(i,k) = A(i,k)*c - temp_Ail*s;
      A(k,i) = A(i,k);
      A(i,l) = A(i,l)*c + temp_Aik*s;
      A(l,i) = A(i,l);
    }
  }
  for (int i=0; i<N; i++){
    double temp_Rik = R(i,k);
    double temp_Ril = R(i,l);
    R(i,k) = R(i,k)*c - temp_Ril*s;
    R(i,l) = R(i,l)*c + temp_Rik*s;
  }

 return;
}


int jacobi_eigensolver(mat& A, mat& R, double tol, vec& eigenvalues, mat& eigenvectors,
const int maxiter, int iterations, bool converged, int k, int l){
  int N = A.n_rows;
  while (abs(A(k,l)) > tol && iterations <= maxiter){
    iterations = iterations +1;
    //cout << k << l << endl;

    jacobi_rotate(A, R, k,l, tol);
    double max_offdiag_A = max_offdiag_symmetric(A, &k, &l);
  }
  cout << "N = " << N << endl;
  cout << "iterations = " << iterations << endl;
  converged = true;
  for (int i = 0; i < N; i++){
    eigenvalues(i) = A(i,i);
  eigenvectors = R;
}

  return iterations;
}
