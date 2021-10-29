#include <iostream>
#include <armadillo>
#include <valarray>

using namespace arma;
using namespace std;

int index(int i, int L) {
  // Function dealing with periodic boundary conditions
    return (i+L)%L;
}

int spinmat(mat A, int L, int i, int j) {
  // Helpfunction to avoid manually calling index() every time we want a element (i,j)
  // from matrix A
    return A(index(i, L), index(j, L));
}

double energy(mat A, int L) {
    // Func. that returns the total energy of the system
    double sum = 0;
    for (int j=0; j<=L-1; j++) {
        for (int i=0; i<=L-1; i++) {
            sum += spinmat(A,L,i,j)*spinmat(A,L,i+1,j) + spinmat(A,L,i,j)*spinmat(A,L,i,j+1);
        }
    }
    return -sum;
}

int delta_E(mat A, int L, int i, int j){
  // Func. computing difference in energy after flipping a single spin at index (i,j)
  return 2*(spinmat(A, L, i, j)*spinmat(A, L, i-1, j)
          + spinmat(A, L, i, j)*spinmat(A, L, i+1, j)
          + spinmat(A, L, i, j)*spinmat(A, L, i, j-1)
          + spinmat(A, L, i, j)*spinmat(A, L, i, j+1));
}

double boltzmann_factor(mat A, int L, int i, int j, double beta){
  // Func. returning the Boltzmann factor at a given index (i,j)
  vec boltzmann_list  = vec(17);
  boltzmann_list = {exp(8*beta), 0, 0, 0, exp(4*beta), 0, 0, 0, 1, 0, 0, 0, exp(-4*beta), 0, 0, 0, exp(-8*beta)};
  return boltzmann_list(delta_E(A, L, i, j) + 8);
}

void test(int L, int i, int j){
  // Func. testing some functions in our code
  double tol = 1e-8;
  int beta = 1;
  mat A(L, L); // Make test-matrix
  A.fill(1); // Let all elements have state s_i = +1

  // Test energy()
  double E = energy(A, L);
  double E_analytic = -8;
  if (abs(E-E_analytic) > tol){
    cout << "Computed energy, E, not equal to analytic value"<< endl;
  }

  // Test delta_E()
  int dE = delta_E(A, L, i, j);
  double dE_analytic = 8;
  if (abs(dE-dE_analytic) > tol){
    cout << "Computed delta energy, dE, not equal to analytic value"<< endl;
  }

  // Test boltzmann_factor()
  double Boltzmann_factor = boltzmann_factor(A, L, i, j, beta);
  double Boltzmann_factor_analytic = exp(-8*beta);
  if (abs(Boltzmann_factor-Boltzmann_factor_analytic) > tol){
    cout << "Computed Boltzmann factor not equal to analytic value"<< endl;
  }
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


int main() {

    int L = 2;
    double Tk_b = 1.0;
    double beta = 1/Tk_b;
    test(L, 0, 1);

    return 0;
}
