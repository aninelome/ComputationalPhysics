#include <iostream>
#include <armadillo>
#include <valarray>
#include "isingmodel.hpp"
//#include <cstdlib>

using namespace arma;
using namespace std;


int main(int argc, const char* argv[]){
  int N_cycles = 2000000;  // Number of Markov Chain Monte Carlo cycles
  int N_burn = 10000;  // Number of Markov Chain Monte Carlo cycles used for burn-in
  vec T_list = linspace(2.1, 2.4, 50); // 50 temperatures from 2.1 to 2.4

  // Declaring vectors to store results
  vec C_v_vec = vec(T_list.size());
  vec X_vec = vec(T_list.size());
  vec eps_exp_temp = vec(T_list.size());
  vec m_abs_temp = vec(T_list.size());

  // Defining vector with different lattice sizes
  vec L_list = vec(4);
  L_list(0) = 40;
  L_list(1) = 60;
  L_list(2) = 80;
  L_list(3) = 100;

  // Looping over different lattice sizes and temperatures
  for (int j = 0; j < L_list.size(); j++)
  {
    int L = L_list(j);
    for (int i = 0; i < T_list.size(); i++)
    {
      cout << i << endl;
      double T = T_list(i);
      double Tk_B = T;
      double beta = 1/Tk_B;
      vec eps_exp_vec = vec(N_cycles+1);
      vec m_abs_vec = vec(N_cycles+1);
      vec eps_vec = vec(N_cycles+1);
      IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
      isingmodel.mcmc(N_burn, i, &C_v_vec, &X_vec, &eps_exp_temp, &m_abs_temp);
    }

      // Storing final results in .bin files 
      C_v_vec.save("C_v_vec"+to_string(L)+".bin");
      X_vec.save("X_vec"+to_string(L)+".bin");
      eps_exp_temp.save("eps_exp_temp"+to_string(L)+".bin");
      m_abs_temp.save("m_abs_temp"+to_string(L)+".bin");
  }
  T_list.save("T_list.bin");

  return 0;
}
