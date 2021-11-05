// #include <iostream>
// #include <armadillo>
// #include <valarray>
#include "functions.hpp"

// using namespace arma;
// using namespace std;


// Constructor 
IsingModel::IsingModel(double beta, double T, int L, int N_cycles){
  beta_ = beta;
  T_ = T; 
  L_ = L;
  N_cycles_ = N_cycles;
}



// Function dealing with periodic boundary conditions
int IsingModel::index(int i) {
    return (i+L_)%L_;
}

// Helpfunction to avoid manually calling index() every time we want a element (i,j)
// from matrix S
int IsingModel::spinmat(mat S, int i, int j) {
    return S(index(i, L_), index(j, L_));
}

// Func. that returns the total energy of the system
double IsingModel::energy(mat S) {
    double sum = 0;
    for (int j=0; j<=L_-1; j++) {
        for (int i=0; i<=L_-1; i++) {
            sum += spinmat(S,L_,i,j)*spinmat(S,L_,i+1,j) + spinmat(S,L_,i,j)*spinmat(S,L_,i,j+1);
        }
    }
    return -sum;
}

// Func. computing difference in energy after flipping a single spin at index (i,j)
int IsingModel::delta_E(mat S, int i, int j){
  return 2*(spinmat(S, L_, i, j)*spinmat(S, L_, i-1, j)
          + spinmat(S, __, i, j)*spinmat(S, L_, i+1, j)
          + spinmat(S, L_, i, j)*spinmat(S, L_, i, j-1)
          + spinmat(S, L_, i, j)*spinmat(S, L_, i, j+1));
}

// Func. returning the Boltzmann factor at a given index (i,j)
double IsingModel::boltzmann_factor(vec boltzmann_list, int dE){
  return boltzmann_list(dE + 8);
}

// Function making matrix containing random spins
mat IsingModel::make_matrix(int L, int* M_sys){
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
mat IsingModel::metropolis(mat S, int L, double beta, int* E_sys, int* M_sys){
  random_device rd;
  mt19937_64 gen(rd());
  uniform_int_distribution<int> RandGen(0,L-1);
  int i_index;
  int j_index;

  i_index = RandGen(gen);
  j_index = RandGen(gen);


  //S_prime(i_index, j_index) = -S_prime(i_index, j_index);
  //int dE = delta_E(S_prime, L, i_index, j_index);
  int dE = delta_E(S, L, i_index, j_index);
  // cout << "dE = " << dE << endl;

  if (dE <= 0 ){
    S(i_index, j_index) *= -1;
    int dM = 2*S(i_index, j_index);
    cout << "dM = " << dM << endl;
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
      S(i_index, j_index) *= -1;
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
