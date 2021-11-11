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
    double Tk_B = 1.0;
    double beta = 1/Tk_B;
    int T = 1;
    vec eps_vec = vec(N_cycles+1);
    vec m_abs_vec = vec(N_cycles+1);
    vec N_c_vec = linspace(0,N_cycles, N_cycles+1);
    cout << "N_cycles = " << N_cycles << endl;
    IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
    isingmodel.mcmc(&eps_vec, &m_abs_vec);
    eps_vec.save("eps_vec.bin");
    m_abs_vec.save("m_abs_vec.bin");
     N_c_vec.save("N_c_vec.bin");

    return 0;

}
