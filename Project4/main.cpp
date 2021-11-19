#include <iostream>
#include <armadillo>
#include <valarray>
#include "isingmodel.hpp"
//#include <cstdlib>

using namespace arma;
using namespace std;

//void run_sim(int T, int L, int N_cycles, int N_burn, int i, vec C_v_vec, vec X_vec, vec eps_exp_temp, vec m_abs_temp){
//  double Tk_B = T;
//  double beta = 1/Tk_B;
//  vec eps_exp_vec = vec(N_cycles+1);
//  vec m_abs_vec = vec(N_cycles+1);
//  vec eps_vec = vec(N_cycles+1);
//  IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
//  isingmodel.mcmc(&eps_exp_vec, &m_abs_vec, &eps_vec, N_burn, i, &C_v_vec, &X_vec, &eps_exp_temp, &m_abs_temp);
//}


int main(int argc, const char* argv[]){
  int N_cycles = 1000000;
  int N_burn = 10000;
  vec T_list = linspace(2.1, 2.4, 10);
  vec C_v_vec = vec(T_list.size());
  vec X_vec = vec(T_list.size());
  vec eps_exp_temp = vec(T_list.size());
  vec m_abs_temp = vec(T_list.size());
  vec L_list = vec(1);
  //L_list(0) = 20;
  //L_list(1) = 60;
  L_list(0) = 80;
  //L_list(0) = 100;
  //double T = 1;
  //double L = 20;
  //double beta = 1./T;
  //IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
  ////double start = omp_get_wtime();
  //isingmodel.mcmc(N_burn, 0, &C_v_vec, &X_vec, &eps_exp_temp, &m_abs_temp);

  //double end = omp_get_wtime();
  //double timeused = end-start;
  //cout << "timeused = " << timeused << " seconds " << endl;
  //exit(1);


  for (int j = 0; j < L_list.size(); j++){
    int L = L_list(j);
    for (int i = 0; i < T_list.size(); i++){
      cout << i << endl;
      double T = T_list(i);
      double Tk_B = T;
      double beta = 1/Tk_B;
      vec eps_exp_vec = vec(N_cycles+1);
      vec m_abs_vec = vec(N_cycles+1);
      vec eps_vec = vec(N_cycles+1);
      IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
      isingmodel.mcmc(N_burn, i, &C_v_vec, &X_vec, &eps_exp_temp, &m_abs_temp);
      //run_sim(T_list(i), L, N_cycles, N_burn, i, C_v_vec, X_vec, eps_exp_temp, m_abs_temp);
      //exit(1);
      }


      cout << "C_v_vec = " << C_v_vec << endl;
      C_v_vec.save("C_v_vec"+to_string(L)+".bin");
      X_vec.save("X_vec"+to_string(L)+".bin");
      eps_exp_temp.save("eps_exp_temp"+to_string(L)+".bin");
      m_abs_temp.save("m_abs_temp"+to_string(L)+".bin");
  }
  T_list.save("T_list.bin");

  return 0;
}

//tuple<double, double, double, double> run_sim(int T, int L, int N_cycles, int N_burn){
//  double Tk_B = T;
//  double beta = 1/Tk_B;
//  vec eps_exp_vec = vec(N_cycles+1);
//  vec m_abs_vec = vec(N_cycles+1);
//  vec eps_vec = vec(N_cycles+1);
//  IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
//  isingmodel.mcmc(&eps_exp_vec, &m_abs_vec, &eps_vec, N_burn);
//  double C_v, m_abs_exp, X, eps_exp;
//  C_v = isingmodel.C_v;
//  cout <<  isingmodel.C_v << endl;
//  cout << "C_v:" << C_v << endl;
//  m_abs_exp = isingmodel.m_abs_exp;
//  X = isingmodel.X;
//  eps_exp = isingmodel.eps_exp;
//  return tuple<double,double,double,double>{C_v, X, eps_exp, m_abs_exp};
//}
//
//
//int main(int argc, const char* argv[]){
//  int L = 2;
//  int N_cycles = 100000;
//  int N_burn = 1000;
//  vec T_list = linspace(1, 2.4, 30);
//  vec C_v_vec = vec(T_list.size());
//  vec X_vec = vec(T_list.size());
//  vec eps_exp_temp = vec(T_list.size());
//  vec m_abs_temp = vec(T_list.size());
//
//
//  tuple<double,double,double,double> tmp;
//  for (int i = 0; i < T_list.size(); i++){
//    //cout << i << endl;
//    tmp = run_sim(T_list(i), L, N_cycles, N_burn);
//    C_v_vec(i) = get<0>(tmp);
//    X_vec(i) = get<1>(tmp);
//    eps_exp_temp(i) = get<2>(tmp);
//    m_abs_temp(i) = get<3>(tmp);
//    }
//  //cout << "C_v:" << C_v_vec << endl;
//  C_v_vec.save("C_v_vec.bin");
//  X_vec.save("X_vec.bin");
//  eps_exp_temp.save("eps_exp_temp.bin");
//  m_abs_temp.save("m_abs_temp.bin");
//  T_list.save("T_list.bin");
//
//
//
//  return 0;
//}

//int main(int argc, const char* argv[]) {
//
//    int L = 20;
//    int N_cycles = 100000;
//    double Tk_B = 1;
//    double beta = 1/Tk_B;
//    double T = 1;
//    int N_burn = 1000;
//    vec eps_exp_vec = vec(N_cycles+1);
//    vec m_abs_vec = vec(N_cycles+1);
//    vec N_c_vec = linspace(0,N_cycles, N_cycles+1);
//    vec eps_vec = vec(N_cycles+1);
//    cout << "N_cycles = " << N_cycles << endl;
//    IsingModel isingmodel = IsingModel(beta, T,  L,  N_cycles);
//    isingmodel.mcmc(&eps_exp_vec, &m_abs_vec, &eps_vec, N_burn);
//    eps_exp_vec.save("eps_exp_vec.bin");
//    m_abs_vec.save("m_abs_vec.bin");
//    N_c_vec.save("N_c_vec.bin");
//    eps_vec.save("eps_vec.bin");
//
//
//    return 0;
//
//}
