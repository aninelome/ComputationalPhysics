#include <iostream>
#include <armadillo>
#include <valarray>
#include <string>

using namespace arma;
using namespace std;

class IsingModel
{
private:
    beta_;
    T_; 
    L_;
    N_cycles_;    

public:
    int index(int i, int L);

    int spinmat(mat S, int L, int i, int j);

    double energy(mat S, int L);

    int delta_E(mat S, int L, int i, int j);

    double boltzmann_factor(mat S, int L, int i, int j, double beta);

    mat make_matrix(int L);

    mat S = mat(L,L);

    mat metropolis(mat S, int L, double beta);
    
    vec boltzmann_list;
    
}


