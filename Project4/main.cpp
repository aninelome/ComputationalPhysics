#include <iostream>
#include <armadillo>
#include <valarray>
#include "isingmodel.hpp"
//#include <cstdlib>

using namespace arma;
using namespace std;

int main() {

    int L = 2;
    // int N = L*L;
    int N_cycles = 100000;
    double Tk_B = 1.0;
    double beta = 1/Tk_B;
    int T = 1;

    IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
    isingmodel.mcmc();

    return 0;

}
