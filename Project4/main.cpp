#include <iostream>
#include <armadillo>
#include <valarray>
#include "isingmodel.hpp"
//#include <cstdlib>

using namespace arma;
using namespace std;

int main() {

    int L = 20;
    int N_cycles = 100000;
    double Tk_B = 1;
    double beta = 1/Tk_B;
    double T = 1;
    int N_burn = 70000;
    vec eps_exp_vec = vec(N_cycles+1);
    vec m_abs_vec = vec(N_cycles+1);
    vec N_c_vec = linspace(0,N_cycles, N_cycles+1);
    vec eps_vec = vec(N_cycles+1);
    cout << "N_cycles = " << N_cycles << endl;
    IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
    isingmodel.burnintime(N_burn);
    isingmodel.mcmc(&eps_exp_vec, &m_abs_vec, &eps_vec);
    eps_exp_vec.save("eps_exp_vec.bin");
    m_abs_vec.save("m_abs_vec.bin");
    N_c_vec.save("N_c_vec.bin");
    eps_vec.save("eps_vec.bin");


    return 0;

}
