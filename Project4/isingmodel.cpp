
#include "isingmodel.hpp"
#include "omp.h"  // OpenMP header

// Constructor
IsingModel::IsingModel(double beta, double T, int L, int N_cycles)
{
    beta_ = beta;
    T_ = T;
    L_ = L;
    N_ = L*L;
    N_cycles_ = N_cycles;
    //S = imat(L,L).fill(1);
    boltzmann_list = {exp(8 * beta_), 0, 0, 0, exp(4 * beta_),
    0, 0, 0, 1, 0, 0, 0, exp(-4 * beta_), 0, 0, 0, exp(-8 * beta_)};
}

// Function for resetting variables for each Markov Chain Monte Carlo cycle
void IsingModel::reset_variables(double* M_tot, double*  M_tot2, double*  M_abs)
{
    S = make_matrix(&M_sys);
    (*M_tot)= 0;
    (*M_tot2) = 0;
    (*M_abs)= 0;
}

// Function dealing with periodic boundary conditions
int IsingModel::index(int i)
{
    return (i + L_) % L_;
}

// Helpfunction to avoid manually calling index() every time we want a element (i,j)
// from matrix S
int IsingModel::spinmat(imat S, int i, int j)
{
    return S(index(i), index(j));
}

// Function that returns the total energy of the system
double IsingModel::energy(imat &S)
{
    double sum = 0;
    for (int j = 0; j <= L_ - 1; j++)
    {
        for (int i = 0; i <= L_ - 1; i++)
        {
            sum += S.at(index(i),index(j))*(
              S.at(index(i+1), index(j))
              + S.at(index(i), index(j+1))
            );
        }
    }
    return -sum;
}

// Function making matrix containing random spins
imat IsingModel::make_matrix(double *M_sys)
{
    imat S = 2*randi(L_, L_, distr_param(0, 1)) - 1;
    (*M_sys) = 0;
    for (int j = 0; j <= L_ - 1; j++)
    {
        for (int i = 0; i <= L_ - 1; i++)
        {
            (*M_sys) += S.at(i, j);
        }
    }
    return S;
}

// Function implementing the Metropolis algorithm
void IsingModel::metropolis(imat &S, double* E_sys, double* M_sys)
{
    for (int n = 0; n < N_; n++)
    {
      int i = randi(distr_param(0,L_-1));
      int j = randi(distr_param(0,L_-1));


      int dE = 2*S.at(index(i),index(j))*(
        S.at(index(i+1), index(j))
        + S.at(index(i-1), index(j))
        + S.at(index(i), index(j+1))
        + S.at(index(i), index(j-1)));

      if (dE <= 0)
      {
          S.at(i, j) *= -1;
          int dM = 2 * S.at(i, j);
          (*E_sys) += dE;
          (*M_sys) += dM;
      }
      else if(randu() <= boltzmann_list.at(dE+8))
      {
          S.at(i, j) *= -1;
          int dM = 2 * S.at(i, j);
          (*E_sys) += dE;
          (*M_sys) += dM;
      }
    }
}


// Function running Markov Chain Monte Carlo method using the Metropolis algorithm
void IsingModel::mcmc(int N_burn, int i, vec* C_v_vec, vec* X_vec, vec* eps_exp_temp, vec* m_abs_temp)
{
    int N = L_ * L_;
    reset_variables(&M_tot, &M_tot2, &M_abs);

    E_sys = 1.*energy(S);
    E_tot = E_sys;
    E_tot2 = E_sys * E_sys;
    M_tot = M_sys;
    M_tot2 = M_sys * M_sys;


    for (int i = 0; i < N_burn; i++)
    {
        metropolis(S, &E_sys, &M_sys);
    }

    #ifdef _OPENMP
    {
    #pragma omp parallel
    {
      double E_local = E_sys;
      double M_local = M_sys;

      imat S_local = S;
      int thread_num = omp_get_thread_num();

      arma::arma_rng::set_seed(thread_num + 42);


      #pragma omp for reduction(+:E_tot, M_tot, M_abs, E_tot2, M_tot2)
      for (int i = 0; i < N_cycles_; i++)
      {
          metropolis(S_local, &E_local, &M_local);

          E_tot += E_local;
          M_tot += M_local;
          M_abs += fabs(M_local);

          E_tot2 += E_local * E_local;
          M_tot2 += M_local * M_local;
      }
    }
  }
  #else
  {
    for (int i = 0; i < N_cycles_; i++)
    {
        metropolis(S, &E_sys, &M_sys);

        E_tot += E_sys;
        M_tot += M_sys;
        M_abs += fabs(M_sys);

        E_tot2 += E_sys * E_sys;
        M_tot2 += M_sys * M_sys;
  }
  }
  #endif



  // Computing expectation values, heat capacity and susceptibility
  double eps_exp = E_tot / (N_cycles_ * N);
  double m_exp = M_tot / (N_cycles_ * N);
  double eps2_exp = (E_tot2 / N_cycles_) *1/(N * N);
  double m2_exp = (M_tot2 / N_cycles_) *1/(N * N);
  double m_abs_exp = M_abs / (N_cycles_ * N);
  double C_v = beta_ / T_ * (E_tot2/N_cycles_ - (E_tot/N_cycles_ * E_tot/N_cycles_));
  double X = beta_ * (M_tot2/N_cycles_ - (M_abs/N_cycles_ * M_abs/N_cycles_));


  // Updating result vectors for each Markov Chain Monte Carlo cycle
  (*C_v_vec)(i) = C_v / N;
  (*X_vec)(i) = X / N;
  (*eps_exp_temp)(i) = eps_exp;
  (*m_abs_temp)(i) = m_abs_exp;

}
