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
    double E_sys;
    double E_tot;
    double E_tot2;
    double M_tot;
    double M_tot2;
    double M_abs;
    vec boltzmann_list;
    int N_;



public:
  // Public observables

    double C_v;
    double X;
    double eps_exp;
    double m_abs_exp;


    IsingModel(double beta, double T, int L, int N_cycles);

    void reset_variables(double* M_tot, double*  M_tot2, double*  M_abs);

    int index(int i);

    int spinmat(imat S, int i, int j);

    double energy(imat &S);

    int delta_E(imat &S, int i, int j);

    double boltzmann_factor(vec boltzmann_list, int dE);

    imat make_matrix(double* M);

    void metropolis(imat &S, double* E_sys, double* M_sys);

    void mcmc(int N_burn, int i, vec* C_v, vec* X_vec, vec* eps_exp_temp, vec* m_abs_temp);



};
#endif
