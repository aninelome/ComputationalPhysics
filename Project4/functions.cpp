#include <iostream>
#include <armadillo>
#include <valarray>

using namespace arma;
using namespace std;

// Function dealing with periodic boundary conditions
int index(int i, int L) {
    return (i+L)%L;
}

// Helpfunction to avoid manually calling index() every time we want a element (i,j)
// from matrix S
int spinmat(mat S, int L, int i, int j) {
    return S(index(i, L), index(j, L));
}

// Func. that returns the total energy of the system
double energy(mat S, int L) {
    double sum = 0;
    for (int j=0; j<=L-1; j++) {
        for (int i=0; i<=L-1; i++) {
            sum += spinmat(S,L,i,j)*spinmat(S,L,i+1,j) + spinmat(S,L,i,j)*spinmat(S,L,i,j+1);
        }
    }
    return -sum;
}

// Func. computing difference in energy after flipping a single spin at index (i,j)
int delta_E(mat S, int L, int i, int j){
  return 2*(spinmat(S, L, i, j)*spinmat(S, L, i-1, j)
          + spinmat(S, L, i, j)*spinmat(S, L, i+1, j)
          + spinmat(S, L, i, j)*spinmat(S, L, i, j-1)
          + spinmat(S, L, i, j)*spinmat(S, L, i, j+1));
}

// Func. returning the Boltzmann factor at a given index (i,j)
double boltzmann_factor(mat S, int L, int i, int j, double beta){
  vec boltzmann_list  = vec(17);
  boltzmann_list = {exp(8*beta), 0, 0, 0, exp(4*beta), 0, 0, 0, 1, 0, 0, 0, exp(-4*beta), 0, 0, 0, exp(-8*beta)};
  return boltzmann_list(delta_E(S, L, i, j) + 8);
}

// Function making matrix containing random spins
mat make_matrix(int L, int* M_sys){
  random_device rd;
  mt19937_64 gen(rd());
  uniform_int_distribution<int> RandGen(0,1);
  int prob;

  mat S = mat(L,L);
  for (int j=0; j<=L-1; j++) {
      for (int i=0; i<=L-1; i++) {
        prob = RandGen(gen);
        S(i,j) = 2*prob - 1;
        (*M_sys) += S(i,j);
    }
  }
  return S;
}

// Function implementing the Metropolis algorithm
mat metropolis(mat S, int L, double beta, int* E_sys, int* M_sys){
  random_device rd;
  mt19937_64 gen(rd());
  uniform_int_distribution<int> RandGen(0,L-1);
  int i_index;
  int j_index;

  i_index = RandGen(gen);
  j_index = RandGen(gen);

  //mat S_prime = S;
  mat S_new;

  //S_prime(i_index, j_index) = -S_prime(i_index, j_index);
  S(i_index, j_index) *= -1;
  //int dE = delta_E(S_prime, L, i_index, j_index);
  int dE = delta_E(S, L, i_index, j_index);

  if (dE <= 0 ){
    int dM = 2*S(i_index, j_index);
    (*E_sys) += dE;
    (*M_sys) += dM;
  }
  else {

    double P_ratio = boltzmann_factor(S, L, i_index, j_index, beta);

    random_device ud; //Random device for uniform distribution
    mt19937_64 gen_u(ud());
    uniform_real_distribution<double> Unigen(0.0,1.0);
    double r;

    r = Unigen(gen_u); //Generating random number
    vec A_list(2);
    A_list[0] = 1;
    A_list[1] = P_ratio;

    if (r <= min(A_list)){
      int dM = 2*S(i_index, j_index);
      (*E_sys) += dE;
      (*M_sys) += dM;
    }
    else{
      S(i_index, j_index) *= -1;
    }
  }
  return S;
}

/*
double M(int L) {
    // Func. that returns the total magnetization of the system
    // given by the sum over all the spins in the system
    double sum = 0;
    int N = L**2;
    for (i=0; i=N-1; i++) {
        sum += S(i);
    }
    return sum
}


double eps(mat S, double J, int L, int N) {
    // function that returns energy per spin
    eps = E(mat S, double J, int L)/N;
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
