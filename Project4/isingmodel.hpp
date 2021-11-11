#ifndef ISINGMODEL_HPP
#define ISINGMODEL_HPP

#include <iostream>
#include <armadillo>
#include <valarray>
#include <string>

using namespace arma;
using namespace std;

class IsingModel
{
private:
    double beta_;
    double T_;
    int L_;
    int N_cycles_;
    double M_sys;
    imat S;


public:
    IsingModel(double beta, double T, int L, int N_cycles);

    int index(int i);

    int spinmat(imat S, int i, int j);

    double energy(imat S);

    int delta_E(imat &S, int i, int j);

    double boltzmann_factor(vec boltzmann_list, int dE);

    imat make_matrix(double* M);

    void metropolis(imat &S, double* E_sys, double* M_sys);

    void mcmc(vec* eps_exp_vec, vec* m_abs_vec, vec* eps_vec);

    void metropolis_burnin(imat &S);

    void burnintime(int N_burn);

    vec boltzmann_list;

};
#endif
