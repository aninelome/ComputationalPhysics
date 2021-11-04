#include <iostream>
#include <armadillo>
#include "functions.cpp"

using namespace arma;
using namespace std;

void test(int L, int i, int j){
  // Func. testing some functions in our code
  double tol = 1e-8;
  int beta = 1;
  mat S(L, L); // Make test-matrix
  S.fill(1); // Let all elements have state s_i = +1

  // Test energy()
  double E = energy(S, L);
  double E_analytic = -8;
  if (abs(E-E_analytic) > tol){
    cout << "Computed energy, E, not equal to analytic value"<< endl;
  }

  // Test delta_E()
  int dE = delta_E(S, L, i, j);
  double dE_analytic = 8;
  if (abs(dE-dE_analytic) > tol){
    cout << "Computed delta energy, dE, not equal to analytic value"<< endl;
  }

  // Test boltzmann_factor()
  double Boltzmann_factor = boltzmann_factor(S, L, i, j, beta);
  double Boltzmann_factor_analytic = exp(-8*beta);
  if (abs(Boltzmann_factor-Boltzmann_factor_analytic) > tol){
    cout << "Computed Boltzmann factor not equal to analytic value"<< endl;
  }
}

int main() {
  int L = 5;
  double Tk_b = 1.0;
  double beta = 1/Tk_b;
  test(2, 0, 1);
    return 0;
}
