#include <iostream>
#include <armadillo>
#include <valarray>
#include "functions.cpp"
//#include <cstdlib>

using namespace arma;
using namespace std;

int main() {

    int L = 2;
    int N = L*L;
    int N_cycle = 10000;
    double Tk_B = 1.0;
    double beta = 1/Tk_B;
    int E_sys;
    int E_tot;
    int E_tot2;
    int M_sys = 0;
    int M_tot;
    int M_tot2;
    int M_abs;
    int T = 1; //[J/k_B]

    mat S = make_matrix(L, &M_sys);
    S.print("S = ");

    E_sys = energy(S,L);
    E_tot = E_sys;
    E_tot2 = E_sys*E_sys;
    M_tot = M_sys;
    M_tot2 = M_sys*M_sys;
    cout << "E0 = " << E_sys << endl;
    cout << "M0 = " << M_sys << endl;

    for (int i = 0; i < N_cycle; i++){
      for (int j = 0; j < N; j++){
        mat S_new = metropolis(S, L, beta, &E_sys, &M_sys);
      E_tot += E_sys;
      M_tot += M_sys;

      E_tot2 += E_sys*E_sys;
      M_tot2 += M_sys*M_sys;

      M_abs = fabs(M_tot);

      }
    }

    //mat S_new = metropolis(S, L, beta, &E_sys, &M_sys);
    //S_new.print("S_new = ");
    //cout << "E_sys = " << E_sys << endl;
    //cout << "M_sys = " << M_sys << endl;
    //cout << "E_tot = " << E_tot << endl;
    //cout << "M_tot = " << M_tot << endl;
    //cout << "M_abs = " << M_abs << endl;
    cout << "-----------------------------------\n" << endl;
    double eps_exp = E_tot/(N_cycle*N);
    double m_exp = M_tot/(N_cycle*N);
    double eps2_exp = E_tot2/(N_cycle*N);
    double m2_exp = M_tot2/(N_cycle*N);
    double m_abs_exp = M_abs/(N_cycle*N);
    double C_v = beta/T*(eps2_exp - (eps_exp*eps_exp));
    double X = beta*(m2_exp - (m_exp*m_exp));

    cout << "C_v = " << C_v << endl;
    cout << "X = " << X << endl;
    cout << "m_abs_exp = " <<  m_abs_exp << endl;
    cout << "eps_exp = " << eps_exp << endl;
    return 0;

}
