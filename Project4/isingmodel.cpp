
#include "isingmodel.hpp"

// Constructor
IsingModel::IsingModel(double beta, double T, int L, int N_cycles)
{
    beta_ = beta;
    T_ = T;
    L_ = L;
    N_cycles_ = N_cycles;
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

// Func. that returns the total energy of the system
double IsingModel::energy(imat S)
{
    double sum = 0;
    for (int j = 0; j <= L_ - 1; j++)
    {
        for (int i = 0; i <= L_ - 1; i++)
        {
            sum += spinmat(S, i, j) * spinmat(S, i + 1, j) + spinmat(S, i, j) * spinmat(S, i, j + 1);
        }
    }
    return -sum;
}

// Func. computing difference in energy after flipping a single spin at index (i,j)
int IsingModel::delta_E(imat &S, int i, int j)
{
    
    return 2 * spinmat(S, i, j)*(spinmat(S, i - 1, j) +  spinmat(S, i + 1, j) + spinmat(S, i, j - 1) + spinmat(S, i, j + 1));
}

// Func. returning the Boltzmann factor at a given index (i,j)
double IsingModel::boltzmann_factor(vec boltzmann_list, int dE)
{
    return boltzmann_list(dE + 8);
}

// Function making matrix containing random spins
imat IsingModel::make_matrix(double *M_sys)
{
    imat S = 2*randi(L_, L_, distr_param(0, 1)) - 1;
    for (int j = 0; j <= L_ - 1; j++)
    {
        for (int i = 0; i <= L_ - 1; i++)
        {
            (*M_sys) += S(i, j);
        }
    }
    return S;
}

// Function implementing the Metropolis algorithm
void IsingModel::metropolis(imat &S, double *E_sys, double *M_sys)
{
   
    int i_index = randi(distr_param(0,L_-1));
    int j_index = randi(distr_param(0,L_-1));

    //S_prime(i_index, j_index) = -S_prime(i_index, j_index);
    //int dE = delta_E(S_prime, L, i_index, j_index);
    int dE = delta_E(S, i_index, j_index);
    //cout << "dE = " << dE << endl;

    if (dE <= 0)
    {
        S(i_index, j_index) *= -1;
        int dM = 2 * S(i_index, j_index);
        //cout << "dM = " << dM << endl;
        (*E_sys) += dE;
        (*M_sys) += dM;
    }
    else if(randu() <= boltzmann_factor(boltzmann_list, dE)){
        S(i_index, j_index) *= -1;
        int dM = 2 * S(i_index, j_index);
        (*E_sys) += dE;
        (*M_sys) += dM;
    }
}

void IsingModel::mcmc()
{
    double E_sys;
    double E_tot;
    double E_tot2;
    double M_sys = 0;
    double M_tot;
    double M_tot2;
    double M_abs;
    int N = L_ * L_;
    boltzmann_list = {exp(8 * beta_), 0, 0, 0, exp(4 * beta_), 0, 0, 0, 1, 0, 0, 0, exp(-4 * beta_), 0, 0, 0, exp(-8 * beta_)};

    imat S = make_matrix(&M_sys);

    E_sys = 1.*energy(S);
    E_tot = E_sys;
    E_tot2 = E_sys * E_sys;
    M_tot = M_sys;
    M_tot2 = M_sys * M_sys;
    cout << "E0 = " << E_sys << endl;
    cout << "M0 = " << M_sys << endl;

    for (int i = 0; i < N_cycles_; i++)
    {
        for (int j = 0; j < N; j++)
        {
            metropolis(S, &E_sys, &M_sys);
        }
        E_tot += E_sys;
        M_tot += M_sys;
        M_abs += fabs(M_sys);

        E_tot2 += E_sys * E_sys;
        M_tot2 += M_sys * M_sys;

        //M_abs = fabs(M_tot);
    }
    cout << "-----------------------------------\n"
         << endl;
    cout << "E_sys = " << E_sys << endl;
    cout << "M_sys = " << M_sys << endl;
    cout << "E_tot = " << E_tot << endl;
    cout << "M_tot = " << M_tot << endl;
    cout << "M_abs = " << M_abs << endl;
    cout << "-----------------------------------\n"
         << endl;
    double eps_exp = E_tot / (N_cycles_ * N);
    double m_exp = M_tot / (N_cycles_ * N);
    double eps2_exp = E_tot2 / (N_cycles_ * N * N);
    double m2_exp = M_tot2 / (N_cycles_ * N * N);
    double m_abs_exp = M_abs / (N_cycles_ * N);
    double C_v = beta_ / T_ * (eps2_exp - (eps_exp * eps_exp));
    double X = beta_ * (m2_exp - (m_exp * m_exp));

    cout << "C_v = " << C_v << endl;
    cout << "X = " << X << endl;
    cout << "m_abs_exp = " << m_abs_exp << endl;
    cout << "eps_exp = " << eps_exp << endl;
    cout << "eps2_exp = " << eps2_exp << endl;
    cout << "m2_exp = " << m2_exp << endl;
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
